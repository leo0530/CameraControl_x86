
// SPM_CameraControlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SPM_CameraControl.h"
#include "SPM_CameraControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CSPM_CameraControlDlg �Ի���


bool g_bSaveImage = false;//����ͼ���bmpͼƬ
bool g_bWriteDataToFile1 = false;
size_t g_iDataSize = 0;
HWND g_hWnd = NULL;

VOID CALLBACK ImageDataRcv(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;
	
	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData1);

	static int nFrameCnt = 0;//�ɼ�֡��

	if (nFrameCnt++ < FRAME_NUMS)//ÿ������洢3֡ͼ������
	{
		::PostMessage(g_hWnd,WM_SAVEIMAGE,1,NULL);
	}
	else
	{
		pMp->StartCamera(1,false);//ֹͣ���1�ɼ�
		pMp->StartCamera(2,true);//�������2�ɼ�
		nFrameCnt = 0;
	}

 }

VOID CALLBACK ImageDataRcv2(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;
	
	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData2);

	static int nFrameCnt = 0;//�ɼ�֡��

	if (nFrameCnt++ < FRAME_NUMS)//ÿ������洢3֡ͼ������
	{
		::PostMessage(g_hWnd,WM_SAVEIMAGE,2,NULL);
	}
	else
	{
		pMp->StartCamera(2,false);//ֹͣ���2�ɼ�
		pMp->StartCamera(3,true); //�������3�ɼ�
		nFrameCnt = 0;//�ɼ�֡�����㣬Ϊ�´βɼ���׼��
	}
 }

VOID CALLBACK ImageDataRcv3(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData3);

	static int nFrameCnt = 0;//�ɼ�֡��

	if (nFrameCnt++ < FRAME_NUMS)//ÿ������洢3֡ͼ������
	{
		::PostMessage(g_hWnd,WM_SAVEIMAGE,3,NULL);
	}
	else
	{
		pMp->StartCamera(3,false);//ֹͣ���3�ɼ�
		pMp->StartCamera(4,true); //�������4�ɼ�
		nFrameCnt = 0;//�ɼ�֡�����㣬Ϊ�´βɼ���׼��
	}
}

VOID CALLBACK ImageDataRcv4(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData4);

	static int nFrameCnt = 0;//�ɼ�֡��

	if (nFrameCnt++ < FRAME_NUMS)//ÿ������洢3֡ͼ������
	{
		::PostMessage(g_hWnd,WM_SAVEIMAGE,4,NULL);
	}
	else
	{
		pMp->StartCamera(4,false);//ֹͣ���3�ɼ�
		pMp->StartCamera(5,true); //�������4�ɼ�
		nFrameCnt = 0;//�ɼ�֡�����㣬Ϊ�´βɼ���׼��
	}
}

VOID CALLBACK ImageDataRcv5(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData5);

	static int nFrameCnt = 0;//�ɼ�֡��

	if (nFrameCnt++ < FRAME_NUMS)//ÿ������洢3֡ͼ������
	{
		::PostMessage(g_hWnd,WM_SAVEIMAGE,5,NULL);
	}
	else
	{
		pMp->StartCamera(5,false);//ֹͣ���5�ɼ�
		pMp->StartCamera(6,true); //�������6�ɼ�
		nFrameCnt = 0;//�ɼ�֡�����㣬Ϊ�´βɼ���׼��
	}
}

VOID CALLBACK ImageDataRcv6(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData6);

	static int nFrameCnt = 0;//�ɼ�֡��

	if (nFrameCnt++ < FRAME_NUMS)//ÿ������洢3֡ͼ������
	{
		::PostMessage(g_hWnd,WM_SAVEIMAGE,6,NULL);
	}
	else
	{
		pMp->StartCamera(6,false);//ֹͣ���6�ɼ�
		pMp->StartCamera(7,true); //�������7�ɼ�
		nFrameCnt = 0;//�ɼ�֡�����㣬Ϊ�´βɼ���׼��
	}
}

