
// SPM_CameraControlDlg.h : ͷ�ļ�
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

#define FRAME_NUMS  3 //ͼ�����ݴ洢֡��

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

	void WriteDataToFile(int iCameraNo);//�������д���ļ�

// �Ի�������
	enum { IDD = IDD_SPM_CAMERACONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	std::vector<UINT64> m_CameraInfoList;//����б�

	int m_iSelectCameraId;

	FILE * m_FileToWrite;

	CDASocket *udpServ;//�첽ͨѶ
// ʵ��
protected:
	HICON m_hIcon;

//	UDPClientClass udpCliCls;

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
	LRESULT OnSaveImage(WPARAM wParam, LPARAM lParam);
	LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);

	void OpenCamera(void);
	void CloseCamera(void);

	afx_msg void OnBnClickedButtonSave();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SaveImage(int index);

	bool StartCamera(int index,bool bOpen);
	void StopCamera(int index);

	

	void InitRosClient(void);//ligy 20191115 add.Ros�ͻ������ã�����Ϊ����ģʽ
	afx_msg void OnBnClickedButton1();
};

//extern HWND g_MainWnd;// = NULL;//�Ի�����
extern HWND g_hWnd;//�Ի�����