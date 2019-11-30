#include<Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class UDPServer{

private:

	WSADATA wsaData;

	SOCKET serverSocket;

	sockaddr_in serverSockAddr;

	

public:
	char buf[1024];

	UDPServer();

	void setSockAddr(const char *destAddr,const int destPort);

	void listen(const int port);

	int receive();

	~UDPServer();

};
extern char g_DataRecv[1024];