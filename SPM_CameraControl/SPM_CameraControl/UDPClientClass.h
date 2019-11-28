#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll


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
	��UDP
	����ֵΪtrue��򿪣������޷���������
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
		curHwnd = hwnd;					//�󶨾����UDP_READ��Ϣ
		if (WSAAsyncSelect(sckClient, curHwnd, UDP_READ, FD_READ) == SOCKET_ERROR)
		{
			return FALSE;
		}
		int nRecvBuf =READ_MAX_BUFFER;	//���ܻ���������Ϊ32K
		setsockopt(sckClient, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf,sizeof(int));
		return TRUE;
	}
 
	/**
	��������
	data:�ǽ������ݵ���ָ��
	addrFrom:����˵�IP��ַ�˿ڽṹָ��
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
	��������
	*/
	int write(UINT8 *data, UINT32 len)
	{
		DWORD dwSend;
		writeWsabuf.buf = (char *)data;
		writeWsabuf.len = len;
		if (sckClient == INVALID_SOCKET)//���û�д�UDP�����޷��������ݣ�ֱ�ӷ���0						
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
	�ж��Ƿ��UDP
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
	�ر�UDP
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
