#include <iostream>
#include <cerrno>
#include <cstdio>
#include <pthread.h>
#include <cstdlib>
#include <wiringPi.h>
#include <thread>

#include "Tcp.h"
#include "Message.h"

using namespace std;

void *workerThread(void *arg);
void *threadGPIO(void *arg);

char rbuf[MAX_SZ];
int equipNum;

int main(int argc, char *argv[])
{
	Tcp client;
	Init config;
	int thread_id;
	pthread_t woker_thread[2];
	int status;
	int arg;
	
	config.setConfiguration();
	equipNum = config.getEquipNum();
	client.makeClient(config.getIp(), config.getPort());
	client.setKeepAlive(1, 10, 3, 1);
	
	cout << "Start Client!" << endl;

	thread_id = pthread_create(&woker_thread[0], NULL, &workerThread, (void *)&client);
	if (thread_id < 0)
	{
		cout << "Thread create error..!!" << endl;
		return -1;
	}
	
#if 1
	thread_id = pthread_create(&woker_thread[1], NULL, &threadGPIO, (void *)&client);
	if (thread_id < 0)
	{
		cout << "Thread create error..!!" << endl;
		return -1;
	}
#endif	
	pthread_join(woker_thread[0], (void **)&status);
	pthread_join(woker_thread[1], (void **)&status);

	return 0;
}
void *workerThread(void *arg)
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

#if 1
void *threadGPIO(void *arg)
{
	Tcp client = *(Tcp *)arg;
	
	struct statusAmp *sdata;
	sdata = (struct statusAmp *)&client.packet.data;

	client.packet.head.source = equipNum;
	client.packet.head.destination = SERVER;
	client.packet.head.cmd = STATUS_AMP;
	client.packet.head.len = sizeof(*sdata);
	
	
	if (wiringPiSetupGpio() == -1)
	{
		cout << "Fail to GPIO setup!!" << endl;
	}
	
	pinMode(4, INPUT);
	pinMode(5, OUTPUT);
	
	int result = 0;
	while (1)
	{
		digitalWrite(5, HIGH);
		delay(1000);
		if (digitalRead(4) == LOW)
		{
			sdata->result = NORMAL;
			client.sendMessage((char*)&client.packet, sizeof(client.packet.head) + client.packet.head.len);
		}
		digitalWrite(5, LOW);
		delay(500);
		
	}

}
#endif