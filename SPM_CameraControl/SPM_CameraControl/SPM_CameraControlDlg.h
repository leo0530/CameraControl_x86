
// SPM_CameraControlDlg.h : 头文件
//

#pragma once

#include "afxwin.h"
#include "CameraControlDlg.h"

#define FRAME_NUMS        3   //保存帧数
#define TIMER_ROS_PUBLIS  2   //ros发布消息定时器
#define TIMER_CAMERA1_START 1024
#define TIMER_CAMERA2_START 1034
#define TIMER_CAMERA3_START 1044
#define TIMER_PERID  1000  //定时器周期1.5s

// CSPM_CameraControlDlg 对话框
class CSPM_CameraControlDlg : public CDialogEx
{
// 构造
public:
	CSPM_CameraControlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SPM_CAMERACONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:

// 实现
protected:
	HICON m_hIcon;

	std::vector<UINT64> m_CameraInfoList;

	CCameraControlDlg* m_pArrayCams[8];

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();

	void InitRosClient(void);//初始化ros节点

	void CreateCameraList(vector<UINT64>& List);//创建相机列表

	void OpenCamera(void);
	void CloseCamera(void);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedButtonStart1();

	// 相机操作，no 相机编号，bOpen 操作方式（false停止采集，true启动采集）
	void doOperateCamera(int no, bool bOpen);

	LRESULT OnControlCamera(WPARAM wp,LPARAM lp);//控制自定义消息，wp用于关闭相机，lp用于开启相机
};