VOID CALLBACK ImageDataRcv7(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData7);

	static int nFrameCnt = 0;//�ɼ�֡��

	if (nFrameCnt++ < FRAME_NUMS)//ÿ������洢3֡ͼ������
	{
		::PostMessage(g_hWnd,WM_SAVEIMAGE,7,NULL);
	}
	else
	{
		pMp->StartCamera(7,false);//ֹͣ���7�ɼ�
		pMp->StartCamera(8,true); //�������8�ɼ�
		nFrameCnt = 0;//�ɼ�֡�����㣬Ϊ�´βɼ���׼��
	}
}

VOID CALLBACK ImageDataRcv8(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData8);

	static int nFrameCnt = 0;//�ɼ�֡��

	if (nFrameCnt++ < FRAME_NUMS)//ÿ������洢3֡ͼ������
	{
		::PostMessage(g_hWnd,WM_SAVEIMAGE,8,NULL);
	}
	else
	{
		pMp->StartCamera(8,false);//ֹͣ���8�ɼ�
		//pMp->StartCamera(4,true); //�������4�ɼ�
		if (pMp->m_FileToWrite != NULL)
		{
			fclose(pMp->m_FileToWrite);
			pMp->m_FileToWrite = NULL;
		}
		nFrameCnt = 0;//�ɼ�֡�����㣬Ϊ�´βɼ���׼��
	}
}

CSPM_CameraControlDlg::CSPM_CameraControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSPM_CameraControlDlg::IDD, pParent)
{
	//_CrtSetBreakAlloc(384); //384Ϊ���

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iSelectCameraId = -1;

	m_FileToWrite = NULL;

}

void CSPM_CameraControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_Image);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE, m_btnCapture);
}

BEGIN_MESSAGE_MAP(CSPM_CameraControlDlg, CDialogEx)
	ON_MESSAGE(WM_SAVEIMAGE,OnSaveImage)
	ON_MESSAGE(WM_UPDATEIMAGE,OnUpdateImage)
	ON_MESSAGE(WM_RECVDATA,OnRecvData)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CSPM_CameraControlDlg::OnBnClickedButtonCapture)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSPM_CameraControlDlg::OnBnClickedButtonSave)
	ON_WM_TIMER()

//	ON_BN_CLICKED(IDC_BUTTON1, &CSPM_CameraControlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSPM_CameraControlDlg ��Ϣ�������

BOOL CSPM_CameraControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	g_hWnd = GetSafeHwnd();

	RECT rect;
	m_Image.GetClientRect(&rect);
	rect.right = rect.left + PICTUREWIDTH;
	rect.bottom = rect.top + PICTUREHEIGHT;
//	m_Image.MoveWindow(&rect, FALSE);
//	m_Image.Set_CCameraView(this);

	OpenCamera();//�����

//	InitRosClient();//��ʼ��ros�ͻ��ˣ�����Ϊ����ģʽ
//	SetTimer(2,100,NULL);

	
	udpServ = new CDASocket();
	if (!udpServ->Create(8888,SOCK_DGRAM))
	{
		printf("udp server create failure1");
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSPM_CameraControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSPM_CameraControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSPM_CameraControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSPM_CameraControlDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	KillTimer(2);//ֹͣ��ʱ��
	CloseCamera();//�ر����

	if (udpServ)
	{
		delete udpServ;
	}
}


void CSPM_CameraControlDlg::OnBnClickedButtonCapture()
{
	::PostMessage(g_hWnd,WM_SAVEIMAGE,1,NULL);
	return;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strBtnText;

	m_btnCapture.GetWindowTextW(strBtnText);

	if (strBtnText.Compare(_T("��ʼ�ɼ�")) == 0)
	{ 
	//	StartCamera(1);
	//	StartCamera(2);

		SetTimer(1,100,NULL);
		m_btnCapture.SetWindowTextW(_T("�ɼ�ֹͣ"));
	}
	else
	{
		StopCamera(1);
		StopCamera(2);

		KillTimer(1);
	/*	StopCamera(2);
		StopCamera(3);
		StopCamera(4);
		StopCamera(5);
		StopCamera(6);
		StopCamera(7);
		StopCamera(8);*/

		m_btnCapture.SetWindowTextW(_T("��ʼ�ɼ�"));
	}
}


void CSPM_CameraControlDlg::ShowImage(void)
{
	m_Image.Invalidate(true);
}

