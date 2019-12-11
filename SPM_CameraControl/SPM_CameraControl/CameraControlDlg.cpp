// CameraControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SPM_CameraControl.h"
#include "CameraControlDlg.h"
#include "afxdialogex.h"


extern "C" VOID CALLBACK ImageDataRcv(HCAMERA, XCCAM_IMAGE*, pXCCAM_IMAGEDATAINFO, PVOID);
// CCameraControlDlg 对话框

IMPLEMENT_DYNAMIC(CCameraControlDlg, CDialogEx)

CCameraControlDlg::CCameraControlDlg(UINT64 UID, int camNo, CWnd* pParent /*=NULL*/)
	: CDialogEx(CCameraControlDlg::IDD, pParent)
	, m_hCamera()
	, m_pBitInfo()
	, m_pRGBData(),
	m_iCamNo(0)
{
	m_iCamNo = camNo;//相机编号

	m_bCamIsCap = false;//默认不采集

	XCCAM_OPENPARAM OParam = {};
	XCCAM_COLORCONVMODE Mode = {};
	Mode.ShiftID = XCCAM_SFTAUTO;

	OParam.UID = UID;
	if (!::XCCAM_Open(&OParam, &m_hCamera))
		throw std::runtime_error("Camera Open Error");
	Mode.Parallel_Thread = 4;
	::XCCAM_SetConvMode(m_hCamera, &Mode, NULL);
	::XCCAM_GetFeatureHandle(m_hCamera, &m_hFeature);
	
	Create(CCameraControlDlg::IDD, pParent);
}

CCameraControlDlg::~CCameraControlDlg()
{
	//如果相机处理采集状态，关闭之
	//if (m_bCamIsCap)
	//	StopCap();

	//if (m_hCamera)
	//	XCCAM_Close(m_hCamera);

	//if (m_pBitInfo)
	//	delete[] m_pBitInfo;
	//if (m_pRGBData)
	//	delete[] m_pRGBData;
}

void CCameraControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_PICTURE, m_PictureBox);
}


BEGIN_MESSAGE_MAP(CCameraControlDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCameraControlDlg 消息处理程序


void CCameraControlDlg::OnDestroy()
{
	if (m_bCamIsCap)
		StopCap();

	if (m_hCamera)
	{
		::XCCAM_Close(m_hCamera);
		m_hCamera = NULL;
	}
	
	if (m_pBitInfo)
		delete[] m_pBitInfo;
	if (m_pRGBData)
		delete[] m_pRGBData;

	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


void CCameraControlDlg::StartCap()//启动采集用时110ms左右
{
	if (!::XCCAM_ResourceAlloc(m_hCamera))
	{
		printf("Resource Alloc Error");
		return;
	}

	ULONG Len = 0;
	if (!::XCCAM_GetBMPINFO(m_hCamera, NULL, &Len, false))
	{
		printf("Get BMPINFO Error");
		::XCCAM_ResourceRelease(m_hCamera);
		return;
	}

	if (m_pBitInfo)
		delete[] m_pBitInfo;
	m_pBitInfo = (PBITMAPINFO)new BYTE[Len];

	if (!::XCCAM_GetBMPINFO(m_hCamera, m_pBitInfo, &Len, false))
	{
		printf("Get BMPINFO Error");
		::XCCAM_ResourceRelease(m_hCamera);
		return;
	}


	if (m_pRGBData)
		delete[] m_pRGBData;
	m_pRGBData = new BYTE[m_pBitInfo->bmiHeader.biSizeImage];

	m_RGBBmp.DeleteObject();
	m_RGBBmp.CreateBitmap(
		m_pBitInfo->bmiHeader.biWidth,
		m_pBitInfo->bmiHeader.biHeight,
		m_pBitInfo->bmiHeader.biPlanes,
		m_pBitInfo->bmiHeader.biBitCount,
		m_pRGBData);

	::XCCAM_SetImageCallBack(m_hCamera, this, ImageDataRcv, Max_Buffer, false);


	if (!::XCCAM_ImageStart(m_hCamera))
	{
		printf("Image Start Error");
		::XCCAM_SetImageCallBack(m_hCamera, NULL, NULL, 0, false);
		::XCCAM_ResourceRelease(m_hCamera);
		return;
	}

	m_bCamIsCap = true;//相机处理采集状态
}


void CCameraControlDlg::StopCap()//停止采集执行时间1000ms
{
	m_bCamIsCap = false;//相机处理停止采集状态

	if (!::XCCAM_ImageStop(m_hCamera))
	{
		printf("Image Stop Error");
		return;
	}
		
	if (!::XCCAM_SetImageCallBack(m_hCamera, 0, 0, 0, false))
	{
		printf("Set Image CallBack Error");
	}

	if (!::XCCAM_ResourceRelease(m_hCamera))
	{
		printf("Resource Release Error");
		return;
	}	
}

DWORD time1 = 0;
DWORD time2 = 0;
//	ImageData Call Back 15ms执行一次
extern "C" VOID CALLBACK ImageDataRcv(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CCameraControlDlg* pMp = (CCameraControlDlg*)Context;

	if(!pMp->m_pRGBData)
		return;

	static int cnt = 0;//用于每5s存一幅图像

	if (cnt++%208 != 0)//每个5s存一次,208试出来的
	{
		return;
	}
	
	::XCCAM_ConvExec(hCamera, pImage, pMp->m_pRGBData);


	if (g_bStartToWrite)
	{
		if (g_iFrmNumsIsDone++ < FRAME_NUM_WRITE)//每个相机存3幅图像
		{
			if (!g_pFileImage)
				return;
			fwrite(pMp->m_pRGBData, sizeof(BYTE), pMp->m_pBitInfo->bmiHeader.biSizeImage, g_pFileImage);
			fseek(g_pFileImage, 0, SEEK_END);//定位到文件尾
			printf("相机%d_第%d帧完成\n",pMp->m_iCamNo, g_iFrmNumsIsDone);
		}
		else
		{
			if (1 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_1_WRITEDONE;//相机1写图像数据完毕							
			}
			else if (2 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_2_WRITEDONE;//相机2写图像数据完毕
			}
			else if (3 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_3_WRITEDONE;//相机3写图像数据完毕
			}
			else if (4 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_4_WRITEDONE;//相机4写图像数据完毕
			}
			else if (5 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_5_WRITEDONE;//相机5写图像数据完毕
			}
			else if (6 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_6_WRITEDONE;//相机6写图像数据完毕
			}
			else if (7 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_7_WRITEDONE;//相机7写图像数据完毕
			}
			else if (8 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_8_WRITEDONE;//相机8写图像数据完毕
			}

			cnt = 0;
		}		
	}

	/*SYSTEMTIME st;
	CString strDate, strTime;
	GetLocalTime(&st);
	printf("%d:%04d-%02d-%02d-%02d-%02d-%02d-%04d\n", 
		pMp->m_iCamNo,
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds
		);*/

}

BOOL CCameraControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strContent;
	strContent.Format(_T("相机编号%d"),m_iCamNo);
	SetWindowText(strContent);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

