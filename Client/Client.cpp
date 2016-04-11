#include <iostream>
#include <cerrno>
#include <cstdio>
#include <pthread.h>
#include <cstdlib>
#include <thread>

#include "Tcp.h"
#include "Message.h"
#include "Gpio.h"

using namespace std;

void workerThread(void *arg);

char rbuf[MAX_SZ];

int main(int argc, char *argv[])
{
	Tcp client;
	Init config;
	int equipNum;
	
	config.setConfiguration();
	equipNum = config.getEquipNum();
	client.makeClient(config.getIp(), config.getPort());
	client.setKeepAlive(1, 10, 3, 1);
	
	cout << "Start Client!" << endl;

	thread th1(workerThread, &client);
	thread th2(&Gpio::checkAmpStatus, Gpio(),&client);

	th1.join();
	th2.join();
	
	return 0;
}

void workerThread(void *arg)
{
	Tcp client = *(Tcp *)arg;
	int rsize = 0;

	while (1)
	{
		if (client.connectToServer())
		{
			while (1)
			{
				rsize = client.receiveMessage(rbuf, sizeof(rbuf));
				client.showMeassge(rbuf, rsize);

				if (rsize <= 0) {
					perror("TCP Receive Error");
					client.closeSocket();
					client.remakeSocket();
					break;
				}
				
				client.handleMessage(rbuf);
				client.sendMessage((char*)&client.packet, sizeof(client.packet.head) + client.packet.head.len);
			}
		}
	}
}
