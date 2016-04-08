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
	
	_ip = ip;
	_port = port;
}


bool Tcp::connectToServer()
{

#if 1
	if (connect(sock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
	{
		perror("Can't connect to server : ");
		return false;
	}
	else
	{
		std::cout << "Connected to sever!!" << std::endl;
		return true;
	}
		
	
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




void Tcp::setKeepAlive(int keepalive, int idle, int cnt, int interval)
{

	if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &keepalive,sizeof(keepalive))) {
		printf("socket option set error..\n");
	}

	if (setsockopt(sock, SOL_TCP, TCP_KEEPIDLE, &idle, sizeof(idle))) {
		printf("socket option set error..\n");
	}

	if (setsockopt(sock, SOL_TCP, TCP_KEEPCNT, &cnt, sizeof(cnt))) {
		printf("socket option set error..\n");
	}

	if (setsockopt(sock, SOL_TCP, TCP_KEEPINTVL, &interval, sizeof(interval))) {
		printf("socket option set error..\n");
	}
	
}


void Tcp::closeSocket()
{
	close(sock);
}


void Tcp::remakeSocket()
{
	makeClient(_ip, _port);
}
