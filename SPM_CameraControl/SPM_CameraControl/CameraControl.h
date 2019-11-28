#pragma once
#include "XCamCtrl.h"
class CCameraControl
{
public:
	CCameraControl(void);
	~CCameraControl(void);
public:
	BYTE* m_pRGBData1;
	BYTE* m_pRGBData2;
	BYTE* m_pRGBData3;
	BYTE* m_pRGBData4;
	BYTE* m_pRGBData5;
	BYTE* m_pRGBData6;
	BYTE* m_pRGBData7;
	BYTE* m_pRGBData8;

	PBITMAPINFO m_pBitInfo1;
	PBITMAPINFO m_pBitInfo2;
	PBITMAPINFO m_pBitInfo3;
	PBITMAPINFO m_pBitInfo4;
	PBITMAPINFO m_pBitInfo5;
	PBITMAPINFO m_pBitInfo6;
	PBITMAPINFO m_pBitInfo7;
	PBITMAPINFO m_pBitInfo8;

	CBitmap m_RGBBmp1;;
	CBitmap m_RGBBmp2;
	CBitmap m_RGBBmp3;
	CBitmap m_RGBBmp4;
	CBitmap m_RGBBmp5;
	CBitmap m_RGBBmp6;
	CBitmap m_RGBBmp7;
	CBitmap m_RGBBmp8;

	std::vector<UINT64> m_CameraInfoList;//����б�

	CXCamCtrl *m_pCamera1;//���1
	CXCamCtrl *m_pCamera2;//���2
	CXCamCtrl *m_pCamera3;//���3
	CXCamCtrl *m_pCamera4;//���4
	CXCamCtrl *m_pCamera5;//���5
	CXCamCtrl *m_pCamera6;//���6
	CXCamCtrl *m_pCamera7;//���7
	CXCamCtrl *m_pCamera8;//���8

	bool m_bIsCamera1Open;
	bool m_bIsCamera2Open;
	bool m_bIsCamera3Open;
	bool m_bIsCamera4Open;
	bool m_bIsCamera5Open;
	bool m_bIsCamera6Open;
	bool m_bIsCamera7Open;
	bool m_bIsCamera8Open;

};

