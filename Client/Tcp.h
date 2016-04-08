#include <iostream>
#include <cstring>
#include <netinet/in.h>
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
	//char rbuf[1024];
public:
	Tcp();
	virtual ~Tcp();
	
	void makeClient(char *ip, int port);
	void connectToServer();
	void sendMessage(char *buf, int sz);
	int receiveMessage(char *buf, int sz);
	int receiveMessage();
	void showMeassge(char * buf, int sz);
};

