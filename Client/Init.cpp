#include "Init.h"


Init::Init()
{
	char ip[100];
	char port[100];
	char group_num[100];
	char dev_num[100];
	
	
	FILE *fd;
	fd = popen("cat /home/pi/configIot.ini | grep 'IP' | awk {'print $3}' | awk 'NR ==1'", "r");
	if (fd != NULL) {
		fgets(ip, sizeof(ip), fd);
	}
	pclose(fd);
	
	fd = popen("cat /home/pi/configIot.ini | grep 'PORT' | awk {'print $3}' | awk 'NR ==1'", "r");
	
	if (fd != NULL) {
		fgets(port, sizeof(port), fd);
	}
	pclose(fd);
	
	fd = popen("cat /home/pi/configIot.ini | grep 'GROUP' | awk {'print $3}' | awk 'NR ==1'", "r");
	
	if (fd != NULL) {
		fgets(group_num, sizeof(group_num), fd);
	}
	pclose(fd);
	
	fd = popen("cat /home/pi/configIot.ini | grep 'EQUIP' | awk {'print $3}' | awk 'NR ==1'", "r");
	
	if (fd != NULL) {
		fgets(dev_num, sizeof(dev_num), fd);
	}
	pclose(fd);


	strcpy(this->ip, ip);
	this->port = atoi(port);
	this->group_num = atoi(group_num);
	this->dev_num = atoi(dev_num);
}


Init::~Init()
{
}

#if 0
void Init::setConfiguration(void)
{
	
}
#endif

char * Init::getIp(void)
{
	return ip;
}


int Init::getPort(void)
{
	return port;
}

int Init::getGroupNum(void)
{
	return group_num;
}
int Init::getDevNum(void)
{
	return dev_num;
}
