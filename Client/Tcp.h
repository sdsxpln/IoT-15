#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
//#include "cmd.h"
#include "Message.h"
#pragma once


class Tcp : public Message
{
private:
	int sock;
	struct sockaddr_in saddr, caddr;
	socklen_t addrlen;
	int opt;
	int ssize, rsize;
	
	char *_ip;
	int _port;
	//char rbuf[1024];
public:
	Tcp();
	virtual ~Tcp();
	
	void makeClient(char *ip, int port);
	bool connectToServer();
	void sendMessage(char *buf, int sz);
	int receiveMessage(char *buf, int sz);
	int receiveMessage();
	void showMeassge(char * buf, int sz);
	
	void setKeepAlive(int keepalive, int idle, int cnt, int interval);
	
	void closeSocket();
	void remakeSocket();
};

