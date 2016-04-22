#include <iostream>
#include <cerrno>
#include <cstdio>
#include <pthread.h>
#include <cstdlib>
#include <thread>
#include <mutex>

#include "Tcp.h"
#include "Message.h"
#include "Gpio.h"
#include "Device.h"
#include "Ossl.h"

using namespace std;

void workerThread(Tcp *client, mutex *mtx_lock);

int main(int argc, char *argv[])
{
#ifndef USE_SSL
	Tcp *client = new Tcp;
#else
	Tcp *client = new Ossl;
	cout << "**Set using SSL**" << endl;
#endif // !SSL
	Init config;
	mutex mtx_lock;
	client->setSSL();
	client->makeClient(config.getIp(), config.getPort());
	client->setKeepAlive(1, 10, 3, 1);

	cout << "**Start Client**" << endl;

	thread th1(workerThread, client, &mtx_lock);						//��� ���� Thread
	thread th2(&Gpio::checkAmpStatus, Gpio(), client, &mtx_lock);		//Amp���� ���� Thread
	thread th3(&Device::checkAlive, Device(), client, &mtx_lock);		//Device Alive Thread

	th1.join();
	th2.join();
	th3.join();
	
	delete client;
	return 0;
}

/*Server�κ��� Command�� ���۹޾� �溸����� ���� */
void workerThread(Tcp *client, mutex *mtx_lock)
{
	char rbuf[MAX_SZ];	
	
	int rsize = 0;
	
	while (1)
	{
		if (client->connectToServer())	
		{
			client->connectSSL();
			while (1)
			{
				rsize = client->receiveMessage(rbuf, sizeof(rbuf));

				if (rsize <= 0) {
					client->closeSocket();
					client->closeSSL();
					client->setSSL();
					client->remakeSocket();
					break;
				}
				client->showMeassge(rbuf, rsize);
				mtx_lock->lock();				
				client->handleMessage(rbuf);
				if (client->getSelectedSend())	//������ �޽����� �������� ����(Group�� ���� ������ �н�)
					client->sendMessage((char*)client->getpacket(), client->getpacketSize());
				mtx_lock->unlock();				
			}
		}
	}
}
