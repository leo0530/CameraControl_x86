#pragma once
#include "afxwin.h"


#define PICTUREWIDTH  640
#define PICTUREHEIGHT 480
// CCameraControlDlg 对话框

class CCameraControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraControlDlg)

public:
	CCameraControlDlg(UINT64 UID,int camNo, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraControlDlg();

// 对话框数据
	enum { IDD = IDD_CAMERA_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	PBITMAPINFO m_pBitInfo;
	BYTE* m_pRGBData;
	HCAMERA m_hCamera;
	XCCAM_DEVINFO m_CameraInfo;
	HFEATURE m_hFeature;
	HTREEITEM m_hitem;
	CBitmap m_RGBBmp;

	int m_iCamNo;//相机编号
	bool m_bCamIsCap;

	void StartCap();
	void StopCap();

//	LRESULT OnUpdateImage(WPARAM, LPARAM);

	afx_msg void OnDestroy();
	
//	afx_msg void OnBnClickedButton1();
//	afx_msg void OnBnClickedButton2();
	
	virtual BOOL OnInitDialog();
//	afx_msg void OnBnClickedButton3();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);

//	CMyDraw m_PictureBox;
//	afx_msg void OnBnClickedButtonCap();
};




