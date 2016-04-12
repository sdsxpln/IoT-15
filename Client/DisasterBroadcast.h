#pragma once
#include <iostream>
#include <unistd.h>

class DisasterBroadcast
{
public:
	DisasterBroadcast();
	~DisasterBroadcast();
	
	void stormStart();
	void stop();
};

