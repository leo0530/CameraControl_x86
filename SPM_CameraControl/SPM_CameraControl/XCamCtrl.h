// XCamCtrl.h: interface for the CXCamCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCAMCTRL_H__F347A89C_B186_49C3_8337_53C3098203DF__INCLUDED_)
#define AFX_XCAMCTRL_H__F347A89C_B186_49C3_8337_53C3098203DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>
using namespace std;
#include "API\XCCamAPI.h"
#pragma comment(lib,"XCCam.lib")

#define Max_Buffer 5

struct CameraInfo
{
public:
	CameraInfo(UINT64 UID, char* pModel)
		: m_UID(UID)
	{
		m_Model = pModel;
	}
	
	
	virtual ~CameraInfo(void)
	{
	}
	
	UINT64 GetUID(void) { return m_UID; }
	std::string& GetModel(void) { return m_Model; }
	
	
protected:
	UINT64 m_UID;
	std::string m_Model;
};

class CXCamCtrl  
{
public:
	CXCamCtrl(UINT64 ID);
	virtual ~CXCamCtrl();
public:
	int GetImageBufLen();
	static void GetCameraList(std::vector<UINT64>& List);

	void StopCamera();
	bool StartCamera(IMAGEFUNC func);

	HCAMERA m_hCamera;
	XCCAM_DEVINFO m_CameraInfo;
	HFEATURE m_hFeature;
	
	PBITMAPINFO m_pBitInfo;
	BYTE* m_pRGBData;

	int m_nRGBBufferLength;

	PBITMAPINFO GetBitmapInfo(void);
	BYTE* GetImageDataBuffer(void);
};
extern BYTE* g_pRGBData1;
extern BYTE* g_pRGBData2;
extern BYTE* g_pRGBData3;
extern BYTE* g_pRGBData4;
extern BYTE* g_pRGBData5;
extern BYTE* g_pRGBData6;
extern BYTE* g_pRGBData7;
extern BYTE* g_pRGBData8;

extern PBITMAPINFO g_pBitInfo1;
extern PBITMAPINFO g_pBitInfo2;
extern PBITMAPINFO g_pBitInfo3;
extern PBITMAPINFO g_pBitInfo4;
extern PBITMAPINFO g_pBitInfo5;
extern PBITMAPINFO g_pBitInfo6;
extern PBITMAPINFO g_pBitInfo7;
extern PBITMAPINFO g_pBitInfo8;

extern CXCamCtrl *g_pCamera1;//相机1
extern CXCamCtrl *g_pCamera2;//相机2
extern CXCamCtrl *g_pCamera3;//相机3
extern CXCamCtrl *g_pCamera4;//相机4
extern CXCamCtrl *g_pCamera5;//相机5
extern CXCamCtrl *g_pCamera6;//相机6
extern CXCamCtrl *g_pCamera7;//相机7
extern CXCamCtrl *g_pCamera8;//相机8

extern bool g_bIsCamera1Open;
extern bool g_bIsCamera2Open;
extern bool g_bIsCamera3Open;
extern bool g_bIsCamera4Open;
extern bool g_bIsCamera5Open;
extern bool g_bIsCamera6Open;
extern bool g_bIsCamera7Open;
extern bool g_bIsCamera8Open;

extern bool g_bIsCameta1Stop;
extern bool g_bIsCameta2Stop;
extern bool g_bIsCameta3Stop;
extern bool g_bIsCameta4Stop;
extern bool g_bIsCameta5Stop;
extern bool g_bIsCameta6Stop;
extern bool g_bIsCameta7Stop;
extern bool g_bIsCameta8Stop;
#endif // !defined(AFX_XCAMCTRL_H__F347A89C_B186_49C3_8337_53C3098203DF__INCLUDED_)
