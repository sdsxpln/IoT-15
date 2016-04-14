#include "Gpio.h"

Gpio::Gpio()
{
}


Gpio::~Gpio()
{
}

void Gpio::checkAmpStatus(Tcp *client, std::mutex *mtx_lock)
{
	Init config;
	statusAmp *sdata;
	sdata = (statusAmp *)&client->packet.data;
	
	if (wiringPiSetupGpio() == -1)
	{
		std::cout << "Fail to GPIO setup!!" << std::endl;
	}
	
	pinMode(4, INPUT);
	pinMode(5, OUTPUT);
	
	int result = 0;
	while (1)
	{
		mtx_lock->lock();
		client->packet.head.source = config.getGroupNum();
		client->packet.head.destination = SERVER;
		client->packet.head.cmd = STATUS_AMP;
		client->packet.head.len = sizeof(*sdata);
		
		//digitalWrite(5, HIGH);
		delay(1000);
		if (digitalRead(4) == LOW)
		{
			sdata->result = NORMAL;
			if(client->getConnectStatus())
				client->sendMessage((char*)&client->packet, sizeof(client->packet.head) + client->packet.head.len);
		}
		mtx_lock->unlock();
		//digitalWrite(5, LOW);
		delay(500);	
	}
}
