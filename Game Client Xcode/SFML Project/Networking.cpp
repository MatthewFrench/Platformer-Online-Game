//
//  Networking.cpp
//  Game Server
//
//  Created by Matthew French on 1/2/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include "Networking.h"

//Hashmap for clients, with the socket as the mapping

Networking::Networking() {
	connectedTCP = false;
	tcpClient = new TcpClient(serverAddress, serverPort, networkThreadDelay);
	udpClient = new UdpClient(serverAddress, serverPort, networkThreadDelay);
	clientID = -1;
	udpConnectTimer = 0;
	connectedUDP = false;
}
void Networking::start() {
	tcpClient->start();
	udpClient->start();
}
void Networking::stop() {
	tcpClient->stop();
	udpClient->stop();
}
void Networking::setCallback(ClientController* s) {
	callback = s;
}
void Networking::sendTcp(sf::Packet* p) {
	tcpClient->sendMsg(p);
}
void Networking::sendUdp(sf::Packet* p) {
	udpClient->sendMsg(p);
}
unsigned short int Networking::getUdpPort() {
	return udpClient->getPort();
}
uint32 Networking::getClientID() {
	return clientID;
}
void Networking::beginUdpConnect(uint32 id) {
	//By setting client ID, it triggers a UDP message to be sent on a timer
	clientID = id;
}
void Networking::connectedToUdpAndTCP() {
	connectedUDP = true;
	callback->onConnect();
}
void Networking::processMessages() {
	if (connectedTCP == false && tcpClient->connected == true) {
		connectedTCP = tcpClient->connected;
		//callback->onConnect();
		
		//Send UDP port to server
		//sendTcp(PacketID::Client::gpUdpPort(this));
		//std::cout << "Sent UDP Port: " << udpClient->getPort() <<std::endl;
		
	} else if (connectedTCP == true && tcpClient->connected == false) {
		connectedTCP = tcpClient->connected;
		callback->onDisconnect();
	}
	if (connectedTCP == true && connectedUDP == false && clientID != -1) {
		//std::cout << "Running UDP Connect Timer" <<std::endl;
		if (udpConnectTimer <= 0) {
			udpConnectTimer = 30;
			//Send udp connect packet to server
			sendUdp(PacketID::Client::gpUdpConnect(this));
			//std::cout << "Sending UDP Connection Attempt" <<std::endl;
		}
		udpConnectTimer -= 1;
	}
	processTCPMessages();
	processUDPMessages();
}
void Networking::processTCPMessage(sf::Packet *packet) {
	callback->onMessage(packet);
}
void Networking::processUDPMessage(sf::Packet *packet) {
	//std::cout<<"Sending udp packet to callback"<<std::endl;
	callback->onMessage(packet);
}
void Networking::processTCPMessages() {
	ChainLink* last = tcpClient->getLastRecievedMessage();
	while(tcpClient->getLastProcessedMessage() != last) {
		if (tcpClient->getLastProcessedMessage()->object1 != NULL) {
			sf::Packet* packet = static_cast<sf::Packet *>(tcpClient->getLastProcessedMessage()->object1);
			
			//uint16 id;
			//*packet >> id;
			//std::cout << "2 Recieved Message: " << id << std::endl;
			
			processTCPMessage(packet);
		}
		ChainLink* p = tcpClient->getLastProcessedMessage();
		tcpClient->setLastProcessedMessage(p->nextLink);
		p->nextLink = NULL; //Chop of the previous link so it can be disposed of
		delete p;
	}
	//Now process the last message recieved and null the object
	if (last->object1 != NULL) {
		sf::Packet* packet = static_cast<sf::Packet *>(last->object1);
		
		//uint16 id;
		//*packet >> id;
		//std::cout << "2 Recieved Message: " << id << std::endl;
		
		processTCPMessage(packet);
		last->object1 = NULL;
	}
}
void Networking::processUDPMessages() {
	ChainLink* last = udpClient->getLastRecievedMessage();
	while(udpClient->getLastProcessedMessage() != last) {
		if (udpClient->getLastProcessedMessage()->object1 != NULL) {
			sf::Packet* packet = static_cast<sf::Packet *>(udpClient->getLastProcessedMessage()->object1);
			//std::cout<< "Recieved UDP Packet!" <<std::endl;
			processUDPMessage(packet);
		}
		ChainLink* p = udpClient->getLastProcessedMessage();
		udpClient->setLastProcessedMessage(p->nextLink);
		p->nextLink = NULL; //Chop of the previous link so it can be disposed of
		delete p;
	}
	//Now process the last message recieved and null the object
	if (last->object1 != NULL) {
		sf::Packet* packet = static_cast<sf::Packet *>(last->object1);
		//std::cout<< "Recieved UDP Packet!" <<std::endl;
		processUDPMessage(packet);
		last->object1 = NULL;
	}
}