
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

HWND g_hWnd = NULL;




CSPM_CameraControlDlg::CSPM_CameraControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSPM_CameraControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i=0;i<8;i++)
	{
		m_pArrayCams[i] = NULL;
	}
}

void CSPM_CameraControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_COMBO1, m_CameraList);
}

BEGIN_MESSAGE_MAP(CSPM_CameraControlDlg, CDialogEx)
	ON_MESSAGE(WM_APP+1000,OnControlCamera)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CSPM_CameraControlDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START1, &CSPM_CameraControlDlg::OnBnClickedButtonStart1)
END_MESSAGE_MAP()


// CSPM_CameraControlDlg ��Ϣ�������
bool g_bRun = false;//�����߳�ִ��
DWORD WINAPI ThreadFunc_CameraControl(LPVOID);//��������߳�

geometry_msgs::Twist twist_msg;
//ros��Ϣ���Ļص�����
void cmd_vel_angular_callback(const geometry_msgs::Twist & cmd_vel)
{
	printf("�����ֻ�cmd_vel %f, %f, %f, %f, %f, %f\n",
		cmd_vel.linear.x, cmd_vel.linear.y, cmd_vel.linear.z,
		cmd_vel.angular.x, cmd_vel.angular.y, cmd_vel.angular.z);
	twist_msg = cmd_vel;
}
ros::NodeHandle nh;
//��Ϣ����
ros::Subscriber < geometry_msgs::Twist > poseSub("cmd_vel", &cmd_vel_angular_callback);
//��Ϣ����
ros::Publisher cmd_vel_pub("cmd_vel_winpc", &twist_msg);

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

	CreateCameraList(m_CameraInfoList);
	
	OpenCamera();//�����

//	InitRosClient();//ros �ͻ�������

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
	
	CloseCamera();//�ر����

	
}

void CSPM_CameraControlDlg::InitRosClient(void)//ligy 20191115 add.Ros�ͻ������ã�����Ϊ����ģʽ
{
	char *ros_master = "192.168.1.150";

	printf("�������� %s\n", ros_master);
	nh.initNode(ros_master);

	nh.subscribe(poseSub);
	printf("�ȴ�������Ϣ\n");

	printf("ת��cmd_vel_winpc��Ϣ \n");


	nh.advertise(cmd_vel_pub);

	SetTimer(TIMER_ROS_PUBLIS, 100, NULL);//	������ʱ��
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
			m_pArrayCams[i] = new CCameraControlDlg(m_CameraInfoList[i],i+1,this);//���i��ʼ��
		}
		catch (...)
		{
			printf("Camera Open Error");
			return;
		}
	
	 //   m_pArrayCams[i]->ShowWindow(SW_SHOW);
	}
	
}


void CSPM_CameraControlDlg::CloseCamera(void)
{
	//�ͷ�����Ի�����Դ
	
	for (int i = 0; i < 8; i++)
	{
		if (m_pArrayCams[i])
			delete m_pArrayCams[i];
	}
}

///////////////////////////////////////////////////////////////////////////////
DWORD startTime;
DWORD endTime;
DWORD WINAPI ThreadFunc_CameraControl(LPVOID p)
{   
	CSPM_CameraControlDlg *pDlg = (CSPM_CameraControlDlg*)p;
	
	while (g_bRun)
	{
		if (g_iImageDataWriteStatus == CAMERA_1_WRITEDONE)
		{	
			g_bStartToWrite = false;
			printf("���1д��ɣ����2��ʼ\n");	
			pDlg->PostMessage(WM_APP+1000,1,2);//���1ֹͣ�ɼ������2��ʼ�ɼ�
		
			g_iFrmNumsIsDone = 0;
		}
		else if (g_iImageDataWriteStatus == CAMERA_2_WRITEDONE)
		{
			g_bStartToWrite = false;
			g_iFrmNumsIsDone = 0;
			pDlg->PostMessage(WM_APP+1000,2,-1);//���1ֹͣ�ɼ������2��ʼ�ɼ�
			fclose(g_pFileImage);
			printf("���2д��ɣ�����\n");
			endTime = GetTickCount();
			printf("�ɼ�����ʱ%d ms",endTime-startTime);

			g_bRun = false;//��ֹ�߳�
		}
	}
	
	//printf("�������̣߳� pid = %d\n", GetCurrentThreadId());   //������߳�pid
	return 0;
}

