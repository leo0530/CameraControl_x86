#include "StdAfx.h"
#include "DASocket.h"

CDASocket::CDASocket(void)
{
	AfxSocketInit();
}


CDASocket::~CDASocket(void)
{
}

extern HWND g_hWnd;//�Ի�����
void CDASocket::OnReceive(int nErrorCode) //OnReceive �����������ݴ���
{
	//TODO: Add your specialized code here and/or call the
	char buff[256] ={0} ;
	 int ret = 0;
	 ret = Receive(buff,256);

	 if (ret == ERROR)
	 {
		 TRACE("error");
	 }
	 else
	 {
		 TRACE(buff);
		 time_t timep;
		 time(&timep);//��ȡʱ���
		 
		 UINT32 pos = (10<<16)|20;
		
		 PostMessage(g_hWnd,WM_RECVDATA,timep,pos);
		 CAsyncSocket::OnReceive(nErrorCode);
	 }
}