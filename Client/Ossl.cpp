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
	
    /* ����ϰ� �Ǵ� ������ ������ �����Ѵ�. - opt*/
	if (SSL_CTX_use_certificate_file(ctx, "./client.crt", SSL_FILETYPE_PEM) <= 0) {    // �������� ���Ϸ� ���� �ε��Ҷ� �����.
		ERR_print_errors_fp(stderr);
		exit(3);
	}
   
    /* ��ȣȭ ����� ���ؼ� �̿��ϴ� ���� Ű�� �����Ѵ�. - opt */
	if (SSL_CTX_use_PrivateKey_file(ctx, "./client.key", SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		exit(4);
	}
   
    /* ���� Ű�� ��� ������ ������ Ȯ���Ѵ�. - opt */
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
    /* ������ �������� �޴´�. */
	server_cert = SSL_get_peer_certificate(ssl);
	CHK_NULL(server_cert);
	std::cout << "Server certificate:" << std::endl;
   
	 /* �������� �̸��� ����Ѵ�. */
	str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
	CHK_NULL(str);
	std::cout << "subject: " << str << std::endl;
	OPENSSL_free(str);
   
	/* �������� issuer�� ����Ѵ�. */
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
