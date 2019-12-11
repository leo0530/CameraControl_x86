// CameraControlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SPM_CameraControl.h"
#include "CameraControlDlg.h"
#include "afxdialogex.h"


extern "C" VOID CALLBACK ImageDataRcv(HCAMERA, XCCAM_IMAGE*, pXCCAM_IMAGEDATAINFO, PVOID);
// CCameraControlDlg �Ի���

IMPLEMENT_DYNAMIC(CCameraControlDlg, CDialogEx)

CCameraControlDlg::CCameraControlDlg(UINT64 UID, int camNo, CWnd* pParent /*=NULL*/)
	: CDialogEx(CCameraControlDlg::IDD, pParent)
	, m_hCamera()
	, m_pBitInfo()
	, m_pRGBData(),
	m_iCamNo(0)
{
	m_iCamNo = camNo;//������

	m_bCamIsCap = false;//Ĭ�ϲ��ɼ�

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
	//����������ɼ�״̬���ر�֮
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


// CCameraControlDlg ��Ϣ�������


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

	// TODO:  �ڴ˴������Ϣ����������
}


void CCameraControlDlg::StartCap()//�����ɼ���ʱ110ms����
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

	m_bCamIsCap = true;//�������ɼ�״̬
}


void CCameraControlDlg::StopCap()//ֹͣ�ɼ�ִ��ʱ��1000ms
{
	m_bCamIsCap = false;//�������ֹͣ�ɼ�״̬

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
//	ImageData Call Back 15msִ��һ��
extern "C" VOID CALLBACK ImageDataRcv(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CCameraControlDlg* pMp = (CCameraControlDlg*)Context;

	if(!pMp->m_pRGBData)
		return;

	static int cnt = 0;//����ÿ5s��һ��ͼ��

	if (cnt++%208 != 0)//ÿ��5s��һ��,208�Գ�����
	{
		return;
	}
	
	::XCCAM_ConvExec(hCamera, pImage, pMp->m_pRGBData);


	if (g_bStartToWrite)
	{
		if (g_iFrmNumsIsDone++ < FRAME_NUM_WRITE)//ÿ�������3��ͼ��
		{
			if (!g_pFileImage)
				return;
			fwrite(pMp->m_pRGBData, sizeof(BYTE), pMp->m_pBitInfo->bmiHeader.biSizeImage, g_pFileImage);
			fseek(g_pFileImage, 0, SEEK_END);//��λ���ļ�β
			printf("���%d_��%d֡���\n",pMp->m_iCamNo, g_iFrmNumsIsDone);
		}
		else
		{
			if (1 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_1_WRITEDONE;//���1дͼ���������							
			}
			else if (2 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_2_WRITEDONE;//���2дͼ���������
			}
			else if (3 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_3_WRITEDONE;//���3дͼ���������
			}
			else if (4 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_4_WRITEDONE;//���4дͼ���������
			}
			else if (5 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_5_WRITEDONE;//���5дͼ���������
			}
			else if (6 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_6_WRITEDONE;//���6дͼ���������
			}
			else if (7 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_7_WRITEDONE;//���7дͼ���������
			}
			else if (8 == pMp->m_iCamNo)
			{
				g_iImageDataWriteStatus = CAMERA_8_WRITEDONE;//���8дͼ���������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strContent;
	strContent.Format(_T("������%d"),m_iCamNo);
	SetWindowText(strContent);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

