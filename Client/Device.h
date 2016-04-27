#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>

#include "cmd.h"
#include "Tcp.h"
#include "Init.h"
#include "Ossl.h"
#include "Gpio.h"

class Device
{
public:
	Device();
	virtual ~Device();

	void checkAlive(Tcp *client, std::mutex *mtx_lock);
	void checkAmpStatus(Tcp *client, std::mutex *mtx_lock);
};

