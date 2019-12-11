
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include <string>
#include <stdio.h>
#include "ros.h"
#include <geometry_msgs/Twist.h>
#include <windows.h>
using namespace std;

#include <vector>
#include "API\XCCamAPI.h"
#pragma comment(lib,"XCCam.lib")

#include "CGlobal.h"//公共帮助函数

#define Max_Buffer      5  //相机采集最大帧数
#define FRAME_NUM_WRITE 3  //写入文件数据帧数
//#if MY_DEBUG      
//#pragma comment( linker, "/subsystem:console /entry:wWinMainCRTStartup" )      //调用命令行窗口
//#endif  
#pragma comment( linker, "/subsystem:console /entry:wWinMainCRTStartup" )    //调用命令行窗口
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

extern FILE *g_pFileImage;//图像数据写入文件
extern bool g_bStartToWrite;///开始采集
extern int  g_iFrmNumsIsDone;//已经写完成的帧数
extern int  g_iImageDataWriteStatus;
enum 
{
	CAMERA_1_WRITEDONE,//相机1写完成
	CAMERA_2_WRITEDONE,//相机2写完成
	CAMERA_3_WRITEDONE,//相机3写完成
	CAMERA_4_WRITEDONE,//相机4写完成
	CAMERA_5_WRITEDONE,//相机5写完成
	CAMERA_6_WRITEDONE,//相机6写完成
	CAMERA_7_WRITEDONE,//相机7写完成
	CAMERA_8_WRITEDONE //相机8写完成
};