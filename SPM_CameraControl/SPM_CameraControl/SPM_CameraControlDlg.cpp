
// SPM_CameraControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SPM_CameraControl.h"
#include "SPM_CameraControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCameraControlDlg* g_pArrayCams[8];
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

HWND g_hWnd = NULL;

CSPM_CameraControlDlg::CSPM_CameraControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSPM_CameraControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i=0;i<8;i++)
	{
		g_pArrayCams[i] = NULL;
	}
}

void CSPM_CameraControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_COMBO1, m_CameraList);
}

BEGIN_MESSAGE_MAP(CSPM_CameraControlDlg, CDialogEx)
//	ON_MESSAGE(WM_APP+1000,OnCameraOperate)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
//	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSPM_CameraControlDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON1, &CSPM_CameraControlDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START1, &CSPM_CameraControlDlg::OnBnClickedButtonStart1)
//	ON_BN_CLICKED(IDC_BUTTON_START2, &CSPM_CameraControlDlg::OnBnClickedButtonStart2)
END_MESSAGE_MAP()


// CSPM_CameraControlDlg 消息处理程序

geometry_msgs::Twist twist_msg;
//ros消息订阅回调函数
void cmd_vel_angular_callback(const geometry_msgs::Twist & cmd_vel)
{
	printf("接收手机cmd_vel %f, %f, %f, %f, %f, %f\n",
		cmd_vel.linear.x, cmd_vel.linear.y, cmd_vel.linear.z,
		cmd_vel.angular.x, cmd_vel.angular.y, cmd_vel.angular.z);
	twist_msg = cmd_vel;
}
ros::NodeHandle nh;
//消息订阅
ros::Subscriber < geometry_msgs::Twist > poseSub("cmd_vel", &cmd_vel_angular_callback);
//消息发布
ros::Publisher cmd_vel_pub("cmd_vel_winpc", &twist_msg);

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

	CreateCameraList(m_CameraInfoList);
	
	OpenCamera();//打开相机

//	InitRosClient();//ros 客户端配置

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
	
	CloseCamera();//关闭相机

	
}

void CSPM_CameraControlDlg::InitRosClient(void)//ligy 20191115 add.Ros客户端设置，设置为订阅模式
{
	char *ros_master = "192.168.1.150";

	printf("正在连接 %s\n", ros_master);
	nh.initNode(ros_master);

	nh.subscribe(poseSub);
	printf("等待接收消息\n");

	printf("转发cmd_vel_winpc消息 \n");


	nh.advertise(cmd_vel_pub);

	SetTimer(TIMER_ROS_PUBLIS, 100, NULL);//	启动定时器
}

void CSPM_CameraControlDlg::OpenCamera(void)
{
	if (m_CameraInfoList.size() == 0)
	{
		printf("no camera found!");
		return;
	}
		
	for (uint16_t i = 0; i < m_CameraInfoList.size(); i++)
	{
		
		try
		{
			g_pArrayCams[i] = new CCameraControlDlg(m_CameraInfoList[i],i+1,this);//相机i初始化
		}
		catch (...)
		{
			printf("Camera Open Error");
			return;
		}
	
	 //   g_pArrayCams[i]->ShowWindow(SW_SHOW);
	}
	
}


void CSPM_CameraControlDlg::CloseCamera(void)
{
	//释放相机对话框资源
	
	for (int i = 0; i < 8; i++)
	{
		if (g_pArrayCams[i])
			delete g_pArrayCams[i];
	}
}




void CSPM_CameraControlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	time_t timep;
	time(&timep);//获取时间戳

	char path[512];
	CString strTime, strPath;
	sprintf_s(path, "d:\\data\\%d_%d_%d.dat", timep, 20, 20);
	startTime = GetTickCount();

	if (g_pFileImage != NULL)
		fclose(g_pFileImage);
	fopen_s(&g_pFileImage, path, "w");
	g_bStartToWrite = true;
	g_iFrmNumsIsDone = 0;

	doOperateCamera(1,true);//相机1启动采集
	
	SetTimer(TIMER_CAMERA1_START,TIMER_PERID,NULL);

	printf("开始采集\n");
}

 void Delay(int ms)//精确到毫秒的延时
{
	LARGE_INTEGER litmp;
	LONGLONG QPart1, QPart2;
	double dfMinus, dfFreq, dfTim;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;// 获得初始值
	do
	{
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;//获得中止值
		dfMinus = (double)(QPart2 - QPart1);
		dfTim = dfMinus / dfFreq;// 获得对应的时间值，单位为秒
	} while (dfTim<0.001*ms);
}

