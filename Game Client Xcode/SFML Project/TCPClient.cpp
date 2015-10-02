
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include <string>

#include "TCPClient.h"

TcpClient::TcpClient(std::string i, int p, long d) {
	ip = i;
	port = p;
	
	connected = false;
	lastProcessedMessage = new ChainLink();
	lastRecievedMessage = lastProcessedMessage;
	
	lastSentMessage = new ChainLink();
	lastToSendMessage=lastSentMessage;
	
	//Set the time to delay thread,  0.5 seconds = 500000000L
	tim.tv_sec  = 0;
	tim.tv_nsec = 5000000L; //5000000L = 200 network updates per second
}
void TcpClient::start() {
	pthread_create(&tcpThreadListener, NULL, listener_helper, this);
}
void TcpClient::stop() {
	connected = false;
	socket->disconnect();
}
ChainLink* TcpClient::getLastRecievedMessage() { return lastRecievedMessage; }
ChainLink* TcpClient::getLastProcessedMessage() { return lastProcessedMessage; }
void TcpClient::setLastProcessedMessage(ChainLink* c) {lastProcessedMessage=c;}
void* TcpClient::runListener() {
	sf::IpAddress server(ip);
	socket = new sf::TcpSocket();
	//Will block main thread for 5 seconds
	if (socket->connect (server, port, sf::seconds(5.0f)) != sf::Socket::Done) {
		std::cout << "Unable to connect to server " << server << std::endl;
	} else {
		//std::cout << "Connected to server " << server << std::endl;
		connected = true;
		//Start recieving
		pthread_create(&tcpThreadSender, NULL, sender_helper, this);
	}
	
	while (connected)
	{
		sf::Packet* packet = new sf::Packet();
		if (socket->receive(*packet) == sf::Socket::Done) {
			ChainLink* a = new ChainLink();
			a->object1 = (void *) packet;
			lastRecievedMessage->nextLink = a;
			lastRecievedMessage = a;
			}
		nanosleep(&tim, &tim2);
	}
	return 0;
}
void TcpClient::sendMsg(sf::Packet* packet) {
	ChainLink* a = new ChainLink();
	a->object1 = (void *) packet;
	lastToSendMessage->nextLink = a;
	lastToSendMessage = a;
}
void* TcpClient::runSender() {
	while (connected)
	{
		ChainLink* last = lastToSendMessage;
		while(lastSentMessage != last) {
			if (lastSentMessage->object1 != NULL) {
				sf::Packet* packet = static_cast<sf::Packet *>(lastSentMessage->object1);
				sf::TcpSocket::Status s = socket->send(*packet);
				if (s != sf::Socket::Done) {
					std::cout << "Couldn't send message TCP" <<std::endl;
				} else {
					//std::cout << "Sent TCP message" << std::endl;
				}
			}
			ChainLink* p = lastSentMessage;
			lastSentMessage = lastSentMessage->nextLink;
			p->nextLink = NULL; //Chop of the previous link so it can be disposed of
		}
		//Now process the last message recieved and null the object
		if (last->object1 != NULL) {
			sf::Packet* packet = static_cast<sf::Packet *>(last->object1);
			sf::TcpSocket::Status s = socket->send(*packet);
			
			if (s != sf::Socket::Done) {
				std::cout << "Couldn't send message TCP" <<std::endl;
			} else {
				//std::cout << "Sent TCP message" << std::endl;
			}
			
			last->object1 = NULL;
		}
		nanosleep(&tim, &tim2);
	}
	return 0;
}