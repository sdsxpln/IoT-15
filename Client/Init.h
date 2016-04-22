#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

class Init
{
private:
	char ip[100];
	int port;
	int group_num;
	int dev_num;
	
public:
	Init();
	virtual ~Init();
	
	char * getIp(void);
	int getPort(void);
	int getGroupNum(void);
	int getDevNum(void);
};

