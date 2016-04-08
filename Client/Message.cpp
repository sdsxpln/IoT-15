#include "Message.h"


Message::Message()
{
}

Message::~Message()
{
}

void Message::sendMessage(char *buf, int sz)
{
}

int Message::receiveMessage(char *buf, int sz)
{
}

void Message::showMeassge(char * buf, int sz)
{
}

void Message::handleMessage(char *buf)
{
	struct msg_head * msgReceiveHead; 
	
	msgReceiveHead = (struct msg_head *)buf;
	
	if (msgReceiveHead->cmd == CMD_ALL_LIVE_BROADCAST_START)
	{
		LiveBroadcast br;
		br.start();
		struct allLiveBroadCastStartAck *sdata;
		sdata = (struct allLiveBroadCastStartAck *)&packet.data;

		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		sdata->result = NORMAL;
	}
	
	if (msgReceiveHead->cmd == CMD_ALL_LIVE_BROADCAST_STOP)
	{
		LiveBroadcast br;
		br.stop();
		struct allLiveBroadCastStopAck *sdata;
		sdata = (struct allLiveBroadCastStopAck *)&packet.data;

		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		sdata->result = NORMAL;
	}

#if 1
	if (msgReceiveHead->cmd == CMD_GROUP_LIVE_BROADCAST_START)
	{
		Init config;
		struct allLiveBroadCastStartAck *sdata;
		sdata = (struct allLiveBroadCastStartAck *)&packet.data;
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		config.setConfiguration();
		if (msgReceiveHead->destination == config.getEquipNum())
		{
			LiveBroadcast br;
			br.start();
			sdata->result = NORMAL;
		}
		else
		{
			std::cout << "Invalid Destination code(EquipNum : " << config.getEquipNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
		}
	}
#endif
	
#if 1
	if (msgReceiveHead->cmd == CMD_GROUP_LIVE_BROADCAST_STOP)
	{
		Init config;
		struct allLiveBroadCastStopAck *sdata;
		sdata = (struct allLiveBroadCastStopAck *)&packet.data;

		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		config.setConfiguration();
		if (msgReceiveHead->destination == config.getEquipNum())
		{
			LiveBroadcast br;
			br.stop();
			sdata->result = NORMAL;
		}
		else
		{
			std::cout << "Invalid Destination code(EquipNum : " << config.getEquipNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
		}
	}
#endif
	if (msgReceiveHead->cmd == CMD_ALL_NATURE_DISASTER_BROADCAST_START)
	{
		DisasterBroadcast dbr;
		struct natureDisasterBroadcastStartRequest *rdata;
		rdata = (struct natureDisasterBroadcastStartRequest *)(char *)buf + sizeof(msg_head); 
		int pid = fork();
		if (pid == 0)
		{
			if (rdata->kind == STORM)
			{
				dbr.stormStart();
			}		
		}
		else
			wait();
		struct natureDisasterBroadcastStartAck *sdata;
		sdata = (struct natureDisasterBroadcastStartAck *)&packet.data;
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		//sdata->kind = STORM;
		sdata->result = NORMAL;
	}
	if (msgReceiveHead->cmd == CMD_ALL_NATURE_DISASTER_BROADCAST_STOP)
	{
		DisasterBroadcast dbr;
		struct natureDisasterBroadcastStopRequest *rdata;
		rdata = (struct natureDisasterBroadcastStopRequest *)(char *)buf + sizeof(msg_head); 
		if (rdata->kind == STORM)
		{
			dbr.stormStop();
			struct natureDisasterBroadcastStopAck *sdata;
			sdata = (struct natureDisasterBroadcastStopAck *)&packet.data;
			packet.head.source = msgReceiveHead->destination;
			packet.head.destination = msgReceiveHead->source;
			packet.head.cmd = msgReceiveHead->cmd;
			packet.head.len = sizeof(*sdata);
			//sdata->kind = STORM;
			sdata->result = NORMAL;
		}
	}
}
