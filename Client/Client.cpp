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
void *gpio(void *arg);

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
	client.connectToServer();
	
	cout << "Start Client!" << endl;

	thread_id = pthread_create(&woker_thread[0], NULL, &workerThread, (void *)&client);
	if (thread_id < 0)
	{
		cout << "Thread create error..!!" << endl;
		return -1;
	}
	
#if 0
	thread_id = pthread_create(&woker_thread[1], NULL, &gpio, (void *)&client);
	if (thread_id < 0)
	{
		cout << "Thread create error..!!" << endl;
		return -1;
	}
#endif	
	pthread_join(woker_thread[0], (void **)&status);
	//pthread_join(woker_thread[1], (void **)&status);

	return 0;
}
void *workerThread(void *arg)
{
	Tcp client = *(Tcp *)arg;
	int rsize = 0;
	while (1)
	{
		rsize = client.receiveMessage(rbuf, sizeof(rbuf));

		if (rsize <= 0) {
			perror("TCP Receive Error");
			break;
		}
		client.handleMessage(rbuf);
		client.sendMessage((char*)&client.packet, sizeof(client.packet.head) + client.packet.head.len);
	}
}

#if 0
void *gpio(void *arg)
{
	Tcp client = *(Tcp *)arg;

	client.packet.head.source = equipNum;
	client.packet.head.destination = 0xAA;
	client.packet.head.cmd = 0xA0;
	client.packet.head.len = sizeof(smsg.packet.data);
	
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
			smsg.packet.data.result = NORMAL;
			client.sendMessage((char *)&smsg.packet, sizeof(smsg.packet));
		}
		digitalWrite(5, LOW);
		delay(500);
		
	}

}
#endif