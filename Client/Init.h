#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>

class Init
{
private:
	char Ip[100];
	int Port;
	int EqipNum;
	
public:
	Init();
	virtual ~Init();
	
	void setConfiguration(void);
	char * getIp(void);
	int getPort(void);
	int getEquipNum(void);
};

