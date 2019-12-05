
// SPM_CameraControlDlg.h : 头文件
//

#pragma once

#include "XCamCtrl.h"
#include "afxwin.h"
#include "DASocket.h"

#define WM_SAVEIMAGE   WM_USER + 1000
#define WM_UPDATEIMAGE WM_USER + 1001
#define WM_CONNECT     WM_USER + 2000

#define PICTUREWIDTH  640
#define PICTUREHEIGHT 480
#define ROS_SERVER_IP "192.168.0.150"

#define FRAME_NUMS  3 //图像数据存储帧数

class CSPM_CameraControlDlg;

class CMyDraw : public CStatic
{
public:
	

	CMyDraw()
		: m_pView()
	{
	}

	void Set_CCameraView( CSPM_CameraControlDlg *pView )
	{
		m_pView = pView;
	}

	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	CSPM_CameraControlDlg *m_pView;
};

// CSPM_CameraControlDlg 对话框
class CSPM_CameraControlDlg : public CDialogEx
{
// 构造
public:
	CSPM_CameraControlDlg(CWnd* pParent = NULL);	// 标准构造函数

	void WriteDataToFile(int iCameraNo);//相机数据写入文件

// 对话框数据
	enum { IDD = IDD_SPM_CAMERACONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	std::vector<UINT64> m_CameraInfoList;//相机列表

	int m_iSelectCameraId;

	FILE * m_FileToWrite;

	CDASocket *udpServ;//异步通讯
// 实现
protected:
	HICON m_hIcon;

//	UDPClientClass udpCliCls;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	CMyDraw m_Image;
	afx_msg void OnBnClickedButtonCapture();
	CButton m_btnCapture;
	void ShowImage(void);

	LRESULT OnUpdateImage(WPARAM, LPARAM);
	LRESULT OnSaveImage(WPARAM wParam, LPARAM lParam);
	LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);

	void OpenCamera(void);
	void CloseCamera(void);

	afx_msg void OnBnClickedButtonSave();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SaveImage(int index);

	bool StartCamera(int index,bool bOpen);
	void StopCamera(int index);

	

	void InitRosClient(void);//ligy 20191115 add.Ros客户端设置，设置为订阅模式
	afx_msg void OnBnClickedButton1();
};

//extern HWND g_MainWnd;// = NULL;//对话框句柄
extern HWND g_hWnd;//对话框句柄