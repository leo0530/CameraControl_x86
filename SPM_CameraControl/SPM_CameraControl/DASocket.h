#pragma once
#include <afxsock.h>
#define WM_RECVDATA WM_USER + 3000 //
class CDASocket :public CAsyncSocket 
{
public:
	CDASocket(void);
	~CDASocket(void);

	void OnReceive(int nErrorCode);
};

