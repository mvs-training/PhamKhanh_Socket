#include "View.h"
#include "Controller.h"
#include "Model.h"
#include <iostream>
#include "tcp.h"
#include <stdlib.h>
#define BUFF_SIZE 2048
using namespace std;
Controller controller1;
char choice_v;
tcp tcp2;
void View::send_fr() {
	int chon;
	cout << "-------MENU ------\n"
                "1.SEND MESS TO FRIEND\n"
                "2.EXIT\n"
                "-----------------------\n";
	while (1)
	{
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			controller1.Detail_Reply(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			return;
		}
	}
}
void  View::Ctrl_R() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.Reply Friend\n"
                "2.EXIT\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			controller1.Reply(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			return;
		}
	}
}
void View::send() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.SEND MESS\n"
                "2.Ctrl L To SEND\n"
                "3.Exit\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			controller1.SendMess(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			controller1.SendMess_ctr_l(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 3:
			return;
		}
	}
}
void View::showmess() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.SEND MESS\n"
                "2.RECEIVED MESSAGE\n"
                "3.EXIT\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			controller1.ShowMess_send(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			controller1.ShowMess_rec(controller1.id);
			cout << "-----------------------" << endl;
			break;
		case 3:
			return;
		}
	}
}
void View::login() {
	int chon;

	while (1)
	{

		cout << "-------MENU ------\n"
                "1.Show Mess\n"
                "2.Detail Mess\n"
                "3.Send Mess\n"
                "4.Add Friend\n"
                "5.Show Friend\n"
                "6.Block Friend\n"
                "7.Update Friend\n"
                "8.Detail Friend\n"
                "9.Exit\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
			case 1:
				showmess();
				break;
			case 2:
				controller1.ShowMessDetail(controller1.id);
				if (controller1.Detail) {
					Ctrl_R();
				}
				break;
			case 3:
				send();
				break;
			case 4:
				controller1.AddFriend(controller1.id);
				break;
			case 5:
				controller1.ShowFriend_ctr_C(controller1.id);
				break;
			case 6:
				controller1.BlockFriend(controller1.id);
				break;
			case 7:
				controller1.Update_fr(controller1.id);
				break;
			case 8:
				controller1.Detail_fr(controller1.id);
				if (controller1.Detail) {
					send_fr();
				}
				break;
			case 9:
				break;
			default:
				printf("\r\n>> ERROR, Reselect..");
				system("pause");
		}
		if (chon == 9)
		{
			break;
		}
	}
}


void View::print_menu() {
	cout << "----MESSENGER APP-----\n";
	cout << "1. SIGN UP\n";
	cout << "2. LOGIN\n";
	cout << "3. LOGOUT\n";
	cout << "4. EXIT\n";
	cout << "\nChoose: ";
}

void View::choose_menu()
{
label1:
	print_menu();
	fflush(stdin);
	cin>>choice_v;
	char buff[] = {choice_v,'\0'};
	switch (choice_v)
	{
	case '1':
		tcp2.tcp_send(buff);
		controller1.SignUp();
		system("cls");
		goto label1;
			break;
	case '2':
		tcp2.tcp_send(buff);
		controller1.SignIn();
		if (controller1.check) {
				login();
			}
			break;

	case 3:
		controller1.SignOut();
			break;
	case 4:
	default:
		cout<<"Khong hop le\n";
		break;
	}
	
	
}
