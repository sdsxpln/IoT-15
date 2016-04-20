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

