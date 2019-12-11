
// SPM_CameraControlDlg.h : ͷ�ļ�
//

#pragma once

#include "afxwin.h"
#include "CameraControlDlg.h"

#define FRAME_NUMS        3   //����֡��
#define TIMER_ROS_PUBLIS  2   //ros������Ϣ��ʱ��
#define TIMER_CAMERA1_START 1024
#define TIMER_CAMERA2_START 1034
#define TIMER_CAMERA3_START 1044
#define TIMER_PERID  1000  //��ʱ������1.5s

// CSPM_CameraControlDlg �Ի���
class CSPM_CameraControlDlg : public CDialogEx
{
// ����
public:
	CSPM_CameraControlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SPM_CAMERACONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:

// ʵ��
protected:
	HICON m_hIcon;

	std::vector<UINT64> m_CameraInfoList;

	CCameraControlDlg* m_pArrayCams[8];

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();

	void InitRosClient(void);//��ʼ��ros�ڵ�

	void CreateCameraList(vector<UINT64>& List);//��������б�

	void OpenCamera(void);
	void CloseCamera(void);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedButtonStart1();

	// ���������no �����ţ�bOpen ������ʽ��falseֹͣ�ɼ���true�����ɼ���
	void doOperateCamera(int no, bool bOpen);

	LRESULT OnControlCamera(WPARAM wp,LPARAM lp);//�����Զ�����Ϣ��wp���ڹر������lp���ڿ������
};

