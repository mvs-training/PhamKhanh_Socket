#include <iostream>
#include <string>
#include <ctime>
#include <sqlite3.h>
#include "Controller.h"
#include "Model.h"
#include <stdlib.h>
#include <Windows.h>
#include "View.h"
#include "tcp.h"
using namespace std;
int choice_m = 0;
View view1;
tcp tcp1;


DWORD WINAPI tcpip_recv(LPVOID arg){
	
	
		tcp1.tcp_recv();
		//Sleep(3000);

	return 0;
}

int main()
{
	view1.choose_menu();
	HANDLE hThread1 = CreateThread(NULL, 0, tcpip_recv, NULL, 0, NULL);

	WaitForSingleObject(hThread1, INFINITE);
	CloseHandle(hThread1);
	

	system("pause");
	return 0;
}