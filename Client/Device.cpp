#include "Device.h"


Device::Device()
{
}


Device::~Device()
{
}

void Device::checkAlive(Tcp *client, std::mutex *mtx_lock)
{
	Init config;
	msgPacket msg;
	statusAlive *sdata;
	sdata = (statusAlive *)&msg.data;
	
	msg.head.source = config.getGroupNum();
	msg.head.destination = SERVER;
	msg.head.cmd = STATUS_ALIVE;
	msg.head.len = sizeof(*sdata);
	sdata->devNum = config.getDevNum();
	
	while (1)
	{
		mtx_lock->lock();
		client->makePacket(msg);
		if(client->getConnectStatus())
			client->sendMessage((char*)client->getpacket(), client->getpacketSize());
		mtx_lock->unlock();
		sleep(10);
	}

}

void Device::checkAmpStatus(Tcp *client, std::mutex *mtx_lock)
{
	Gpio gpio;
	Init config;
	msgPacket msg;
	
	statusAmp *sdata;
	sdata = (statusAmp *)&msg.data;
	
	gpio.setDirection(4, "INPUT");
	gpio.setDirection(5, "OUTPUT");
	
	while (1)
	{
		mtx_lock->lock();
		msg.head.source = config.getGroupNum();
		msg.head.destination = SERVER;
		msg.head.cmd = STATUS_AMP;
		msg.head.len = sizeof(*sdata);
		
		//gpio.write(5, HIGH);
		sleep(1);
		if (gpio.read(4) == LOW)
		{
			sdata->result = ABNORMAL;
			client->makePacket(msg);
			if (client->getConnectStatus())
				client->sendMessage((char*)client->getpacket(), client->getpacketSize());
		}
		//gpio.write(5, LOW);
		mtx_lock->unlock();
		sleep(1);
	}
}
