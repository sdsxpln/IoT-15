#pragma once

#define MAX_SZ															1024

#define CMD_ALL_LIVE_BROADCAST_START									(0x10)
#define CMD_ALL_LIVE_BROADCAST_STOP										(0x11)
#define CMD_GROUP_LIVE_BROADCAST_START									(0x12)
#define CMD_GROUP_LIVE_BROADCAST_STOP									(0x13)

#define CMD_ALL_NATURE_DISASTER_BROADCAST_START							(0x20)
#define CMD_ALL_NATURE_DISASTER_BROADCAST_STOP							(0x21)


#define CMD_GROUP_NATURE_DISASTER_BROADCAST_START						(0x40)
#define CMD_GROUP_NATURE_DISASTER_BROADCAST_STOP						(0x41)

#define CMD_ALL_SOCIETY_DISASTER_BROADCAST_START						(0x30)
#define CMD_ALL_SOCIETY_DISASTER_BROADCAST_STOP							(0x31)


#define CMD_GROUP_SOCIETY_DISASTER_BROADCAST_START						(0x50)
#define CMD_GROUP_SOCIETY_DISASTER_BROADCAST_STOP						(0x51)

#define	CMD_BOARD_REBOOT												(0x90)

#define STATUS_AMP														(0xA0)

#define STATUS_ALIVE													(0xB0)

#define NORMAL															(0x01)
#define ABNORMAL														(0x00)

#define SERVER															(0x01)

#define STORM															(0x01)
#define FLOOD															(0x02)
#define HEAVY_RAIN														(0x03)
#define TSUNAMI															(0x04)
#define HEAVY_SNOW														(0x05)
#define DROUGHT															(0x06)
#define EARTHQUAKE														(0x07)
#define N_ETC															(0x08)


struct __attribute__((__packed__)) msg_head {
	char source;
	char destination;
	char cmd;
	char len;
};
struct __attribute__((__packed__)) msgPacket {
	msg_head head;
	void *data;
};
struct __attribute__((__packed__)) allLiveBroadCastStartRequest {
	
};
struct __attribute__((__packed__)) allLiveBroadCastStartAck {
	unsigned char result;		
};

struct __attribute__((__packed__)) allLiveBroadCastStopRequest {
	
};
struct __attribute__((__packed__)) allLiveBroadCastStopAck {
	unsigned char result;		
};

struct __attribute__((__packed__)) natureDisasterBroadcastStartRequest {
	unsigned char kind;
};
struct __attribute__((__packed__)) natureDisasterBroadcastStartAck {
	//unsigned char kind;
	unsigned char result;
};

struct __attribute__((__packed__)) natureDisasterBroadcastStopRequest {
	unsigned char kind;
};
struct __attribute__((__packed__)) natureDisasterBroadcastStopAck {
	//unsigned char kind;
	unsigned char result;
};

struct __attribute__((__packed__)) statusAmp {
	unsigned char result;		
};

struct __attribute__((__packed__)) statusAlive {
	unsigned char devNum;		
};

struct __attribute__((__packed__)) rebootBoardRequest {
	unsigned char devNum;		
};

struct __attribute__((__packed__)) rebootBoardAck {
	unsigned char result;		
};