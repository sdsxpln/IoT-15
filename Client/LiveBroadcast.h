#pragma once

#include <iostream>

class LiveBroadcast 
{
public:
	LiveBroadcast();
	virtual ~LiveBroadcast();

	void start(void);
	
	void stop(void);
};

