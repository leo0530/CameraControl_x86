
// SPM_CameraControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SPM_CameraControl.h"
#include "SPM_CameraControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//geometry_msgs::Twist twist_msg;
//void cmd_vel_angular_callback(const geometry_msgs::Twist & cmd_vel)
//{
//	printf("接收手机cmd_vel %f, %f, %f, %f, %f, %f\n",
//		cmd_vel.linear.x, cmd_vel.linear.y, cmd_vel.linear.z,
//		cmd_vel.angular.x, cmd_vel.angular.y, cmd_vel.angular.z);
//	twist_msg = cmd_vel;
//}
//ros::NodeHandle nh;
//ros::Subscriber < geometry_msgs::Twist > poseSub("cmd_vel", &cmd_vel_angular_callback);
//ros::Publisher cmd_vel_pub("cmd_vel_winpc", &twist_msg);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// CSPM_CameraControlDlg 对话框


bool g_bSaveImage = false;//保存图像成bmp图片
bool g_bWriteDataToFile1 = false;
size_t g_iDataSize = 0;
HWND g_hWnd = NULL;

VOID CALLBACK ImageDataRcv(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;
	
	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData1);

	/*static int cnt = 0;
	cnt++;
	if(cnt%10 == 0)
	{
		::PostMessage(g_hWnd,WM_UPDATEIMAGE,NULL,NULL);
	}*/

	if(g_bSaveImage)
	{
		g_bSaveImage = false;
		::PostMessage(g_hWnd,WM_SAVEIMAGE,NULL,NULL);
	}

	//if(g_bWriteDataToFile1)//写数据流到文件
	//{
	//	g_bWriteDataToFile1 = false;
	//	
	//	SYSTEMTIME st;
	//	GetLocalTime(&st);
	//	char path[512];
	//	CString strTime,strPath;
	//	sprintf_s(path,"d:\\%04d%02d%02d_%02d%02d%02d%04d.dat",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wMinute,st.wMilliseconds);
	//	
	//	FILE * stream;
	//	stream=fopen(path, "w");
	//
	//	int ret = fwrite(g_pRGBData1, sizeof(BYTE), int(g_iDataSize/1000) , stream);
	//	fseek(stream,0,SEEK_END);//定位到文件尾
	//	fclose(stream);
	//}
 }

VOID CALLBACK ImageDataRcv2(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;
	
	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData2);
 }

VOID CALLBACK ImageDataRcv3(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData3);
}

VOID CALLBACK ImageDataRcv4(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData4);
}

VOID CALLBACK ImageDataRcv5(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData5);
}

VOID CALLBACK ImageDataRcv6(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData6);
}

VOID CALLBACK ImageDataRcv7(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData7);
}

VOID CALLBACK ImageDataRcv8(HCAMERA hCamera, pXCCAM_IMAGE pImage, pXCCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	CSPM_CameraControlDlg* pMp = (CSPM_CameraControlDlg*)Context;

	::XCCAM_ConvExec(hCamera, pImage, g_pRGBData8);
}

CSPM_CameraControlDlg::CSPM_CameraControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSPM_CameraControlDlg::IDD, pParent)
{
	//_CrtSetBreakAlloc(384); //384为块号

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iSelectCameraId = -1;

}

void CSPM_CameraControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_Image);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE, m_btnCapture);
}

LRESULT CSPM_CameraControlDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	UINT8 *data = new UINT8[READ_MAX_BUFFER];
	SOCKADDR_IN addrFrom;
	UINT32 len = udpCliCls.read(data, &addrFrom, wParam, lParam);
	if (len > 0)
	{
		printf("***UDP client recv\r\n", len);
		printf("ip = %08x port = %5d\r\n", addrFrom.sin_addr.S_un.S_addr, ntohs(addrFrom.sin_port));
		for (DWORD i = 0; i < len; i++)
		{
			printf("%d=%02x\r\n", i, data[i]);
		}
	}
	delete data;
	data = NULL;
	return 0;
}

bool CSPM_CameraControlDlg::InitSock(int port)
{
	WSADATA wsaData;

	//初始化TCP协议
	BOOL ret = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(ret != 0)
	{
		printf("初始化网络协议失败");
		return FALSE;
	}

	//创建服务器端套接字
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_serverSocket == INVALID_SOCKET)
	{
		printf("创建套接字失败");
		closesocket(m_serverSocket);
		WSACleanup();
		return FALSE;
	}

	//将SeverSock设置为异步非阻塞模式，并为它注册各种网络异步事件，其中m_hWnd      
	//为应用程序的主对话框或主窗口的句柄
	if(WSAAsyncSelect(m_serverSocket, this->m_hWnd, WM_CONNECT, FD_ACCEPT|FD_READ) == SOCKET_ERROR)
	{
		printf("注册网络异步事件失败");
		WSACleanup();
		return FALSE;
	}

	//绑定到本地一个端口上
	sockaddr_in localaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(port);     //端口号不要与其他应用程序冲突
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);;
	if(bind(m_serverSocket ,(struct sockaddr*)&localaddr,sizeof(sockaddr)) == SOCKET_ERROR)
	{
		printf("绑定地址失败");
		closesocket(m_serverSocket);
		WSACleanup();
		return FALSE;
	}


	listen(m_serverSocket, 5); //设置侦听模式

	return TRUE;
}

