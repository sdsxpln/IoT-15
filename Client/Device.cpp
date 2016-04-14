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
	statusAlive *sdata;
	sdata = (statusAlive *)&client->packet.data;

	while (1)
	{
		mtx_lock->lock();
		client->packet.head.source = config.getGroupNum();
		client->packet.head.destination = SERVER;
		client->packet.head.cmd = STATUS_ALIVE;
		client->packet.head.len = sizeof(*sdata);
		sdata->devNum = config.getDevNum();
	
		if(client->getConnectStatus())
			client->sendMessage((char*)&client->packet, sizeof(client->packet.head) + client->packet.head.len);
		mtx_lock->unlock();
		sleep(10);
	}
}

