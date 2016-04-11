#include "Gpio.h"

Gpio::Gpio()
{
}


Gpio::~Gpio()
{
}


void Gpio::checkAmpStatus(void *arg)
{
	Tcp client = *(Tcp *)arg;
	Init config;
	struct statusAmp *sdata;
	sdata = (struct statusAmp *)&client.packet.data;
	
	config.setConfiguration();

	client.packet.head.source = config.getEquipNum();
	client.packet.head.destination = SERVER;
	client.packet.head.cmd = STATUS_AMP;
	client.packet.head.len = sizeof(*sdata);
	
	
	if (wiringPiSetupGpio() == -1)
	{
		std::cout << "Fail to GPIO setup!!" << std::endl;
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
