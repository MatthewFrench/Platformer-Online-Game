//
//  UDP.h
//  SFML Project
//
//  Created by Matthew French on 1/1/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "ChainLink.h"

#include "Global.h"

#ifndef SFML_Project_UDP_h
#define SFML_Project_UDP_h

class UdpClient
{
protected:
	int port;
	std::string ip;
	sf::UdpSocket* socket;
	sf::IpAddress server;
	
	pthread_t udpThreadListener;
	pthread_t udpThreadSender;
	bool connected;
	
	ChainLink* lastProcessedMessage;
	ChainLink* lastRecievedMessage;
	
	ChainLink* lastSentMessage;
	ChainLink* lastToSendMessage;
	
	struct timespec tim, tim2;
public:
	UdpClient(std::string i, int p, long d);
	void start();
	void stop();
	void sendMsg(sf::Packet* packet);
	ChainLink* getLastRecievedMessage();
	ChainLink* getLastProcessedMessage();
	void setLastProcessedMessage(ChainLink* c);
	unsigned short int getPort();
private:
	void* runListener();
	void* runSender();
	
	static void *listener_helper(void *context){
		return ((UdpClient *)context)->runListener();
    }
	static void *sender_helper(void *context){
		return ((UdpClient *)context)->runSender();
    }
};

#endif
