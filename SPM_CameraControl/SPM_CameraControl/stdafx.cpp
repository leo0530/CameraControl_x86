
// stdafx.cpp : 只包括标准包含文件的源文件
// SPM_CameraControl.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

FILE *g_pFileImage = NULL;//图像数据写入文件
bool g_bStartToWrite = false;///开始采集
int  g_iFrmNumsIsDone = 0;//已经写完成的帧数
int  g_iImageDataWriteStatus = -1;