#include <iostream>
#include <wiringPi.h>
#include "Tcp.h"
#include "Init.h"

#pragma once
class Gpio
{
public:
	Gpio();
	virtual ~Gpio();
	
	void checkAmpStatus(void *arg);
};

