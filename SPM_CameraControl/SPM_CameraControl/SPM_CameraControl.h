
// SPM_CameraControl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSPM_CameraControlApp:
// �йش����ʵ�֣������ SPM_CameraControl.cpp
//

class CSPM_CameraControlApp : public CWinApp
{
public:
	CSPM_CameraControlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	bool initSocket(void);
	void closeSocket(void);
	virtual int ExitInstance();
};

extern CSPM_CameraControlApp theApp;