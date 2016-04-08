#include <cstdio>
#include <iostream>
#include "cmd.h"
#include "LiveBroadcast.h"
#include "DisasterBroadcast.h"
#include "Init.h"
#pragma once


class Message
{
public:
	msgPacket packet;

	Message();
	virtual ~Message();
	
	void sendMessage(char *buf, int sz);
	int receiveMessage(char *buf, int sz);
	void showMeassge(char * buf, int sz);
	void handleMessage(char *buf);

	
};