void CSPM_CameraControlDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	time_t timep;
	time(&timep);//��ȡʱ���

	char path[512];
	CString strTime, strPath;
	sprintf_s(path, "d:\\data\\%d_%d_%d.dat", timep, 20, 20);
	startTime = GetTickCount();

	if (g_pFileImage != NULL)
		fclose(g_pFileImage);
	fopen_s(&g_pFileImage, path, "w");
	g_bStartToWrite = true;
	g_iFrmNumsIsDone = 0;

	doOperateCamera(1,true);//���1�����ɼ�
	
	SetTimer(TIMER_CAMERA1_START,TIMER_PERID,NULL);

	
	//DWORD  threadId = 0;
	//g_bRun = true;//��ʼִ��
	//HANDLE hThread = CreateThread(NULL, 0, ThreadFunc_CameraControl, this, 0, &threadId); // �����߳�
	//CloseHandle(hThread);

	printf("��ʼ�ɼ�\n");
}


void CSPM_CameraControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	//if (nIDEvent == TIMER_ROS_PUBLIS)
	//{
	//	cmd_vel_pub.publish(&twist_msg);//ros�ڵ㷢����Ϣ
	//	nh.spinOnce();
	//}

	if (TIMER_CAMERA1_START == nIDEvent)
	{
		if (g_iImageDataWriteStatus == CAMERA_1_WRITEDONE)
		{	
			g_bStartToWrite = false;
			printf("���1д��ɣ����2��ʼ\n");				
			doOperateCamera(1,false);//���1ֹͣ�ɼ�
			doOperateCamera(2,true);//���2�����ɼ�
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
			doOperateCamera(2,false);//���2ֹͣ�ɼ�
			fclose(g_pFileImage);
			printf("���2д��ɣ�����\n");
			KillTimer(TIMER_CAMERA2_START);

			endTime = GetTickCount();

			printf("�ɼ�����ʱ%d ms",endTime-startTime);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strButtonText;
	GetDlgItem(IDC_BUTTON_START1)->GetWindowText(strButtonText);

	if(!m_pArrayCams[0])
		return;

	if (strButtonText.Compare(_T("start1")) == 0)
	{
		GetDlgItem(IDC_BUTTON_START1)->SetWindowText(_T("stop1"));
	
		m_pArrayCams[0]->StartCap();
	}
	else
	{
		GetDlgItem(IDC_BUTTON_START1)->SetWindowText(_T("start1"));
		m_pArrayCams[0]->StopCap();
	}
}


// ���������no �����ţ�bOpen ������ʽ��falseֹͣ�ɼ���true�����ɼ���
void CSPM_CameraControlDlg::doOperateCamera(int no, bool bOpen)
{
	if (no<1 || no>8)
	{
		printf("����������!������Χ��1-8��");
		return;
	}

	if (!m_pArrayCams[no-1])
	{
		printf("���δ�򿪣�");
		return;
	}

	bOpen?m_pArrayCams[no-1]->StartCap():m_pArrayCams[no-1]->StopCap();
}

LRESULT  CSPM_CameraControlDlg::OnControlCamera(WPARAM wp,LPARAM lp)
{
	if (wp > 0)
	{
		doOperateCamera(wp,false);//ֹͣ�ɼ�
	}

	if (lp > 0)
	{
		doOperateCamera(lp,true);
		g_bStartToWrite = true;
	}
	return 0;
}