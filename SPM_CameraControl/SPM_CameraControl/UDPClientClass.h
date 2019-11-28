#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


#define UDP_READ	WM_USER + 3
#define READ_MAX_BUFFER	32 * 1024
class UDPClientClass
{
private:
	SOCKADDR_IN addrTo;
	SOCKET sckClient;
	WSABUF writeWsabuf;
	WSABUF readWsabuf;
	HWND curHwnd;
public:
	UDPClientClass()
	{
		sckClient = INVALID_SOCKET;
	}
 
	~UDPClientClass()
	{
		Close();
	}
 
	BOOL Init()
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
		wVersionRequested = MAKEWORD(2, 2);
		err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
			return false;
		}
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			WSACleanup();
			return FALSE;
		}
		return true;
	}
 
	/**
	打开UDP
	返回值为true则打开，否则无法发送数据
	*/
	BOOL Open(const char *ip, UINT16 port, HWND hwnd)
	{
		if (!Init())
		{
			return FALSE;
		}
		sckClient = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, 0);
		if (sckClient == INVALID_SOCKET)
		{
			return FALSE;
		}
		addrTo.sin_addr.S_un.S_addr = inet_addr(ip);
		addrTo.sin_family = AF_INET;
		addrTo.sin_port = htons(port);
		curHwnd = hwnd;					//绑定句柄和UDP_READ消息
		if (WSAAsyncSelect(sckClient, curHwnd, UDP_READ, FD_READ) == SOCKET_ERROR)
		{
			return FALSE;
		}
		int nRecvBuf =READ_MAX_BUFFER;	//接受缓冲区设置为32K
		setsockopt(sckClient, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf,sizeof(int));
		return TRUE;
	}
 
	/**
	接受数据
	data:是接受数据的首指针
	addrFrom:服务端的IP地址端口结构指针
	*/
	DWORD read(UINT8 *data, SOCKADDR_IN *addrFrom, WPARAM w, LPARAM l)
	{
		switch (LOWORD(l))
		{
		case FD_READ:
			DWORD dwRead;
			DWORD dwFlag = 0;
			readWsabuf.len = READ_MAX_BUFFER;
			readWsabuf.buf = (char *)data;
			int len = sizeof(SOCKADDR);
			if (WSARecvFrom(sckClient, &readWsabuf, 1, &dwRead, &dwFlag, (SOCKADDR *)addrFrom, &len, NULL, NULL) == SOCKET_ERROR)
			{
				return 0;
			}
			return dwRead;
		}
		return 0;
	}
 
	/**
	发送数据
	*/
	int write(UINT8 *data, UINT32 len)
	{
		DWORD dwSend;
		writeWsabuf.buf = (char *)data;
		writeWsabuf.len = len;
		if (sckClient == INVALID_SOCKET)//如果没有打开UDP，则无法发送数据，直接返回0						
		{
			return 0;
		}
		if (WSASendTo(sckClient, &writeWsabuf, 1, &dwSend, 0, (SOCKADDR *)&addrTo, sizeof(SOCKADDR), NULL, NULL) == SOCKET_ERROR)
		{
			return 0;
		}
		return dwSend;
	}
 
	/**
	判断是否打开UDP
	*/
	BOOL IsOpen()
	{
		if (sckClient != INVALID_SOCKET)
		{
			return TRUE;
		}
		return FALSE;
	}
 
	/**
	关闭UDP
	*/
	void Close()
	{
		if (sckClient != INVALID_SOCKET)
		{
			WSACleanup();
			sckClient = INVALID_SOCKET;
		}
	}
};
