//
//  TCP.h
//  SFML Project
//
//  Created by Matthew French on 1/1/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "ChainLink.h"
#include <tgmath.h>

#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2d.h"
#include "ResourcePath.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "Global.h"

#ifndef SFML_Project_TCP_h
#define SFML_Project_TCP_h

class TcpClient
{
protected:
	int port;
	std::string ip;
	sf::TcpSocket* socket;

	pthread_t tcpThreadListener;
	pthread_t tcpThreadSender;
	
	ChainLink* lastProcessedMessage;
	ChainLink* lastRecievedMessage;
	
	ChainLink* lastSentMessage;
	ChainLink* lastToSendMessage;
	
	struct timespec tim, tim2;
public:
	TcpClient(std::string i, int p, long d);
	void start();
	void stop();
	void sendMsg(sf::Packet* packet);
	ChainLink* getLastRecievedMessage();
	ChainLink* getLastProcessedMessage();
	void setLastProcessedMessage(ChainLink* c);
	
	bool connected;
private:
	void* runListener();
	void* runSender();
	
	static void *listener_helper(void *context){
		return ((TcpClient *)context)->runListener();
    }
	static void *sender_helper(void *context){
		return ((TcpClient *)context)->runSender();
    }
};


#endif
