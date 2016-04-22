#pragma once

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "cmd.h"
#include "LiveBroadcast.h"
#include "DisasterBroadcast.h"
#include "Init.h"

class Message
{
private:
	bool selectSendingPacket;
	msgPacket packet;
public:
	Message();
	virtual ~Message();
	
	int sendMessage(char *buf, int sz);
	int receiveMessage(char *buf, int sz);
	void showMeassge(char * buf, int sz);
	void handleMessage(char *buf);
	bool getSelectedSend();
	msgPacket* getpacket();
	int getpacketSize();
	void makePacket(msgPacket);
	
};

