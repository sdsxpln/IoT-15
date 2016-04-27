#include "DisasterBroadcast.h"


DisasterBroadcast::DisasterBroadcast()
{
}


DisasterBroadcast::~DisasterBroadcast()
{
}


void DisasterBroadcast::stormStart()
{
	std::cout << "Storm Start!!" << std :: endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/storm.mp3", NULL);
}

void DisasterBroadcast::floodStart()
{
	std::cout << "Flood Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/flood.mp3", NULL);
}

void DisasterBroadcast::heavyRainStart()
{
	std::cout << "Heavy Rain Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/heavyrain.mp3", NULL);
}

void DisasterBroadcast::tsunamiStart()
{
	std::cout << "Tsunami Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/tsunami.mp3", NULL);
}

void DisasterBroadcast::heavySnowStart()
{
	std::cout << "Heavy Snow Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/heavysnow.mp3", NULL);
}

void DisasterBroadcast::droughtStart()
{
	std::cout << "Drought Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/drought.mp3", NULL);
}

void DisasterBroadcast::earthquakeStart()
{
	std::cout << "Earthquake Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/earthquake.mp3", NULL);
}

void DisasterBroadcast::nEtcStart()
{
	std::cout << "etc Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/etc.mp3", NULL);
}


void DisasterBroadcast::stop()
{
	std::cout << "Disaster Stop!!" << std::endl;
	system("killall omxplayer.bin");
}


void DisasterBroadcast::fireStart()
{
	std::cout << "Fire Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/fire.mp3", NULL);
}


void DisasterBroadcast::collapseStart()
{
	std::cout << "Collapse Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/collapse.mp3", NULL);
}


void DisasterBroadcast::explosionStart()
{
	std::cout << "Explosion Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/explosion.mp3", NULL);
}


void DisasterBroadcast::accidentStart()
{
	std::cout << "Accident Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/accident.mp3", NULL);
}


void DisasterBroadcast::sEtcStart()
{
	std::cout << "etc Start!!" << std::endl;
	execlp("/usr/bin/omxplayer", " ", "/home/tmp/music/etc.mp3", NULL);
}
