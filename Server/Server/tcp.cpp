#include "tcp.h"
#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include "Controller.h"
#define SERVER_PORT 5500
#define SERVER_PORT1 5501
#define SERVER_PORT2 5502
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048
char buff[BUFF_SIZE];
char buff1[BUFF_SIZE][BUFF_SIZE];
char buff2[BUFF_SIZE][BUFF_SIZE];
int n = 0;
int m = 0;
Controller cl1;
int tcp::tcp_recv(void)
{
	n=0;
	m=0;
	//Step 1: Initiate Winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	if(WSAStartup(wVersion, &wsaData))
	printf("Version is not supported\n");
	//Step 2: Construct socket
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//Step 3: Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	if(bind(listenSock,(sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
	printf("Error! Cannot bind this address.");
	_getch();
	return 0;
	}
	//Step 4: Listen request from client
	if(listen(listenSock,10)){

	printf("Error! Cannot listen.");
	_getch();
	return 0;
	}
	printf("Server started!");
	//Step 5: Communicate with client
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	while(1){
	SOCKET connSock;
	//accept request
	connSock = accept(listenSock, (sockaddr *) & clientAddr, &clientAddrLen);
	//receive message from client
	
	int ret; 
	ret = recv(connSock, buff, BUFF_SIZE, 0);
	if(ret == SOCKET_ERROR){
	printf("Error : %", WSAGetLastError());
	break;
	}
	else if (strlen(buff) > 0){
	buff[ret] = 0;
	printf("\nReceive from client[%s:%d]: %s",inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port),buff);
	//CHECK buff => SignUp ,SignIn
	if(buff[0] == '1'&& buff[1] =='\0')
	{
		//Echo to client
	char buff_echo[] = {'O','K','\0'};
	ret = send(connSock, buff_echo, strlen(buff_echo), 0);
	if(ret == SOCKET_ERROR)
	printf("Error: %", WSAGetLastError());
	closesocket(connSock);
	closesocket(listenSock);
	WSACleanup();
	tcp_recv1();
	}
	if(buff[0] == '2'&& buff[1] =='\0')
	{
		//Echo to client
	char buff_echo[] = {'O','K','\0'};
	ret = send(connSock, buff_echo, strlen(buff_echo), 0);
	if(ret == SOCKET_ERROR)
	printf("Error: %", WSAGetLastError());
	closesocket(connSock);
	closesocket(listenSock);
	WSACleanup();
	tcp_recv2();
	}
	
	} 
		
	}
	//else(buff[1] == '2'&& buff[2] =='\0')
	//{
	//	//Echo to client
	//char buff_echo[] = {'O','K','\0'};
	//ret = send(connSock, buff_echo, strlen(buff_echo), 0);
	//if(ret == SOCKET_ERROR)
	//printf("Error: %", WSAGetLastError());
	//}
	//	closesocket(connSock);
	//} //end accepting
	////Step 5: Close socket
	//	closesocket(listenSock);
	////Step 6: Terminate Winsock
	//	WSACleanup();
	//	tcp_recv2();
	//}
	
	return 0;

}

int tcp::tcp_recv1(void)
{
	n=0;
	//Step 1: Initiate Winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	if(WSAStartup(wVersion, &wsaData))
	printf("Version is not supported\n");
	//Step 2: Construct socket
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//Step 3: Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	if(bind(listenSock,(sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
	printf("Error! Cannot bind this address.");
	_getch();
	return 0;
	}
	//Step 4: Listen request from client
	if(listen(listenSock,10)){

	printf("Error! Cannot listen.");
	_getch();
	return 0;
	}
	printf("\nServer started!");
	
	//Step 5: Communicate with client
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	do{
	SOCKET connSock;
	//accept request
	connSock = accept(listenSock, (sockaddr *) & clientAddr, &clientAddrLen);
	//receive message from client
	
	int ret; 
	
	ret = recv(connSock, buff1[n], BUFF_SIZE, 0);
	if(ret == SOCKET_ERROR){
	printf("Error : %", WSAGetLastError());
	break;
	}
	else if (strlen(buff1[n]) > 0){
	printf("\nReceive from client[%s:%d]: %s",inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port),buff1[n]);
	//Echo to client
	char buff3[] = {'O','K','\0'};
	ret = send(connSock, buff3, strlen(buff3), 0);
	n++;
	if(ret == SOCKET_ERROR)
	printf("Error: %", WSAGetLastError());
	}
	
	closesocket(connSock);
	}while(n!=6);//end accepting
	cl1.SignUp(buff1[n-6],buff1[n-5],buff1[n-4],buff1[n-3],buff1[n-2],buff1[n-1]);
	//Step 5: Close socket
	closesocket(listenSock);
	//Step 6: Terminate Winsock
	WSACleanup();
	tcp_recv();
	return 0;

}


int tcp::tcp_recv2(void)
{
	n =0;
	//Step 1: Initiate Winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	if(WSAStartup(wVersion, &wsaData))
	printf("Version is not supported\n");
	//Step 2: Construct socket
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//Step 3: Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	if(bind(listenSock,(sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
	printf("Error! Cannot bind this address.");
	_getch();
	return 0;
	}
	//Step 4: Listen request from client
	if(listen(listenSock,10)){

	printf("Error! Cannot listen.");
	_getch();
	return 0;
	}
	printf("\nServer started!");
	
	
	//Step 5: Communicate with client
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	
	do{
	SOCKET connSock;
	//accept request
	connSock = accept(listenSock, (sockaddr *) & clientAddr, &clientAddrLen);
	//receive message from client
	
	int ret; 
	
	ret = recv(connSock, buff1[n], BUFF_SIZE, 0);
	if(ret == SOCKET_ERROR){
	printf("Error : %", WSAGetLastError());
	break;
	}
	else if (strlen(buff1[n]) > 0){
	printf("\nReceive from client[%s:%d]: %s",inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port),buff1[n]);
	//Echo to client
	char buff3[] = {'O','K','\0'};
	ret = send(connSock, buff3, strlen(buff3), 0);
	n++;

	if(ret == SOCKET_ERROR)
	printf("Error: %", WSAGetLastError());
	}
	if(n==2)
	{
		char result[]={cl1.SignIn(buff2[m-2],buff2[m-1]),'\0'};
		char result1[]={"Dang nhap thanh cong"};
		char result2[]={"Dang nhap that bai"};
		if(result[0] == 't')
			int ret2 = send(connSock, result1, strlen(result1), 0);
		else
			int ret2 = send(connSock, result2, strlen(result2), 0);
	}
	closesocket(connSock);
	}while(n!=2);

	//end accepting
	//Step 5: Close socket
	closesocket(listenSock);
	//Step 6: Terminate Winsock
	WSACleanup();
	tcp_recv();
	return 0;

}


tcp::~tcp(void)
{
}
