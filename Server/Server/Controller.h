#pragma once
class Controller
{
public:
	int choice_c;
	int  id;
	char *username;
	char *password;
	char *sex;
	char *birthday;
	char *fullname;
	char *address;
	int zID;
	bool check;
	bool Detail;
	int zID2;
public:
	void SignUp(char username[],char password[],char birthday[],char fullname[],char sex[],char address[] );
	public:
	char SignIn(char username[],char password[]);
	void SingUp();
	void SignOut();
	void ShowMess_send(int);
	void ShowMess_rec(int);
	int ShowMessDetail(int);
	void SendMess(int);
	void SendMess_ctr_l(int);
	void AddFriend(int);
	void ShowFriend(int);
	void BlockFriend(int);
	void Update_fr(int);
	void Reply(int);
	void Detail_Reply(int);
	void ShowFriend_ctr_C(int);
	int Detail_fr(int);
	void login();
};

