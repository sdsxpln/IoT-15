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
		connetStatus = false;
		return false;
	}
	else
	{
		std::cout << "Connected to sever!!" << std::endl;
		connetStatus = true;
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

void Tcp::setKeepAlive(int keepalive, int idle, int cnt, int interval)
{

	if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &keepalive,sizeof(keepalive))) {
		std::cout << "socket option set error" << std::endl;
	}

	if (setsockopt(sock, SOL_TCP, TCP_KEEPIDLE, &idle, sizeof(idle))) {
		std::cout << "socket option set error" << std::endl;
	}

	if (setsockopt(sock, SOL_TCP, TCP_KEEPCNT, &cnt, sizeof(cnt))) {
		std::cout << "socket option set error" << std::endl;
	}

	if (setsockopt(sock, SOL_TCP, TCP_KEEPINTVL, &interval, sizeof(interval))) {
		std::cout << "socket option set error" << std::endl;
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


bool Tcp::getConnectStatus()
{
	return connetStatus;
}
