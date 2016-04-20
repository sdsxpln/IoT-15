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
	msgPacket msg;
	statusAmp *sdata;
	sdata = (statusAmp *)&msg.data;
	
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
		msg.head.source = config.getGroupNum();
		msg.head.destination = SERVER;
		msg.head.cmd = STATUS_AMP;
		msg.head.len = sizeof(*sdata);
		
		//digitalWrite(5, HIGH);
		delay(1000);
		if (digitalRead(4) == LOW)
		{
			sdata->result = NORMAL;
			if(client->getConnectStatus())
				client->sendMessage((char*)client->getpacket(), client->getpacketSize());
		}
		mtx_lock->unlock();
		//digitalWrite(5, LOW);
		delay(500);	
	}
}
