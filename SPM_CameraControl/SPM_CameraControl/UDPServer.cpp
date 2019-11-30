#include"UDPServer.h"

#include<iostream>
using namespace std;

char g_DataRecv[1024] = {0};
UDPServer::UDPServer()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	serverSocket = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);     
}
void UDPServer::listen(const int port)
{
	serverSockAddr.sin_family=AF_INET;
	serverSockAddr.sin_port=htons(port);
	serverSockAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(serverSocket, (SOCKADDR*)&serverSockAddr, sizeof(serverSockAddr));
}
int UDPServer::receive()
{
    int serverSockAddrSize =sizeof(serverSockAddr);
	int len = recvfrom(serverSocket, g_DataRecv, sizeof(g_DataRecv), 0,(SOCKADDR *)&serverSockAddr, &serverSockAddrSize);

	return len;
}
UDPServer::~UDPServer()
{
	closesocket(serverSocket);
	WSACleanup();

}
