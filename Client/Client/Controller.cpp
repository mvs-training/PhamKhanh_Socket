#include "Controller.h"
#include "View.h"
#include "Model.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <sqlite3.h>
#include "tcp.h"
using namespace std;
Model model1;
Controller controller2;
tcp tcp3;
void Controller::SignUp() {
	username = new (char);
	password = new char;
	birthday = new char;
	fullname = new char;
	sex=new char;
	address= new char;
	cout << "Username:";
	fflush(stdin);
	cin >> username;
	tcp3.tcp_send(username);
	cout << "Password:";
	fflush(stdin);
	cin >> password;
	tcp3.tcp_send(password);
	cout << "Sex:";
	fflush(stdin);
	cin >> sex;
	tcp3.tcp_send(sex);
	cout << "Birthday:";
	fflush(stdin);
	cin >> birthday;
	tcp3.tcp_send(birthday);
	cout << "Fullname:";
	fflush(stdin);
    cin.getline(fullname,30);
	tcp3.tcp_send(fullname);
	cout << "Address:";
	fflush(stdin);
    cin.getline(address,30);
	tcp3.tcp_send(address);
	Model conn;
	conn.Open();
	if (conn.Select_all(conn.db,username)>0) {
		cout << "user exist" << endl;
	}
	else
	{
		conn.SQL_Reg(conn.db, username, password, sex, birthday, fullname, address);
		int id_mask = conn.Select_mask(conn.db);
		conn.Insert_maskuser(conn.db, id_mask, fullname,sex, address);
		cout << "DONE" << endl;
		system("pause");
	}
}
void Controller::SignIn() {
	username = new char;
	password = new char;

	cout << "username: ";
	fflush(stdin);
	cin >> username;
	tcp3.tcp_send(username);
	cout << "password: ";
	fflush(stdin);
	cin >> password;
	tcp3.tcp_send(password);
	Model conn;
	conn.Open();
	if (conn.SQL_login(conn.db,username,password)>0) {
		cout << "Login successfuly!\n";
		id = conn.SQL_login(conn.db, username, password);
		check = true;
		zID = id;
	}
	else {
		cout << "Login fail!\n";
		check = false;
		getch();
	}
}
void Controller::SignOut() {
	check = false;
	cout << "-----Please Login.-------\n";
}

void Controller::SendMess(int id) {
	if (check) {
		int id2;
		cout << "Receiver: ";
		char *frien;
		frien = new char;
		cin >> frien;
		Model conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0) {
			char *mess, *dt;
			mess = new char;
			dt = new char;
			if (conn.CheckBlock(conn.db, id, id2)) {
				cout << "====>You is blocked\n";
			}
			else {
				int tt = 1;
				conn.update_tt(conn.db, id, id2);
				cout << "Content: \n";
				cin.ignore();
				cin.getline(mess,100);
				time_t hientai = time(0);
				dt = ctime(&hientai);
				long int x;
				x = static_cast<int> (hientai);
				conn.WriteToMess(conn.db, id, id2, mess, dt,tt, x);
				conn.ShowMessDetail(conn.db, id, id2);
			}
		}
		else cout << "--Account Not Exist--\n";
	}
	else {
		cout << "Please Login\n\n";
	}
}
void Controller::SendMess_ctr_l(int id) {
 if(check){
	        char choo;
            cout << "Press Ctrl + L to continue.\n";
            cin.ignore();
            choo = getch();
            if(choo == 12){
				Model conn;
				conn.Open();
				ShowFriend(id);
				cout << "Select number: ";
				int n;
				cin >> n;
				int id2=conn.ShowaaFriend(conn.db,id,n);
				char *mess, *dt;
				mess = new char;
				dt = new char;
				int tt = 1;
				conn.update_tt(conn.db, id, id2);
				cout << "Content: \n";
				cin.ignore(1);
				cin.getline(mess, 100);
				time_t hientai = time(0);
				dt = ctime(&hientai);
				long int x;
				x = static_cast<int> (hientai);
				conn.WriteToMess(conn.db, id, id2, mess, dt, tt, x);
            }
 }
        else {
                cout << "Please Login\n\n";
	}
}

