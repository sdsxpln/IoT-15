#pragma once

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "Tcp.h"

#define USE_SSL

#define CHK_NULL(x) if((x) == NULL) exit(1);
#define CHK_ERR(err, s) if((err) == -1) { perror(s); exit(1); }
#define CHK_SSL(err) if((err) == -1) { ERR_print_errors_fp(stderr); exit(2); }

class Ossl : public Tcp
{
private:
	SSL *ssl;
	int err;
   
	SSL_CTX *ctx;
	X509 *server_cert;
	char *str;
	const SSL_METHOD *meth;

	int ssize, rsize;
public:
	Ossl();
	virtual ~Ossl();
	
	void setSSL();
	void connectSSL();
	void closeSSL();
	
	int sendMessage(char *buf, int sz);
	int receiveMessage(char *buf, int sz);
};

