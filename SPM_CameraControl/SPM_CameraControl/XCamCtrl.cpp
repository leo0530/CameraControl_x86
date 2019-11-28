// XCamCtrl.cpp: implementation of the CXCamCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "SPM_Camera.h"
#include "XCamCtrl.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//相机图像数据指针
BYTE* g_pRGBData1 = NULL;
BYTE* g_pRGBData2 = NULL;
BYTE* g_pRGBData3 = NULL;
BYTE* g_pRGBData4 = NULL;
BYTE* g_pRGBData5 = NULL;
BYTE* g_pRGBData6 = NULL;
BYTE* g_pRGBData7 = NULL;
BYTE* g_pRGBData8 = NULL;

PBITMAPINFO g_pBitInfo1 = NULL;
PBITMAPINFO g_pBitInfo2 = NULL;
PBITMAPINFO g_pBitInfo3 = NULL;
PBITMAPINFO g_pBitInfo4 = NULL;
PBITMAPINFO g_pBitInfo5 = NULL;
PBITMAPINFO g_pBitInfo6 = NULL;
PBITMAPINFO g_pBitInfo7 = NULL;
PBITMAPINFO g_pBitInfo8 = NULL;

CXCamCtrl *g_pCamera1 = NULL;//相机1
CXCamCtrl *g_pCamera2 = NULL;//相机2
CXCamCtrl *g_pCamera3 = NULL;//相机3
CXCamCtrl *g_pCamera4 = NULL;//相机4
CXCamCtrl *g_pCamera5 = NULL;//相机5
CXCamCtrl *g_pCamera6 = NULL;//相机6
CXCamCtrl *g_pCamera7 = NULL;//相机7
CXCamCtrl *g_pCamera8 = NULL;//相机8
//相机打开状态
bool g_bIsCamera1Open = FALSE;
bool g_bIsCamera2Open = FALSE;
bool g_bIsCamera3Open = FALSE;
bool g_bIsCamera4Open = FALSE;
bool g_bIsCamera5Open = FALSE;
bool g_bIsCamera6Open = FALSE;
bool g_bIsCamera7Open = FALSE;
bool g_bIsCamera8Open = FALSE;
//相机停止状态
bool g_bIsCameta1Stop = FALSE;
bool g_bIsCameta2Stop = FALSE;
bool g_bIsCameta3Stop = FALSE;
bool g_bIsCameta4Stop = FALSE;
bool g_bIsCameta5Stop = FALSE;
bool g_bIsCameta6Stop = FALSE;
bool g_bIsCameta7Stop = FALSE;
bool g_bIsCameta8Stop = FALSE;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXCamCtrl::CXCamCtrl(UINT64 ID)
{
	m_pBitInfo = NULL;
	m_pRGBData = NULL;

	XCCAM_OPENPARAM OParam = {};
	XCCAM_COLORCONVMODE Mode = {};
	Mode.ShiftID = XCCAM_SFTAUTO;
	
	OParam.UID = ID;
	if (!::XCCAM_Open(&OParam, &m_hCamera))
		printf("Camera Open Error");
	Mode.Parallel_Thread = 4;
	::XCCAM_SetConvMode(m_hCamera, &Mode, NULL);
	::XCCAM_GetFeatureHandle(m_hCamera, &m_hFeature);
	
	if (!::XCCAM_ResourceAlloc(m_hCamera))
	{
		printf("Resource Alloc Error!");
	}
	
	ULONG Len = 0;
	if (!::XCCAM_GetBMPINFO(m_hCamera, NULL, &Len, false))
	{
		::XCCAM_ResourceRelease(m_hCamera);
		printf("Get BMPINFO Error!");
	}
	
	if (m_pBitInfo)
		delete[] m_pBitInfo;
	m_pBitInfo = (PBITMAPINFO)new BYTE[Len];
	
	if (!::XCCAM_GetBMPINFO(m_hCamera, m_pBitInfo, &Len, false))
	{
		::XCCAM_ResourceRelease(m_hCamera);
		printf("Get BMPINFO Error！");
	}
	//if(m_pRGBData)
	//	delete []m_pRGBData;
	//m_pRGBData = new BYTE[m_pBitInfo->bmiHeader.biSizeImage];
}

CXCamCtrl::~CXCamCtrl()
{
	::XCCAM_Close(m_hCamera);
	m_hCamera = NULL;
	
	if (m_pBitInfo)
		delete[]m_pBitInfo;
	//if(m_pRGBData)
	//	delete []m_pRGBData;
}



bool CXCamCtrl::StartCamera(IMAGEFUNC func)
{
	::XCCAM_SetImageCallBack(m_hCamera, this, func, Max_Buffer, false);
		
	if (!::XCCAM_ImageStart(m_hCamera))
	{
		::XCCAM_SetImageCallBack(m_hCamera, NULL, NULL, 0, false);
		::XCCAM_ResourceRelease(m_hCamera);
		printf("Image Start Error！");
		return false;
	}
	
	return true;
}

void CXCamCtrl::StopCamera()
{
	if(!::XCCAM_ImageStop(m_hCamera))
		printf("Image Stop Error");

	::XCCAM_SetImageCallBack(m_hCamera, 0, 0, 0, false);

	if(!::XCCAM_ResourceRelease(m_hCamera))
		printf("Resource Release Error");

}

void CXCamCtrl::GetCameraList(std::vector<UINT64>& List)
{	
	XCCAM_LIST* pDevList = NULL;
	
	pDevList = (XCCAM_LIST*)new BYTE[sizeof(XCCAM_LIST) + sizeof(XCCAM_DEVINFO) * 30];
	pDevList->Count = 30;
	if (!::XCCAM_GetList(pDevList))
	{
		delete[] pDevList;
		return;
	}
	
	for (ULONG idx = 0; idx < pDevList->Count; idx++)
	{
		List.push_back(pDevList->Info[idx].UID);
	/*	CameraInfo *pInfo = NULL;
		
		switch (pDevList->Info[idx].DeviceType)
		{
		case XCCAM_GIGECAMERA:
			pInfo = new CameraInfo(pDevList->Info[idx].UID, pDevList->Info[idx].u.GigEDev.ModelName);
			break;
		case XCCAM_USBCAMERA:
			pInfo = new CameraInfo(pDevList->Info[idx].UID, pDevList->Info[idx].u.UsbDev.ModelName);
			break;
		}

		if (pInfo)
			List.push_back(pInfo);*/
	}
	
	delete[] pDevList;
}

int CXCamCtrl::GetImageBufLen()
{
	return m_nRGBBufferLength;
}


PBITMAPINFO CXCamCtrl::GetBitmapInfo(void)
{
	return m_pBitInfo==NULL?NULL:m_pBitInfo;
}


BYTE* CXCamCtrl::GetImageDataBuffer(void)
{
	return m_pRGBData==NULL?NULL:m_pRGBData;
}
