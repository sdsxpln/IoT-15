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
	
	void setDirection(int pin, std::string direction);
	int read(int pin);
	void write(int pin,int val);
};