void CSPM_CameraControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//if (nIDEvent == TIMER_ROS_PUBLIS)
	//{
	//	cmd_vel_pub.publish(&twist_msg);//ros节点发布消息
	//	nh.spinOnce();
	//}

	if (TIMER_CAMERA1_START == nIDEvent)
	{
		if (g_iImageDataWriteStatus == CAMERA_1_WRITEDONE)
		{	
			g_bStartToWrite = false;
			printf("相机1写完成，相机2开始\n");				
			doOperateCamera(1,false);//相机1停止采集
			doOperateCamera(2,true);//相机2启动采集
			g_bStartToWrite = true;
			g_iFrmNumsIsDone = 0;
			SetTimer(TIMER_CAMERA2_START,TIMER_PERID,NULL);
			KillTimer(TIMER_CAMERA1_START);
		}
	}

	if (TIMER_CAMERA2_START == nIDEvent)
	{
		if (g_iImageDataWriteStatus == CAMERA_2_WRITEDONE)
		{
			g_bStartToWrite = false;
			g_iFrmNumsIsDone = 0;
			doOperateCamera(2,false);//相机2停止采集
			fclose(g_pFileImage);
			printf("相机2写完成，结束\n");
			KillTimer(TIMER_CAMERA2_START);

			endTime = GetTickCount();

			printf("采集共用时%d ms",endTime-startTime);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSPM_CameraControlDlg::CreateCameraList(std::vector<UINT64>& List)
{

	::XCCAM_SetStructVersion(XCCAM_LIBRARY_STRUCT_VERSION);

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
	}

	delete[] pDevList;
}


void CSPM_CameraControlDlg::OnBnClickedButtonStart1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strButtonText;
	GetDlgItem(IDC_BUTTON_START1)->GetWindowText(strButtonText);

	if(!g_pArrayCams[0])
		return;

	if (strButtonText.Compare(_T("start1")) == 0)
	{
		GetDlgItem(IDC_BUTTON_START1)->SetWindowText(_T("stop1"));
	
		g_pArrayCams[0]->StartCap();
		///StartCap();
	}
	else
	{
		GetDlgItem(IDC_BUTTON_START1)->SetWindowText(_T("start1"));
		g_pArrayCams[0]->StopCap();
		//StopCap();
	}
}


//void CSPM_CameraControlDlg::OnBnClickedButtonStart2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString strButtonText;
//	GetDlgItem(IDC_BUTTON_START2)->GetWindowText(strButtonText);
//
//	if (!g_pArrayCams[1])
//	{
//		return;
//	}
//
//	g_iFrmNumsIsDone = 0;
//
//	if (strButtonText.Compare(_T("start2")) == 0)
//	{
//		GetDlgItem(IDC_BUTTON_START2)->SetWindowText(_T("stop2"));
//
//		g_pArrayCams[1]->StartCap();
//		///StartCap();
//	}
//	else
//	{
//		GetDlgItem(IDC_BUTTON_START2)->SetWindowText(_T("start2"));
//		//StopCap();
//		g_pArrayCams[1]->StopCap();
//	}
//}


// 相机操作，no 相机编号，bOpen 操作方式（false停止采集，true启动采集）
void CSPM_CameraControlDlg::doOperateCamera(int no, bool bOpen)
{
	if (no<1 || no>8)
	{
		printf("相机编号有误!正常范围是1-8！");
		return;
	}

	if (!g_pArrayCams[no-1])
	{
		printf("相机未打开！");
		return;
	}

	bOpen?g_pArrayCams[no-1]->StartCap():g_pArrayCams[no-1]->StopCap();
}