void CMyDraw::DrawItem(LPDRAWITEMSTRUCT lpdis)
{
	return;
	CDC dc;
	CDC SrcData;
	CBitmap bmp;
	if(m_pView->m_iSelectCameraId == 1)
	{
		if(!g_pRGBData1)
			return;

		bmp.DeleteObject();
		bmp.CreateBitmap(
			g_pBitInfo1->bmiHeader.biWidth,
			g_pBitInfo1->bmiHeader.biHeight,
			g_pBitInfo1->bmiHeader.biPlanes,
			g_pBitInfo1->bmiHeader.biBitCount,
			g_pRGBData1);

		bmp.SetBitmapBits(g_pBitInfo1->bmiHeader.biSizeImage, g_pRGBData1);
		dc.Attach(lpdis->hDC);
		CRect rect(lpdis->rcItem);

		SrcData.CreateCompatibleDC(NULL);
		CBitmap* OldSrc = SrcData.SelectObject(&bmp);

		int Mode = dc.SetStretchBltMode(COLORONCOLOR);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &SrcData, 0, 0,
		g_pBitInfo1->bmiHeader.biWidth,
		g_pBitInfo1->bmiHeader.biHeight, 
		SRCCOPY);
		dc.SetStretchBltMode(Mode);
		SrcData.SelectObject(OldSrc);
		SrcData.DeleteDC();

		dc.Detach();
	}
	else if(m_pView->m_iSelectCameraId == 2)
	{
		if(!g_pRGBData2)
			return;

		bmp.DeleteObject();
		bmp.CreateBitmap(
			g_pBitInfo2->bmiHeader.biWidth,
			g_pBitInfo2->bmiHeader.biHeight,
			g_pBitInfo2->bmiHeader.biPlanes,
			g_pBitInfo2->bmiHeader.biBitCount,
			g_pRGBData2);

		bmp.SetBitmapBits(g_pBitInfo2->bmiHeader.biSizeImage, g_pRGBData2);
		dc.Attach(lpdis->hDC);
		CRect rect(lpdis->rcItem);

		SrcData.CreateCompatibleDC(NULL);
		CBitmap* OldSrc = SrcData.SelectObject(&bmp);

	
		int Mode = dc.SetStretchBltMode(COLORONCOLOR);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &SrcData, 0, 0,
		g_pBitInfo2->bmiHeader.biWidth,
		g_pBitInfo2->bmiHeader.biHeight, 
		SRCCOPY);
		dc.SetStretchBltMode(Mode);
		SrcData.SelectObject(OldSrc);
		SrcData.DeleteDC();

		dc.Detach();
	}

	
	
}
LRESULT CSPM_CameraControlDlg::OnUpdateImage(WPARAM, LPARAM)
{
	m_Image.Invalidate();
	return 0;
}

LRESULT CSPM_CameraControlDlg::OnRecvData(WPARAM wParam, LPARAM lParam)//udp�յ�����
{
//	TRACE("ʱ���:%x,λ��:%x\n",wParam,lParam);
	char path[512];
	CString strTime,strPath;
	sprintf_s(path,"d:\\%d_%d_%d.dat",wParam,(lParam>>16)&0xffff,lParam&0xffff);

	TRACE("%s\n",path);
	return 0;

	if (m_FileToWrite == NULL)
	{
		m_FileToWrite = fopen(path, "w");//���ļ�
		StartCamera(1,true);//�������1�ɼ�
	}

	return 0;
}
LRESULT CSPM_CameraControlDlg::OnSaveImage(WPARAM wParam, LPARAM lParam)
{
	WriteDataToFile(wParam);

	//if (!g_pRGBData1)
	//{
	//	return 1;
	//}

	//CBitmap wBitMap;

	//wBitMap.CreateBitmap(
	//	g_pBitInfo1->bmiHeader.biWidth,
	//	g_pBitInfo1->bmiHeader.biHeight,
	//	g_pBitInfo1->bmiHeader.biPlanes,
	//	g_pBitInfo1->bmiHeader.biBitCount,
	//	g_pRGBData1);

	//SYSTEMTIME st;
	//GetLocalTime(&st);
	//CString strTime,strPath;
	//strTime.Format(_T("%04d%02d%02d_%02d%02d%02d%04d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wMinute,st.wMilliseconds);
	//strPath = _T("d:\\") + strTime + _T(".bmp");

	//CImage Image;

	//Image.Attach(wBitMap);
	//Image.Save(strPath, Gdiplus::ImageFormatBMP);

	return 0;
}

