#include "Init.h"


Init::Init()
{
}


Init::~Init()
{
}


void Init::setConfiguration(void)
{
	char ipaddr[100];
	char port[100];
	char num[100];
	
	
	FILE *fd;
	fd = popen("cat /home/pi/configIot.ini | grep 'IP' | awk {'print $3}' | awk 'NR ==1'", "r");
	if (fd != NULL) {
		fgets(ipaddr, sizeof(ipaddr), fd);
	}
	pclose(fd);
	
	fd = popen("cat /home/pi/configIot.ini | grep 'PORT' | awk {'print $3}' | awk 'NR ==1'", "r");
	
	if (fd != NULL) {
		fgets(port, sizeof(port), fd);
	}
	pclose(fd);
	
	fd = popen("cat /home/pi/configIot.ini | grep 'EQUIP' | awk {'print $3}' | awk 'NR ==1'", "r");
	
	if (fd != NULL) {
		fgets(num, sizeof(num), fd);
	}
	pclose(fd);

	strcpy(Ip, ipaddr);
	Port = atoi(port);
	EqipNum = atoi(num);
}

char * Init::getIp(void)
{
	return Ip;
}


int Init::getPort(void)
{
	return Port;
}


int Init::getEquipNum(void)
{
	return EqipNum;
}
