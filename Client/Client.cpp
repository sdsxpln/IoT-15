#include <iostream>
#include <cerrno>
#include <cstdio>
#include <pthread.h>
#include <cstdlib>
#include <thread>
#include <mutex>

#include "Tcp.h"
#include "Message.h"
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

	thread th1(workerThread, client, &mtx_lock);							//경보 기능 수행 Thread
	thread th2(&Device::checkAmpStatus, Device(), client, &mtx_lock);		//Amp상태 점검 Thread
	thread th3(&Device::checkAlive, Device(), client, &mtx_lock);			//Device Alive Thread

	th1.join();
	th2.join();
	th3.join();
	
	delete client;
	return 0;
}

/*Server로부터 Command를 전송받아 경보기능을 수행 */
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
				if (client->checkMessage(rbuf, rsize)) //수신바이트와 데이터 헤더의 길이가 같은지 검사(짧으면 재전송?? 길면 짤라야하나??)
				{
					client->handleMessage(rbuf);
					if (client->getSelectedSend())	//서버로 메시지를 전송할지 결정(Group에 맞지 않으면 패스)
						client->sendMessage((char*)client->getpacket(), client->getpacketSize());
				}
				else
				{
					cout << "Different Data Length!!" << endl;
				}
				mtx_lock->unlock();				
			}
		}
	}
}