void CSPM_CameraControlDlg::OpenCamera(void)
{
	::XCCAM_SetStructVersion(XCCAM_LIBRARY_STRUCT_VERSION);

	CXCamCtrl::GetCameraList(m_CameraInfoList);//��ȡ�б����

	if(m_CameraInfoList.size() == 0)
	{
		printf("No Found Camera!");
		return;
	}

	
		
	//����m_CameraInfoList���δ����
	for (UINT i = 0;i < m_CameraInfoList.size(); ++i)
	{
		if (i == 0)
		{
			g_pCamera1 = new CXCamCtrl(m_CameraInfoList[i]);
			if(g_pCamera1->GetBitmapInfo() != NULL)
			{
				g_pBitInfo1 = g_pCamera1->GetBitmapInfo();
				
				if(g_pRGBData1)
					delete []g_pRGBData1;
			//	g_iDataSize = g_pBitInfo1->bmiHeader.biSizeImage;
				g_pRGBData1 = new BYTE[g_pCamera1->GetBitmapInfo()->bmiHeader.biSizeImage];
			}
			else
			{
				delete g_pCamera1;
				if(g_pRGBData1)
					delete []g_pRGBData1;
			}
		}//end if (i == 0)
		else if (i == 1)
		{
			g_pCamera2 = new CXCamCtrl(m_CameraInfoList[i]);
			if(g_pCamera2->GetBitmapInfo() != NULL)
			{
				g_pBitInfo2 = g_pCamera2->GetBitmapInfo();
				if(g_pRGBData2)
					delete []g_pRGBData2;
				g_pRGBData2 = new BYTE[g_pCamera2->GetBitmapInfo()->bmiHeader.biSizeImage];

				g_bIsCamera2Open = TRUE;
			}
			else
			{
				delete g_pCamera2;
				if(g_pRGBData2)
					delete []g_pRGBData2;
			}
		}//end if (i == 1)
		else if (i == 2)
		{
			if(g_pCamera3->GetBitmapInfo() != NULL)
			{
				g_pBitInfo3 = g_pCamera3->GetBitmapInfo();
				if(g_pRGBData3)
					delete []g_pRGBData3;
				g_pRGBData3 = new BYTE[g_pCamera3->GetBitmapInfo()->bmiHeader.biSizeImage];

				g_bIsCamera3Open = TRUE;
			}
			else
			{
				delete g_pCamera3;
				if(g_pRGBData3)
					delete []g_pRGBData3;
			}
		}//end if (i == 2)
		else if (i == 3)
		{
			if(g_pCamera4->GetBitmapInfo() != NULL)
			{
				g_pBitInfo4 = g_pCamera4->GetBitmapInfo();
				if(g_pRGBData4)
					delete []g_pRGBData4;
				g_pRGBData4= new BYTE[g_pCamera4->GetBitmapInfo()->bmiHeader.biSizeImage];

				g_bIsCamera4Open = TRUE;
			}
			else
			{
				delete g_pCamera4;
				if(g_pRGBData4)
					delete []g_pRGBData4;
			}
		}//end if (i == 3)
		else if (i == 4)
		{
			if(g_pCamera5->GetBitmapInfo() != NULL)
			{
				g_pBitInfo5 = g_pCamera5->GetBitmapInfo();
				if(g_pRGBData5)
					delete []g_pRGBData5;
				g_pRGBData5= new BYTE[g_pCamera5->GetBitmapInfo()->bmiHeader.biSizeImage];

				g_bIsCamera5Open = TRUE;
			}
			else
			{
				delete g_pCamera5;
				if(g_pRGBData5)
					delete []g_pRGBData5;
			}
		}//end if (i == 4)
		else if (i == 5)
		{
			if(g_pCamera6->GetBitmapInfo() != NULL)
			{
				g_pBitInfo6 = g_pCamera6->GetBitmapInfo();
				if(g_pRGBData6)
					delete []g_pRGBData6;
				g_pRGBData6= new BYTE[g_pCamera6->GetBitmapInfo()->bmiHeader.biSizeImage];

				g_bIsCamera6Open = TRUE;
			}
			else
			{
				delete g_pCamera6;
				if(g_pRGBData6)
					delete []g_pRGBData6;
			}
		}//end if (i == 5)
		else if (i == 6)
		{
			if(g_pCamera7->GetBitmapInfo() != NULL)
			{
				g_pBitInfo7 = g_pCamera7->GetBitmapInfo();
				if(g_pRGBData7)
					delete []g_pRGBData7;
				g_pRGBData7= new BYTE[g_pCamera7->GetBitmapInfo()->bmiHeader.biSizeImage];

				g_bIsCamera7Open = TRUE;
			}
			else
			{
				delete g_pCamera7;
				if(g_pRGBData7)
					delete []g_pRGBData7;
			}
		}//end if (i == 6)
		else if (i == 7)
		{
			if(g_pCamera8->GetBitmapInfo() != NULL)
			{
				g_pBitInfo8 = g_pCamera8->GetBitmapInfo();
				if(g_pRGBData8)
					delete []g_pRGBData8;
				g_pRGBData8= new BYTE[g_pCamera8->GetBitmapInfo()->bmiHeader.biSizeImage];

				g_bIsCamera8Open = TRUE;
			}
			else
			{
				delete g_pCamera8;
				if(g_pRGBData8)
					delete []g_pRGBData8;
			}
		}//end if (i == 7)
	}

	
}


