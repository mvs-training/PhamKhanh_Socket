#include "tcp.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#define SERVER_PORT 5500
#define SERVER_PORT1 5501
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048
using namespace std;

int tcp::tcp_recv(void)
{
	//Step 1: Inittiate Winsock
	WSADATA wsaData;
	WORD wversion = MAKEWORD(2,2);
	if(WSAStartup(wversion, &wsaData))
	printf("Version is not supported\n");
	//Step 2: Construct socket
	SOCKET client;
	client = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//(optional) Set time-out for receiving

	int tv = 10000; //Time-out interval: 10000ms
	setsockopt(client, SOL_SOCKET, SO_RCVTIMEO,(const char*)(&tv), sizeof(int));
	//Step 3: Specify server address
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	//Step 4: Request to connect server
	if(connect(client, (sockaddr *) &serverAddr, sizeof(serverAddr)))
	{
		printf("Error! Cannot connect server. %d",WSAGetLastError());
		_getch();
		return 0;
	}
	printf("Connected server!\n");
	//Step 5: Communicate with server
	char buff[BUFF_SIZE];
	int ret;

	//Receive echo message
	ret = recv(client, buff, BUFF_SIZE, 0);
	if(ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
			printf("Time-out!");
		else
			printf("Error! Cannot receive message.");
	}
	else if (strlen(buff) > 0)
	{
	buff[ret] = 0;
	printf("Receive from server[%s:%d] %s\n",inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port),buff);
	}
	//Step 6: Close socket
	closesocket(client);
	//Step 7: Terminate Winsock
	WSACleanup();
	_getch();
	return 0;
}

int tcp::tcp_send(char buff[])
{
	//Step 1: Inittiate Winsock
	WSADATA wsaData;
	WORD wversion = MAKEWORD(2,2);
	if(WSAStartup(wversion, &wsaData))
	printf("Version is not supported\n");
	//Step 2: Construct socket
	SOCKET client;
	client = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//(optional) Set time-out for receiving

	int tv = 10000; //Time-out interval: 10000ms
	setsockopt(client, SOL_SOCKET, SO_RCVTIMEO,(const char*)(&tv), sizeof(int));
	//Step 3: Specify server address
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	//Step 4: Request to connect server
	if(connect(client, (sockaddr *) &serverAddr, sizeof(serverAddr)))
	{
		printf("Error! Cannot connect server. %d",WSAGetLastError());
		_getch();
		return 0;
	}
	//Step 5: Communicate with server

	int ret;
	//Send message
	ret = send(client, buff, strlen(buff), 0);
	if(ret == SOCKET_ERROR)
	printf("Error! Cannot send mesage.");

	//Receive echo message
	ret = recv(client, buff, BUFF_SIZE, 0);
	if(ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
			printf("Time-out!");
		
	}
	else if (strlen(buff) > 0)
	{
	buff[ret] = 0;
	printf("Receive from server[%s:%d] %s\n",inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port),buff);
	}
	
	//Step 6: Close socket
	closesocket(client);
	//Step 7: Terminate Winsock
	WSACleanup();
	_getch();
	return 0;
}




tcp::~tcp(void)
{
}