LRESULT CSPM_CameraControlDlg::OnConnect(WPARAM  wParam ,LPARAM lParam) 
{
	if (FD_READ == lParam)
	{
		char buf[1024] ={0}; 
		int len = recv(m_clientSocket,buf,1024,0) ;
		printf("%s\n",buf);
	}
	return 0;
}


BEGIN_MESSAGE_MAP(CSPM_CameraControlDlg, CDialogEx)
	ON_MESSAGE(WM_SAVEIMAGE,OnSaveImage)
	ON_MESSAGE(WM_UPDATEIMAGE,OnUpdateImage)
	ON_MESSAGE(UDP_READ, OnSock)	//消息绑定UDP_READ
	ON_MESSAGE(WM_CONNECT,OnConnect) 

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CSPM_CameraControlDlg::OnBnClickedButtonCapture)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSPM_CameraControlDlg::OnBnClickedButtonSave)
//	ON_BN_CLICKED(IDC_BUTTON1, &CSPM_CameraControlDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_ID1, &CSPM_CameraControlDlg::OnBnClickedRadioId1)
	ON_BN_CLICKED(IDC_RADIO_ID2, &CSPM_CameraControlDlg::OnBnClickedRadioId2)
	ON_BN_CLICKED(IDC_RADIO_ID3, &CSPM_CameraControlDlg::OnBnClickedRadioId3)
	ON_BN_CLICKED(IDC_RADIO_ID4, &CSPM_CameraControlDlg::OnBnClickedRadioId4)
	ON_BN_CLICKED(IDC_RADIO_ID5, &CSPM_CameraControlDlg::OnBnClickedRadioId5)
	ON_BN_CLICKED(IDC_RADIO_ID6, &CSPM_CameraControlDlg::OnBnClickedRadioId6)
	ON_BN_CLICKED(IDC_RADIO_ID7, &CSPM_CameraControlDlg::OnBnClickedRadioId7)
	ON_BN_CLICKED(IDC_RADIO_ID8, &CSPM_CameraControlDlg::OnBnClickedRadioId8)
	ON_BN_CLICKED(IDC_BUTTON1, &CSPM_CameraControlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSPM_CameraControlDlg 消息处理程序

BOOL CSPM_CameraControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	g_hWnd = GetSafeHwnd();

	

	(CButton*)GetDlgItem(IDC_RADIO_ID1)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_RADIO_ID2)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_RADIO_ID3)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_RADIO_ID4)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_RADIO_ID5)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_RADIO_ID6)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_RADIO_ID7)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_RADIO_ID8)->EnableWindow(FALSE);

	RECT rect;
	m_Image.GetClientRect(&rect);
	rect.right = rect.left + PICTUREWIDTH;
	rect.bottom = rect.top + PICTUREHEIGHT;
	m_Image.MoveWindow(&rect, FALSE);
	m_Image.Set_CCameraView(this);

	OpenCamera();//打开相机

//	InitRosClient();//初始化ros客户端，设置为订阅模式
//	SetTimer(2,100,NULL);

	/*if (!InitSock(8888))
	{
		printf("tcp server open fail");
	}*/

	if (!udpCliCls.IsOpen())
	{
		udpCliCls.Open("192.168.1.168",8888,this->m_hWnd);//服务器地址：192.168.1.168
	}

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSPM_CameraControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSPM_CameraControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSPM_CameraControlDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	KillTimer(2);//停止定时器
	CloseCamera();//关闭相机

	closesocket(m_serverSocket);          //关闭连接
	WSACleanup();
}


