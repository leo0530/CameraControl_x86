
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// SPM_CameraControl.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

FILE *g_pFileImage = NULL;//ͼ������д���ļ�
bool g_bStartToWrite = false;///��ʼ�ɼ�
int  g_iFrmNumsIsDone = 0;//�Ѿ�д��ɵ�֡��
int  g_iImageDataWriteStatus = -1;