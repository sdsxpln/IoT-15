#pragma once

#include <iostream>
#include <wiringPi.h>
#include <mutex>
#include "Tcp.h"
#include "Init.h"
#include "Ossl.h"

#pragma once
class Gpio
{
public:
	Gpio();
	virtual ~Gpio();
	
	void checkAmpStatus(Tcp *client, std::mutex *mtx_lock);
};