void CSPM_CameraControlDlg::OnBnClickedButtonCapture()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strBtnText;
	m_btnCapture.GetWindowTextW(strBtnText);

	if (strBtnText.Compare(_T("开始采集")) == 0)
	{ 
	//	StartCamera(1);
	//	StartCamera(2);

		SetTimer(1,100,NULL);
		m_btnCapture.SetWindowTextW(_T("采集停止"));
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

		m_btnCapture.SetWindowTextW(_T("开始采集"));
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
LRESULT CSPM_CameraControlDlg::OnSaveImage(WPARAM, LPARAM)
{
	if (!g_pRGBData1)
	{
		return 1;
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
	strTime.Format(_T("%04d%02d%02d_%02d%02d%02d%04d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wMinute,st.wMilliseconds);
	strPath = _T("d:\\") + strTime + _T(".bmp");

	CImage Image;

	Image.Attach(wBitMap);
	Image.Save(strPath, Gdiplus::ImageFormatBMP);

	return 0;
}

void CSPM_CameraControlDlg::OpenCamera(void)
{
	::XCCAM_SetStructVersion(XCCAM_LIBRARY_STRUCT_VERSION);

	CXCamCtrl::GetCameraList(m_CameraInfoList);//获取列表相机

	if(m_CameraInfoList.size() == 0)
	{
		printf("No Found Camera!");
		return;
	}

	
		
	//根据m_CameraInfoList依次打开相机
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
				g_iDataSize = g_pBitInfo1->bmiHeader.biSizeImage;
				g_pRGBData1 = new BYTE[g_pCamera1->GetBitmapInfo()->bmiHeader.biSizeImage];

			//	g_bIsCamera1Open = TRUE;

				(CButton*)GetDlgItem(IDC_RADIO_ID1)->EnableWindow(TRUE);
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

				(CButton*)GetDlgItem(IDC_RADIO_ID2)->EnableWindow(TRUE);
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

				(CButton*)GetDlgItem(IDC_RADIO_ID3)->EnableWindow(TRUE);
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

				(CButton*)GetDlgItem(IDC_RADIO_ID4)->EnableWindow(TRUE);
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

				(CButton*)GetDlgItem(IDC_RADIO_ID5)->EnableWindow(TRUE);
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

				(CButton*)GetDlgItem(IDC_RADIO_ID6)->EnableWindow(TRUE);
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

				(CButton*)GetDlgItem(IDC_RADIO_ID7)->EnableWindow(TRUE);
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

				(CButton*)GetDlgItem(IDC_RADIO_ID8)->EnableWindow(TRUE);
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
	// TODO: 在此添加控件通知处理程序代码
//	SaveImage(1);
	g_bSaveImage = true;
	g_bWriteDataToFile1 = true;

}



void CSPM_CameraControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*if(nIDEvent == 1)
	{
		::PostMessage(g_hWnd,WM_UPDATEIMAGE,NULL,NULL);
	}*/
	/*if (nIDEvent == 2)
	{
		cmd_vel_pub.publish(&twist_msg);
		nh.spinOnce();
	}*/
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


void CSPM_CameraControlDlg::OnBnClickedRadioId1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelectCameraId = 1;
}


void CSPM_CameraControlDlg::OnBnClickedRadioId2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelectCameraId = 2;
}


void CSPM_CameraControlDlg::OnBnClickedRadioId3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelectCameraId = 3;
}


void CSPM_CameraControlDlg::OnBnClickedRadioId4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelectCameraId = 4;
}


void CSPM_CameraControlDlg::OnBnClickedRadioId5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelectCameraId = 5;

}


void CSPM_CameraControlDlg::OnBnClickedRadioId6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelectCameraId = 6;
}


void CSPM_CameraControlDlg::OnBnClickedRadioId7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelectCameraId = 7;
}


void CSPM_CameraControlDlg::OnBnClickedRadioId8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iSelectCameraId = 8;
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
	//else if (index == 5)
	//{
	//	if (g_bIsCamera5Open)
	//	{	
	//		g_bIsCameta5Stop = !g_pCamera5->StartCamera(ImageDataRcv5);
	//	} 
	//} 
	//else if (index == 6)
	//{
	//	if (g_bIsCamera6Open)
	//	{	
	//		g_bIsCameta6Stop = !g_pCamera6->StartCamera(ImageDataRcv6);
	//	} 
	//} 
	//else if (index == 7)
	//{
	//	if (g_bIsCamera7Open)
	//	{	
	//		g_bIsCameta7Stop = !g_pCamera7->StartCamera(ImageDataRcv7);
	//	} 
	//} 
	//else if (index == 8)
	//{
	//	if (g_bIsCamera8Open)
	//	{	
	//		g_bIsCameta8Stop = !g_pCamera8->StartCamera(ImageDataRcv8);
	//	} 
	//} 
	
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


//void CSPM_CameraControlDlg::InitRosClient(void)//ligy 20191115 add.Ros客户端设置，设置为订阅模式
//{
//	//ros::NodeHandle nh;
//	char *ros_master = "192.168.1.150";
//
//	printf("正在连接 %s\n", ros_master);
//	nh.initNode(ros_master);
//
//	nh.subscribe(poseSub);
//	printf("等待接收消息\n");
//
//	printf("转发cmd_vel_winpc消息 \n");
//	
//	nh.advertise(cmd_vel_pub);
//	
//}


void CSPM_CameraControlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT8 buf[10]={1,2,3,5,6,7,8,9};
	udpCliCls.write(buf,8);
}
