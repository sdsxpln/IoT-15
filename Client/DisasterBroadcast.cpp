#include "DisasterBroadcast.h"


DisasterBroadcast::DisasterBroadcast()
{
}


DisasterBroadcast::~DisasterBroadcast()
{
}


void DisasterBroadcast::stormStart()
{
	std::cout << "Storm Start!!" << std :: endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/Kalimba.mp3", NULL);
}


void DisasterBroadcast::stop()
{
	std::cout << "Storm Stop!!" << std::endl;
	system("killall omxplayer.bin");
}