void CSPM_CameraControlDlg::CloseCamera(void)
{
	if (g_pCamera1)
	{
		if (!g_bIsCameta1Stop)
		{
			StartCamera(1,false);
		}
	}

	if (g_pCamera2)
	{
		if (!g_bIsCameta2Stop)
		{
			StartCamera(2,false);
		}
	}

	if (g_pCamera3)
	{
		if (!g_bIsCameta3Stop)
		{
			StartCamera(3,false);
		}
	}

	if (g_pRGBData1)
	{
		delete []g_pRGBData1;
	}

	if(g_pCamera2)
	{
		delete g_pCamera2;
	}

	if (g_pRGBData2)
	{
		delete []g_pRGBData2;
	}

	if(g_pCamera3)
	{
		delete g_pCamera3;
	}

	if (g_pRGBData3)
	{
		delete []g_pRGBData3;
	}

	if(g_pCamera4)
	{
		delete g_pCamera4;
	}

	if (g_pRGBData4)
	{
		delete []g_pRGBData4;
	}

	if(g_pCamera5)
	{
		delete g_pCamera5;
	}

	if (g_pRGBData5)
	{
		delete []g_pRGBData5;
	}

	if(g_pCamera6)
	{
		delete g_pCamera6;
	}

	if (g_pRGBData6)
	{
		delete []g_pRGBData6;
	}

	if(g_pCamera7)
	{
		delete g_pCamera7;
	}

	if (g_pRGBData7)
	{
		delete []g_pRGBData7;
	}

	if(g_pCamera8)
	{
		delete g_pCamera8;
	}

	if (g_pRGBData8)
	{
		delete []g_pRGBData8;
	}

	
}


void CSPM_CameraControlDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_bSaveImage = true;
	g_bWriteDataToFile1 = true;
}



void CSPM_CameraControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*if(nIDEvent == 1)
	{
		::PostMessage(g_hWnd,WM_UPDATEIMAGE,NULL,NULL);
	}*/
	//if (nIDEvent == 2)
	//{
	//	//cmd_vel_pub.publish(&twist_msg);
	//	//nh.spinOnce();
	//}
	CDialogEx::OnTimer(nIDEvent);
}


