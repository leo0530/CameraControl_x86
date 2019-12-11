
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include <string>
#include <stdio.h>
#include "ros.h"
#include <geometry_msgs/Twist.h>
#include <windows.h>
using namespace std;

#include <vector>
#include "API\XCCamAPI.h"
#pragma comment(lib,"XCCam.lib")

#include "CGlobal.h"//������������

#define Max_Buffer      5  //����ɼ����֡��
#define FRAME_NUM_WRITE 3  //д���ļ�����֡��
//#if MY_DEBUG      
//#pragma comment( linker, "/subsystem:console /entry:wWinMainCRTStartup" )      //���������д���
//#endif  
#pragma comment( linker, "/subsystem:console /entry:wWinMainCRTStartup" )    //���������д���
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

extern FILE *g_pFileImage;//ͼ������д���ļ�
extern bool g_bStartToWrite;///��ʼ�ɼ�
extern int  g_iFrmNumsIsDone;//�Ѿ�д��ɵ�֡��
extern int  g_iImageDataWriteStatus;
enum 
{
	CAMERA_1_WRITEDONE,//���1д���
	CAMERA_2_WRITEDONE,//���2д���
	CAMERA_3_WRITEDONE,//���3д���
	CAMERA_4_WRITEDONE,//���4д���
	CAMERA_5_WRITEDONE,//���5д���
	CAMERA_6_WRITEDONE,//���6д���
	CAMERA_7_WRITEDONE,//���7д���
	CAMERA_8_WRITEDONE //���8д���
};