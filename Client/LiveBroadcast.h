#include <iostream>
#pragma once
class LiveBroadcast 
{
public:
	LiveBroadcast();
	virtual ~LiveBroadcast();

	void start(void);
	
	void stop(void);
};