void CSPM_CameraControlDlg::SaveImage(int index)
{
	if (!g_pRGBData1)
	{
		return;
	}

	CBitmap wBitMap;

	wBitMap.CreateBitmap(
		g_pBitInfo1->bmiHeader.biWidth,
		g_pBitInfo1->bmiHeader.biHeight,
		g_pBitInfo1->bmiHeader.biPlanes,
		g_pBitInfo1->bmiHeader.biBitCount,
		g_pRGBData1);

	SYSTEMTIME st;
	GetLocalTime(&st);
	CString strTime,strPath;
	strTime.Format(_T("%4d-%2d-%2d-%2d-%2d-%2d-%4d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wMinute,st.wMilliseconds);
	strPath = _T("d:\\") + strTime + _T(".bmp");

	CImage Image;

	Image.Attach(wBitMap);
	Image.Save(strPath, Gdiplus::ImageFormatBMP);
}



bool CSPM_CameraControlDlg::StartCamera(int index,bool bOpen)
{
	if (index == 1)
	{
		if (g_pCamera1)
		{
			if (bOpen)
			{
				g_bIsCameta1Stop = !g_pCamera1->StartCamera(ImageDataRcv);
			} 
			else
			{
				g_pCamera1->StopCamera();
				g_bIsCameta1Stop = true;
			}
		}
	} 
	else if (index == 2)
	{
		if (g_pCamera2)
		{
			if (bOpen)
			{
				g_bIsCameta2Stop = !g_pCamera2->StartCamera(ImageDataRcv2);
			} 
			else
			{
				g_pCamera2->StopCamera();
				g_bIsCameta2Stop = true;
			}
		}
	} 
	else if (index == 3)
	{
		if (g_pCamera3)
		{
			if (bOpen)
			{
				g_bIsCameta3Stop = !g_pCamera3->StartCamera(ImageDataRcv3);
			} 
			else
			{
				g_pCamera3->StopCamera();
				g_bIsCameta3Stop = true;
			}
		}
	} 
	else if (index == 4)
	{
		if (g_pCamera4)
		{
			if (bOpen)
			{
				g_bIsCameta4Stop = !g_pCamera4->StartCamera(ImageDataRcv4);
			} 
			else
			{
				g_pCamera4->StopCamera();
				g_bIsCameta4Stop = true;
			}
		}
	} 
	else if (index == 5)
	{
		if (g_pCamera5)
		{
			if (bOpen)
			{
				g_bIsCameta5Stop = !g_pCamera5->StartCamera(ImageDataRcv5);
			} 
			else
			{
				g_pCamera5->StopCamera();
				g_bIsCameta5Stop = true;
			}
		}
	} 
	else if (index == 6)
	{
		if (g_pCamera6)
		{
			if (bOpen)
			{
				g_bIsCameta6Stop = !g_pCamera6->StartCamera(ImageDataRcv6);
			} 
			else
			{
				g_pCamera6->StopCamera();
				g_bIsCameta6Stop = true;
			}
		}
	} 
	else if (index == 7)
	{
		if (g_pCamera7)
		{
			if (bOpen)
			{
				g_bIsCameta7Stop = !g_pCamera7->StartCamera(ImageDataRcv7);
			} 
			else
			{
				g_pCamera7->StopCamera();
				g_bIsCameta7Stop = true;
			}
		}
	} 
	else if (index == 8)
	{
		if (g_pCamera8)
		{
			if (bOpen)
			{
				g_bIsCameta8Stop = !g_pCamera8->StartCamera(ImageDataRcv8);
			} 
			else
			{
				g_pCamera8->StopCamera();
				g_bIsCameta8Stop = true;
			}
		}
	} 

	
	return true;
}


void CSPM_CameraControlDlg::StopCamera(int index)
{
	if (index == 1)
	{
		if (g_bIsCamera1Open)
		{
			g_pCamera1->StopCamera();
			g_bIsCameta1Stop = true;
		} 
	}
	else if (index == 2)
	{
		if (g_bIsCamera2Open)
		{
			g_pCamera2->StopCamera();
			g_bIsCameta2Stop = true;
		} 
	}
	else if (index == 3)
	{
		if (g_bIsCamera3Open)
		{
			g_pCamera3->StopCamera();
			g_bIsCameta3Stop = true;
		} 
	}
	else if (index == 4)
	{
		if (g_bIsCamera4Open)
		{
			g_pCamera4->StopCamera();
			g_bIsCameta4Stop = true;
		} 
	}
	if (index == 5)
	{
		if (g_bIsCamera5Open)
		{
			g_pCamera5->StopCamera();
			g_bIsCameta5Stop = true;
		} 
	}
	else if (index == 6)
	{
		if (g_bIsCamera6Open)
		{
			g_pCamera6->StopCamera();
			g_bIsCameta6Stop = true;
		} 
	}
	else if (index == 7)
	{
		if (g_bIsCamera7Open)
		{
			g_pCamera7->StopCamera();
			g_bIsCameta7Stop = true;
		} 
	}
	else if (index == 8)
	{
		if (g_bIsCamera8Open)
		{
			g_pCamera8->StopCamera();
			g_bIsCameta8Stop = true;
		} 
	}
}


//void CSPM_CameraControlDlg::InitRosClient(void)//ligy 20191115 add.Ros�ͻ������ã�����Ϊ����ģʽ
//{
//	//ros::NodeHandle nh;
//	char *ros_master = "192.168.1.150";
//
//	printf("�������� %s\n", ros_master);
//	nh.initNode(ros_master);
//
//	nh.subscribe(poseSub);
//	printf("�ȴ�������Ϣ\n");
//
//	printf("ת��cmd_vel_winpc��Ϣ \n");
//	
//	nh.advertise(cmd_vel_pub);
//	
//}


void CSPM_CameraControlDlg::WriteDataToFile(int iCameraNo)//������ɼ��������Զ�������ʽд���ļ�
{
	if (m_FileToWrite == NULL)
	{
		return;
	}
	if (iCameraNo == 1)//���1
	{
		if (g_pRGBData1 == NULL)
		{
			return;
		}
		int ret = fwrite(g_pRGBData1, sizeof(BYTE), g_pBitInfo1->bmiHeader.biSizeImage, m_FileToWrite);
		fseek(m_FileToWrite,0,SEEK_END);//��λ���ļ�β
	} 
	else if (iCameraNo == 2)//���2
	{
		if (g_pRGBData2 == NULL)
		{
			return;
		}

		int ret = fwrite(g_pRGBData2, sizeof(BYTE), g_pBitInfo2->bmiHeader.biSizeImage, m_FileToWrite);
		fseek(m_FileToWrite,0,SEEK_END);//��λ���ļ�β
	} 
	else if (iCameraNo == 3)//���3
	{
		if (g_pRGBData3 == NULL)
		{
			return;
		}
		int ret = fwrite(g_pRGBData3, sizeof(BYTE), g_pBitInfo3->bmiHeader.biSizeImage, m_FileToWrite);
		fseek(m_FileToWrite,0,SEEK_END);//��λ���ļ�β
	} 
	else if (iCameraNo == 4)//���4
	{
		if (g_pRGBData4 == NULL)
		{
			return;
		}
		int ret = fwrite(g_pRGBData4, sizeof(BYTE), g_pBitInfo4->bmiHeader.biSizeImage, m_FileToWrite);
		fseek(m_FileToWrite,0,SEEK_END);//��λ���ļ�β
	} 
	else if (iCameraNo == 5)//���5
	{
		if (g_pRGBData5 == NULL)
		{
			return;
		}

		int ret = fwrite(g_pRGBData5, sizeof(BYTE), g_pBitInfo5->bmiHeader.biSizeImage, m_FileToWrite);
		fseek(m_FileToWrite,0,SEEK_END);//��λ���ļ�β
	} 
	else if (iCameraNo == 6)//���6
	{
		if (g_pRGBData6 == NULL)
		{
			return;
		}
		int ret = fwrite(g_pRGBData6, sizeof(BYTE), g_pBitInfo6->bmiHeader.biSizeImage, m_FileToWrite);
		fseek(m_FileToWrite,0,SEEK_END);//��λ���ļ�β
	} 
	else if (iCameraNo == 7)//���7
	{
		if (g_pRGBData7 == NULL)
		{
			return;
		}
		int ret = fwrite(g_pRGBData7, sizeof(BYTE), g_pBitInfo7->bmiHeader.biSizeImage, m_FileToWrite);
		fseek(m_FileToWrite,0,SEEK_END);//��λ���ļ�β
	} 
	else if (iCameraNo == 8)//���8
	{
		if (g_pRGBData8 == NULL)
		{
			return;
		}
		int ret = fwrite(g_pRGBData8, sizeof(BYTE), g_pBitInfo8->bmiHeader.biSizeImage, m_FileToWrite);
		fseek(m_FileToWrite,0,SEEK_END);//��λ���ļ�β
	} 
}
