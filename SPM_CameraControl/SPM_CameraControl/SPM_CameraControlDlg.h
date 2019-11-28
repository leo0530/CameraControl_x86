
// SPM_CameraControlDlg.h : ͷ�ļ�
//

#pragma once

#include "XCamCtrl.h"
#include "UDPClientClass.h"
#include "afxwin.h"

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") 

#define WM_SAVEIMAGE   WM_USER + 1000
#define WM_UPDATEIMAGE WM_USER + 1001

#define PICTUREWIDTH  640
#define PICTUREHEIGHT 480
#define ROS_SERVER_IP "192.168.0.150"

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
	std::vector<UINT64> m_CameraInfoList;//����б�

	int m_iSelectCameraId;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	LRESULT OnSaveImage(WPARAM, LPARAM);

	void OpenCamera(void);
	void CloseCamera(void);

	afx_msg void OnBnClickedButtonSave();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SaveImage(int index);
	afx_msg void OnBnClickedRadioId1();
	afx_msg void OnBnClickedRadioId2();
	afx_msg void OnBnClickedRadioId3();
	afx_msg void OnBnClickedRadioId4();
	afx_msg void OnBnClickedRadioId5();
	afx_msg void OnBnClickedRadioId6();
	afx_msg void OnBnClickedRadioId7();
	afx_msg void OnBnClickedRadioId8();
	bool StartCamera(int index,bool bOpen);
	void StopCamera(int index);
//	void InitRosClient(void);
};