void Controller::ShowMess_send(int ID) {
	if (check) {
		Model conn;
		conn.Open();
		conn.SQL_Mess_send(conn.db, zID);
	}
	else {
		cout << "Please Login\n\n";
	}
}
void Controller::ShowMess_rec(int ID) {
	if (check) {
		Model conn;
		conn.Open();
		conn.SQL_Mess_receive(conn.db, zID);
	}
	else {
		cout << "Please Login\n\n";
	}
}
int Controller::ShowMessDetail(int id1) {
	if (check) {
		int id2;
		cout << "Enter User: ";
		char *frien;
		frien = new char;
		cin >> frien;
		Model conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0) {
			conn.ShowMessDetail(conn.db, id1, id2);
			zID2 = id2;
			Detail = true;
		}
		else {
              cout << "Account not exist \n";
		       Detail = false;
            }
	}
	else {
		cout << "Please Login\n\n";
	}
	return zID2;
}
void Controller::ShowFriend(int id) {
	if (check) {
		Model conn;
		conn.Open();
		conn.ShowFriend(conn.db, id);
	}
	else {
		cout << "Please Login\n\n";
	}
}
void Controller::ShowFriend_ctr_C(int id) {
   if(check){
            char choo;
            cout << "Press Ctrl + C to Sort Friend\n";
            cin.ignore();
            choo = getch();
            if(choo == 3){
				Model conn;
				conn.Open();
				conn.ShowFriend(conn.db, id);
            }
    }
	else {
		cout << "Please Login\n\n";
	}
}
void Controller::AddFriend(int id) {
	if (check) {
		cout << "Username: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Model conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (!conn.CheckFriend(conn.db, id, id2)) {
				if (!conn.CheckBlock(conn.db, id, id2)) {
					conn.WriteToFriend(conn.db, id, id2);
					ShowFriend(id);
				}
				else cout << "------You was blocked----\n\n\n";
			}
			else cout << "------You was friend ----------\n\n\n";
		}
		else cout << "--Account not Exist--\n";
	}
	else cout << "Please Login\n\n";
}
void Controller::BlockFriend(int id) {
	if (check) {
		cout << "Enter username: \n";
		char *usename;
		username = new char;
		cin >> username;
		Model conn;
		conn.Open();
		int id2 = conn.Seach_fr(username);
		if (id2 > 0) {
			conn.BlockFriend(conn.db, id, id2);
			cout << "---------Block Successfuly---------\n";
			conn.ShowFriend(conn.db, id);
		}
		else cout << "--Account not Exist--\n";
	}
	else {
		cout << "Please Login\n\n";
	}
}
void Controller::Update_fr(int id) {
	if (check) {
		cout << "Enter username: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Model conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (conn.CheckFriend(conn.db, id, id2)) {
				fullname = new char;
				sex=new char;
				address=new char;
				cout << "Name: ";
				cin.ignore(1);
                cin.getline(fullname,30);
				cout << "Sex: ";
				cin >> sex;
				cout << "Address:";
				cin.ignore(1);
                cin.getline(address,30);
				conn.Update_fr(conn.db,fullname,sex,address,id2);
			}
			else cout << "-You was friend -\n\n\n";
		}
		else cout << "-Account not Exist-\n";
	}
	else cout << "Please Login\n\n";
}
int Controller::Detail_fr(int id) {
	if (check) {
		cout << "Enter Username: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Model conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (conn.CheckFriend(conn.db, id, id2)) {
				conn.Detail_fr(conn.db, id2);
				Detail = true;
				zID2 = id2;
			}
			else { cout << "------You was friend -\n\n\n"; Detail = false;}
		}
		else { cout << "--Account Not Exist--\n"; Detail = false;}
	}
	else cout << "Please Login\n\n";
	return zID2;
}
void Controller::Reply(int id) {
    if(check){

           char choo;
	       cout << "Press Ctrl + R.\n";
           cin.ignore();
           choo = getch();
            if(choo == 18){
			char *mess, *dt;
			mess = new char;
			dt = new char;
			int tt = 1;
			Model conn;
			conn.Open();
			conn.update_tt(conn.db, id, zID2);
			cout << "Content: \n";
			cin.getline(mess,50);
			time_t hientai = time(0);
			dt = ctime(&hientai);
			long int x;
			x = static_cast<int> (hientai);
			conn.WriteToMess(conn.db, id, zID2, mess, dt, tt, x);
			conn.ShowMessDetail(conn.db, id, zID2);
		}
    }
    else
        cout << "Please Login \n";

	}
void Controller::Detail_Reply(int id) {
	char *mess, *dt;
	mess = new char;
	dt = new char;
	int tt = 1;
	Model conn;
	conn.Open();
	conn.update_tt(conn.db, id, zID2);
	cout << "Content: \n";
	cin.ignore();
	cin.getline(mess,50);
	time_t hientai = time(0);
	dt = ctime(&hientai);
	long int x;
	x = static_cast<int> (hientai);
	conn.WriteToMess(conn.db, id, zID2, mess, dt, tt, x);
	conn.ShowMessDetail(conn.db, id, zID2);
}






