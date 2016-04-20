#pragma once

#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include "Message.h"

class Tcp : public Message
{
private:
	int sock;
	struct sockaddr_in saddr, caddr;
	socklen_t addrlen;
	int opt;
	int ssize, rsize;
	
	char *ip;
	int port;
	bool connetStatus;
	
public:
	Tcp();
	virtual ~Tcp();
	
	void makeClient(char *ip, int port);
	bool connectToServer();
	void sendMessage(char *buf, int sz);
	int receiveMessage(char *buf, int sz);
	int receiveMessage();
	
	void setKeepAlive(int keepalive, int idle, int cnt, int interval);
	
	void closeSocket();
	void remakeSocket();
	bool getConnectStatus();
};


