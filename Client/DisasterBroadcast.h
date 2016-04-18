#pragma once
#include <iostream>
#include <unistd.h>

class DisasterBroadcast
{
public:
	DisasterBroadcast();
	~DisasterBroadcast();
	
	void stormStart();
	void floodStart();
	void heavyRainStart();
	void tsunamiStart();
	void heavySnowStart();
	void droughtStart();
	void earthquakeStart();
	void nEtcStart();
	
	void fireStart();
	void collapseStart();
	void explosionStart();
	void accidentStart();
	void sEtcStart();
	
	void stop();
};

