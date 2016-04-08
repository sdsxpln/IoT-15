#include "Tcp.h"


Tcp::Tcp()
{
}

Tcp::~Tcp()
{
}


void Tcp::makeClient(char *ip, int port)
{
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Can't create socket" << std::endl;
		return;
	}
	bzero((char *)&saddr, sizeof(saddr));
	
	saddr.sin_family = AF_INET;
	
	saddr.sin_addr.s_addr = inet_addr(ip);
	
	saddr.sin_port = htons(port);
}


void Tcp::connectToServer()
{

#if 1
	if (connect(sock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
	{
		perror("Can't connect to server : ");
		return;
	}
	else
		std::cout << "Connected to sever!!" << std::endl;
#endif
}

void Tcp::sendMessage(char *buf, int sz)
{
	
	ssize = write(sock, buf, sz);
	
}

int Tcp::receiveMessage(char *buf, int sz)
{
	rsize = read(sock, buf, sz);
	
	return rsize;
}

int Tcp::receiveMessage()
{
	
}

void Tcp::showMeassge(char * buf, int sz)
{
	int i, column;

	printf(" 4  3  2  1\n"
			"-----------\n");

	for (column = 0, i = 0; i < sz; column++, i++) {
		if (column == 4) {
			printf("\n");
			column = 0;
		}
		printf("%02X ", buf[i]);
	}
	printf("\n");
}


