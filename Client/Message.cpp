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
	int i, column;

	printf(" 1  2  3  4\n"
			"-----------\n");
	for (column = 0, i = 0; i < sz; column++, i++) {
		if (column == 4) {
			printf("\n");
			column = 0;
		}
		printf("%02X ", buf[i]);
	}
	printf("\n");
}

void Message::handleMessage(char *buf)
{
	msg_head * msgReceiveHead; 
	
	msgReceiveHead = (msg_head *)buf;
	
	if (msgReceiveHead->cmd == CMD_ALL_LIVE_BROADCAST_START)
	{
		LiveBroadcast br;
		br.start();
		allLiveBroadCastStartAck *sdata;
		sdata = (allLiveBroadCastStartAck *)&packet.data;

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
		allLiveBroadCastStopAck *sdata;
		sdata = (allLiveBroadCastStopAck *)&packet.data;

		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		sdata->result = NORMAL;
	}

#if 1
	if (msgReceiveHead->cmd == CMD_GROUP_LIVE_BROADCAST_START)
	{
		Init dev;
		allLiveBroadCastStartAck *sdata;
		sdata = (allLiveBroadCastStartAck *)&packet.data;
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		if (msgReceiveHead->destination == dev.getGroupNum())
		{
			LiveBroadcast br;
			br.start();
			sdata->result = NORMAL;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
		}
	}
#endif
	
#if 1
	if (msgReceiveHead->cmd == CMD_GROUP_LIVE_BROADCAST_STOP)
	{
		Init dev;
		allLiveBroadCastStopAck *sdata;
		sdata = (allLiveBroadCastStopAck *)&packet.data;

		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		if (msgReceiveHead->destination == dev.getGroupNum())
		{
			LiveBroadcast br;
			br.stop();
			sdata->result = NORMAL;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
		}
	}
#endif
	if (msgReceiveHead->cmd == CMD_ALL_NATURE_DISASTER_BROADCAST_START)
	{
		DisasterBroadcast dbr;
		natureDisasterBroadcastStartRequest *rdata;
		rdata = (natureDisasterBroadcastStartRequest *)(char *)buf + sizeof(msg_head); 
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
		natureDisasterBroadcastStartAck *sdata;
		sdata = (natureDisasterBroadcastStartAck *)&packet.data;
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
		//struct natureDisasterBroadcastStopRequest *rdata;
		//rdata = (struct natureDisasterBroadcastStopRequest *)(char *)buf + sizeof(msg_head); 
		//if (rdata->kind == STORM)
		//{
			dbr.stop();
			natureDisasterBroadcastStopAck *sdata;
			sdata = (struct natureDisasterBroadcastStopAck *)&packet.data;
			packet.head.source = msgReceiveHead->destination;
			packet.head.destination = msgReceiveHead->source;
			packet.head.cmd = msgReceiveHead->cmd;
			packet.head.len = sizeof(*sdata);
			//sdata->kind = STORM;
			sdata->result = NORMAL;
		//}
	}
	
	if (msgReceiveHead->cmd == CMD_GROUP_NATURE_DISASTER_BROADCAST_START)
	{
		//Init config;
		Init dev;
		DisasterBroadcast dbr;
		natureDisasterBroadcastStartRequest *rdata;
		rdata = (natureDisasterBroadcastStartRequest *)(char *)buf + sizeof(msg_head);
		
		natureDisasterBroadcastStartAck *sdata;
		sdata = (natureDisasterBroadcastStartAck *)&packet.data;
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		if (msgReceiveHead->destination == dev.getGroupNum())
		{
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
			//sdata->kind = STORM;
			sdata->result = NORMAL;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
		}	
	}
	if (msgReceiveHead->cmd == CMD_GROUP_NATURE_DISASTER_BROADCAST_STOP)
	{
		Init dev;
		natureDisasterBroadcastStopAck *sdata;
		sdata = (natureDisasterBroadcastStopAck *)&packet.data;
		
		if (msgReceiveHead->destination == dev.getGroupNum())
		{
			DisasterBroadcast dbr;
			dbr.stop();
			
			packet.head.source = msgReceiveHead->destination;
			packet.head.destination = msgReceiveHead->source;
			packet.head.cmd = msgReceiveHead->cmd;
			packet.head.len = sizeof(*sdata);
			sdata->result = NORMAL;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
		}
	}
	
	if (msgReceiveHead->cmd == CMD_BOARD_REBOOT)
	{
		rebootBoard *sdata;
		sdata = (rebootBoard *)&packet.data;
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		sdata->result = NORMAL;
	
		system("sudo reboot -n");
	}
}
