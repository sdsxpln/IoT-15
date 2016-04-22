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

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "Message.h"

#define CHK_NULL(x) if((x) == NULL) exit(1);
#define CHK_ERR(err, s) if((err) == -1) { perror(s); exit(1); }
#define CHK_SSL(err) if((err) == -1) { ERR_print_errors_fp(stderr); exit(2); }

class Tcp : public Message
{
private:
	struct sockaddr_in saddr, caddr;
	socklen_t addrlen;
	int opt;
	int ssize, rsize;
	char *ip;
	int port;
protected:
	int sock;
	bool connetStatus;
public:
	Tcp();
	virtual ~Tcp();
	
	void makeClient(char *ip, int port);
	bool connectToServer(void);
	virtual int sendMessage(char *buf, int sz);
	virtual int receiveMessage(char *buf, int sz);
	virtual int receiveMessage(void);
	
	void setKeepAlive(int keepalive, int idle, int cnt, int interval);
	
	void closeSocket(void);
	void remakeSocket(void);
	bool getConnectStatus();
	
	virtual void setSSL(void);
	virtual void connectSSL(void);
	virtual void closeSSL(void);
};


