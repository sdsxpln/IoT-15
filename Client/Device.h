#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>

#include "cmd.h"
#include "Tcp.h"
#include "Init.h"

class Device
{
public:
	Device();
	virtual ~Device();
	
	void checkAlive(Tcp *client, std::mutex *mtx_lock);
};

