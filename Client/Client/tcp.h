#pragma comment(lib, "Ws2_32.lib")
#pragma once
class tcp
{
public:
	int tcp_recv(void);
	int tcp_send(char buff[]);

	~tcp(void);
};

