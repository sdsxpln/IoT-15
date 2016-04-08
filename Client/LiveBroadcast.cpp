#include "LiveBroadcast.h"


LiveBroadcast::LiveBroadcast()
{
}


LiveBroadcast::~LiveBroadcast()
{
}


void LiveBroadcast::start(void)
{
	std::cout << "Start Live Broadcast!!" << std::endl;
	system("/home/pi/Live.sh");
}


void LiveBroadcast::stop(void)
{
	std::cout << "Stop Live Broadcast!!" << std::endl;
	system("/home/pi/Liveoff.sh");
}
