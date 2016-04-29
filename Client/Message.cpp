#include "Message.h"


Message::Message()
{
}

Message::~Message()
{
}

int Message::sendMessage(char *buf, int sz)
{
}

int Message::receiveMessage(char *buf, int sz)
{
}

void Message::showMeassge(char * buf, int sz)
{
	int i, column;
	std::cout << " 1  2  3  4" << std::endl;
	std::cout << "-----------" << std::endl;
	for (column = 0, i = 0; i < sz; column++, i++) {
		if (column == 4) {
			std::cout << std::endl;
			column = 0;
		}
		std::cout << std::setfill('0')<<std::setw(2)<<std::hex << (int)buf[i]<<" "; 
	}
	std::cout << std::endl;
	std::cout << "-----------" << std::endl;
}

void Message::handleMessage(char *buf)
{
	msg_head * msgReceiveHead; 
	
	msgReceiveHead = (msg_head *)buf;
	
	selectSendingPacket = false;
	
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
		
		FILE *fd = popen("ip addr | grep \"inet\" | grep brd | grep eth0 | awk '{print $2}' | awk -F/ '{print $1}'", "r");
		if (fd != NULL) {
			fgets(sdata->devIP, sizeof(sdata->devIP), fd);
		}
		pclose(fd);
		
		packet.head.len = strlen(sdata->devIP) + sizeof(sdata->result) -1 ; //line feed 제거
		selectSendingPacket = true;

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
		
		selectSendingPacket = true;
	}

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
			
			FILE *fd = popen("ip addr | grep \"inet\" | grep brd | grep eth0 | awk '{print $2}' | awk -F/ '{print $1}'", "r");
			if (fd != NULL) {
				fgets(sdata->devIP, sizeof(sdata->devIP), fd);
			}
			pclose(fd);
		
			packet.head.len = strlen(sdata->devIP) + sizeof(sdata->result) - 1; //line feed 제거
			
			selectSendingPacket = true;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
			selectSendingPacket = false;
		}
	}
	
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
			selectSendingPacket = true;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
			selectSendingPacket = false;
		}
	}

	if (msgReceiveHead->cmd == CMD_ALL_NATURE_DISASTER_BROADCAST_START)
	{
		DisasterBroadcast dbr;
		natureDisasterBroadcastStartRequest *rdata;
		rdata = (natureDisasterBroadcastStartRequest *)(char *)buf + sizeof(msg_head); 
		
		natureDisasterBroadcastStartAck *sdata;
		sdata = (natureDisasterBroadcastStartAck *)&packet.data;
		
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		int pid = fork();
		if (pid == 0)
		{
			switch (rdata->kind)
			{
			case STORM :
				dbr.stormStart();
				sdata->result = NORMAL;
				break;
			case FLOOD :
				dbr.floodStart();
				sdata->result = NORMAL;
				break;
			case HEAVY_RAIN :
				dbr.heavyRainStart();
				sdata->result = NORMAL;
				break;
			case TSUNAMI :
				dbr.tsunamiStart();
				sdata->result = NORMAL;
				break;
			case HEAVY_SNOW :
				dbr.heavySnowStart();
				sdata->result = NORMAL;
				break;
			case DROUGHT :
				dbr.droughtStart();
				sdata->result = NORMAL;
				break;
			case EARTHQUAKE :
				dbr.earthquakeStart();
				sdata->result = NORMAL;
				break;
			case N_ETC :
				dbr.nEtcStart();
				sdata->result = NORMAL;
				break;
			default : 
				std::cout << "Invalid kind of disaster!!" << std::endl;
				sdata->result = ABNORMAL;
			}
		}
		else
			wait();
		
		selectSendingPacket = true;
	}
	if (msgReceiveHead->cmd == CMD_ALL_NATURE_DISASTER_BROADCAST_STOP)
	{
		DisasterBroadcast dbr;
	
		dbr.stop();
		natureDisasterBroadcastStopAck *sdata;
		sdata = (natureDisasterBroadcastStopAck *)&packet.data;
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		sdata->result = NORMAL;
		
		selectSendingPacket = true;
	}
	
	if (msgReceiveHead->cmd == CMD_GROUP_NATURE_DISASTER_BROADCAST_START)
	{
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
				switch (rdata->kind)
				{
				case STORM :
					dbr.stormStart();
					sdata->result = NORMAL;
					break;
				case FLOOD :
					dbr.floodStart();
					sdata->result = NORMAL;
					break;
				case HEAVY_RAIN :
					dbr.heavyRainStart();
					sdata->result = NORMAL;
					break;
				case TSUNAMI :
					dbr.tsunamiStart();
					sdata->result = NORMAL;
					break;
				case HEAVY_SNOW :
					dbr.heavySnowStart();
					sdata->result = NORMAL;
					break;
				case DROUGHT :
					dbr.droughtStart();
					sdata->result = NORMAL;
					break;
				case EARTHQUAKE :
					dbr.earthquakeStart();
					sdata->result = NORMAL;
					break;
				case N_ETC :
					dbr.nEtcStart();
					sdata->result = NORMAL;
					break;
				default : 
					std::cout << "Invalid kind of disaster!!" << std::endl;
					sdata->result = ABNORMAL;
				}
			}
			else
				wait();
			
			selectSendingPacket = true;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
			selectSendingPacket = false;
		}	
	}
	if (msgReceiveHead->cmd == CMD_GROUP_NATURE_DISASTER_BROADCAST_STOP)
	{
		Init dev;
		natureDisasterBroadcastStopAck *sdata;
		sdata = (natureDisasterBroadcastStopAck *)&packet.data;
		
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		if (msgReceiveHead->destination == dev.getGroupNum())
		{
			DisasterBroadcast dbr;
			dbr.stop();
			sdata->result = NORMAL;
			selectSendingPacket = true;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
			selectSendingPacket = false;
		}
	}
	
	if (msgReceiveHead->cmd == CMD_ALL_SOCIETY_DISASTER_BROADCAST_START)
	{
		DisasterBroadcast dbr;
		societyDisasterBroadcastStartRequest *rdata;
		rdata = (societyDisasterBroadcastStartRequest *)(char *)buf + sizeof(msg_head); 
		
		societyDisasterBroadcastStartAck *sdata;
		sdata = (societyDisasterBroadcastStartAck *)&packet.data;
		
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		int pid = fork();
		if (pid == 0)
		{
			switch (rdata->kind)
			{
			case FIRE :
				dbr.fireStart();
				sdata->result = NORMAL;
				break;
			case COLLAPSE :
				dbr.collapseStart();
				sdata->result = NORMAL;
				break;
			case EXPLOSION :
				dbr.explosionStart();
				sdata->result = NORMAL;
				break;
			case ACCIDENT :
				dbr.accidentStart();
				sdata->result = NORMAL;
				break;
			case S_ETC :
				dbr.sEtcStart();
				sdata->result = NORMAL;
				break;
			default : 
				std::cout << "Invalid kind of disaster!!" << std::endl;
				sdata->result = ABNORMAL;
			}
		}
		else
			wait();
		
		selectSendingPacket = true;
		
	}
	
	if (msgReceiveHead->cmd == CMD_ALL_SOCIETY_DISASTER_BROADCAST_STOP)
	{
		DisasterBroadcast dbr;
	
		dbr.stop();
		societyDisasterBroadcastStopAck *sdata;
		sdata = (societyDisasterBroadcastStopAck *)&packet.data;
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		sdata->result = NORMAL;
		
		selectSendingPacket = true;
	}
	
	if (msgReceiveHead->cmd == CMD_GROUP_SOCIETY_DISASTER_BROADCAST_START)
	{
		Init dev;
		DisasterBroadcast dbr;
		societyDisasterBroadcastStartRequest *rdata;
		rdata = (societyDisasterBroadcastStartRequest *)(char *)buf + sizeof(msg_head);
		
		societyDisasterBroadcastStartAck *sdata;
		sdata = (societyDisasterBroadcastStartAck *)&packet.data;
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		if (msgReceiveHead->destination == dev.getGroupNum())
		{
			int pid = fork();
			if (pid == 0)
			{
				switch (rdata->kind)
				{
				case FIRE :
					dbr.fireStart();
					sdata->result = NORMAL;
					break;
				case COLLAPSE :
					dbr.collapseStart();
					sdata->result = NORMAL;
					break;
				case EXPLOSION :
					dbr.explosionStart();
					sdata->result = NORMAL;
					break;
				case ACCIDENT :
					dbr.accidentStart();
					sdata->result = NORMAL;
					break;
				case S_ETC :
					dbr.sEtcStart();
					sdata->result = NORMAL;
					break;
				default : 
					std::cout << "Invalid kind of disaster!!" << std::endl;
					sdata->result = ABNORMAL;
				}
			}
			else
				wait();
			
			selectSendingPacket = true;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
			selectSendingPacket = false;
		}	
		
	}
	
	if (msgReceiveHead->cmd == CMD_GROUP_SOCIETY_DISASTER_BROADCAST_STOP)
	{
		Init dev;
		societyDisasterBroadcastStopAck *sdata;
		sdata = (societyDisasterBroadcastStopAck *)&packet.data;
		
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		if (msgReceiveHead->destination == dev.getGroupNum())
		{
			DisasterBroadcast dbr;
			dbr.stop();
			sdata->result = NORMAL;
			selectSendingPacket = true;
		}
		else
		{
			std::cout << "Invalid Destination code(GroupNum : " << dev.getGroupNum() << ")" << std::endl;
			sdata->result = ABNORMAL;
			selectSendingPacket = false;
		}
		
	}
	
	if (msgReceiveHead->cmd == CMD_BOARD_REBOOT)
	{
		Init dev;
		rebootBoardRequest *rdata;
		rdata = (rebootBoardRequest *)(char *)buf + sizeof(msg_head);
		
		rebootBoardAck *sdata;
		sdata = (rebootBoardAck *)&packet.data;
		
		packet.head.source = msgReceiveHead->destination;
		packet.head.destination = msgReceiveHead->source;
		packet.head.cmd = msgReceiveHead->cmd;
		packet.head.len = sizeof(*sdata);
		
		if (rdata->devNum == dev.getDevNum())
		{
			sdata->result = NORMAL;		
			system("sudo reboot -n");
			selectSendingPacket = true;
		}
		else
		{
			sdata->result = ABNORMAL;
			std::cout << "Invalid dev number" << std::endl;
			selectSendingPacket = false;
		}	
	}
}


bool Message::getSelectedSend()
{
	return selectSendingPacket;
}


msgPacket* Message::getpacket()
{
	return &packet;
}


int Message::getpacketSize()
{
	return packet.head.len + sizeof(packet.head);
}


void Message::makePacket(msgPacket msg)
{
	packet = msg;
}

bool Message::checkMessage(char *buf, int rsize)
{
	msg_head * msgReceiveHead; 
	
	msgReceiveHead = (msg_head *)buf;
	
	if ( rsize == msgReceiveHead->len+ sizeof(*msgReceiveHead))
		return true;
		
	else
		return false;
		
}
