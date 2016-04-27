#include "Ossl.h"


Ossl::Ossl()
{
	connetStatus = false;
}


Ossl::~Ossl()
{
}

void Ossl::setSSL()
{
	SSL_library_init();
	SSL_load_error_strings();
	SSLeay_add_ssl_algorithms();
	meth = SSLv3_client_method();
	ctx = SSL_CTX_new(meth);
	CHK_NULL(ctx);
	
    /* 사용하게 되는 인증서 파일을 설정한다. - opt*/
	if (SSL_CTX_use_certificate_file(ctx, "./client.crt", SSL_FILETYPE_PEM) <= 0) {    // 인증서를 파일로 부터 로딩할때 사용함.
		ERR_print_errors_fp(stderr);
		exit(3);
	}
   
    /* 암호화 통신을 위해서 이용하는 개인 키를 설정한다. - opt */
	if (SSL_CTX_use_PrivateKey_file(ctx, "./client.key", SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		exit(4);
	}
   
    /* 개인 키가 사용 가능한 것인지 확인한다. - opt */
	if (!SSL_CTX_check_private_key(ctx)) {
		std::cout << "Private key does not match the certificate public key" << std::endl;
		exit(5);
	}
}

void Ossl::connectSSL()
{
	ssl = SSL_new(ctx); 
	CHK_NULL(ssl);
   
	SSL_set_fd(ssl, Tcp::sock);
	err = SSL_connect(ssl); 
	CHK_NULL(err);
	
	if (err < 0)
		connetStatus = false;
	else
		connetStatus = true;
	std::cout << "Private key does not match the certificate public key" <<  SSL_get_cipher(ssl) << std::endl;
  
	/* Get server's certificate (note: beware of dynamic allocation) - opt */
    /* 서버의 인증서를 받는다. */
	server_cert = SSL_get_peer_certificate(ssl);
	CHK_NULL(server_cert);
	std::cout << "Server certificate:" << std::endl;
   
	 /* 인증서의 이름을 출력한다. */
	str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
	CHK_NULL(str);
	std::cout << "subject: " << str << std::endl;
	OPENSSL_free(str);
   
	/* 인증서의 issuer를 출력한다. */
	str = X509_NAME_oneline(X509_get_issuer_name(server_cert), 0, 0);
	CHK_NULL(str);
	std::cout << "issuer: " << str << std::endl;
	OPENSSL_free(str);
   
	X509_free(server_cert);
}

void Ossl::closeSSL()
{
	SSL_free(ssl);
	SSL_CTX_free(ctx);
}

int Ossl::sendMessage(char *buf, int sz)
{
	ssize = SSL_write(ssl, buf, sz);
	return ssize;
}

int Ossl::receiveMessage(char *buf, int sz)
{
	rsize = SSL_read(ssl, buf, sz);
	return rsize;
}
