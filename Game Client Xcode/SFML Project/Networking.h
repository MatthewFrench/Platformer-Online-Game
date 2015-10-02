//
//  Networking.h
//  Game Server
//
//  Created by Matthew French on 1/2/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_Networking_h
#define Game_Server_Networking_h
#include "UDPClient.h"
#include "TCPClient.h"
#include <SFML/Network.hpp>
#include "ClientController.h"

class ClientController;

class Networking
{
protected:
	TcpClient* tcpClient;
	UdpClient* udpClient;
	ClientController* callback;
	bool connectedTCP, connectedUDP;
	uint32 clientID;
	int udpConnectTimer;
public:
	Networking();
	void start();
	void stop();
	void setCallback(ClientController* s);
	void sendTcp(sf::Packet* p);
	void sendUdp(sf::Packet* p);
	unsigned short int getUdpPort();
	uint32 getClientID();
	void beginUdpConnect(uint32 id);
	void connectedToUdpAndTCP();
	void processMessages();
private:
	void processTCPMessages();
	void processUDPMessages();
	//Individual messages
	void processTCPMessage(sf::Packet* packet);
	void processUDPMessage(sf::Packet* packet);
};


#endif
