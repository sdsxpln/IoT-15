#include "Gpio.h"

Gpio::Gpio()
{
	if (wiringPiSetupGpio() == -1)
	{
		std::cout << "Fail to GPIO setup!!" << std::endl;
	}
}


Gpio::~Gpio()
{
}

void Gpio::setDirection(int pin, std::string direction)
{
	if (direction == "INPUT")
	{
		pinMode(pin, INPUT);
	}
	if (direction == "OUTPUT")
	{
		pinMode(5, OUTPUT);
	}
}
int Gpio::read(int pin)
{
	return digitalRead(pin);
}


void Gpio::write(int pin, int val)
{
	digitalWrite(pin,val);
}
