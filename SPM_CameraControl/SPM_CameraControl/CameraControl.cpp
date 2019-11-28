#include "stdafx.h"
#include "CameraControl.h"


CCameraControl::CCameraControl(void)
{
	//图像数据指针
	m_pRGBData1 = NULL;
	m_pRGBData2 = NULL;
	m_pRGBData3 = NULL;
	m_pRGBData4 = NULL;
	m_pRGBData5 = NULL;
	m_pRGBData6 = NULL;
	m_pRGBData7 = NULL;
	m_pRGBData8 = NULL;
	//相机控制
	m_pCamera1 = NULL;
	m_pCamera2 = NULL;
	m_pCamera3 = NULL;
	m_pCamera4 = NULL;
	m_pCamera5 = NULL;
	m_pCamera6 = NULL;
	m_pCamera7 = NULL;
	m_pCamera8 = NULL;

	m_pBitInfo1 = NULL;
	m_pBitInfo2 = NULL;
	m_pBitInfo3 = NULL;
	m_pBitInfo4 = NULL;
	m_pBitInfo5 = NULL;
	m_pBitInfo6 = NULL;
	m_pBitInfo7 = NULL;
	m_pBitInfo8 = NULL;

	m_bIsCamera1Open = false;
	m_bIsCamera2Open = false;
	m_bIsCamera3Open = false;
	m_bIsCamera4Open = false;
	m_bIsCamera5Open = false;
	m_bIsCamera6Open = false;
	m_bIsCamera7Open = false;
	m_bIsCamera8Open = false;
}


CCameraControl::~CCameraControl(void)
{
	if (m_pCamera1)
	{
		delete m_pCamera1;
	}
	if (m_pCamera2)
	{
		delete m_pCamera2;
	}
	if (m_pCamera3)
	{
		delete m_pCamera4;
	}
	if (m_pCamera5)
	{
		delete m_pCamera5;
	}
	if (m_pCamera6)
	{
		delete m_pCamera6;
	}
	if (m_pCamera7)
	{
		delete m_pCamera7;
	}
	if (m_pCamera8)
	{
		delete m_pCamera8;
	}

	if (m_pRGBData1)
	{
		delete []m_pRGBData1;
	}

	if (m_pRGBData2)
	{
		delete []m_pRGBData2;
	}


	if (m_pRGBData1)
	{
		delete []m_pRGBData1;
	}
	if (m_pRGBData3)
	{
		delete []m_pRGBData3;
	}
	if (m_pRGBData4)
	{
		delete []m_pRGBData4;
	}
	if (m_pRGBData5)
	{
		delete []m_pRGBData5;
	}
	if (m_pRGBData6)
	{
		delete []m_pRGBData6;
	}
	if (m_pRGBData7)
	{
		delete []m_pRGBData7;
	}
	if (m_pRGBData7)
	{
		delete []m_pRGBData7;
	}
}
