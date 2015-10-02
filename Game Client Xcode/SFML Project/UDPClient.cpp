
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <iostream>

#include "UDPClient.h"

#include <time.h>

UdpClient::UdpClient(std::string i, int p, long d) {
	ip = i;
	port = p;
	
	connected = false;
	lastProcessedMessage = new ChainLink();
	lastRecievedMessage = lastProcessedMessage;
	
	lastSentMessage = new ChainLink();
	lastToSendMessage=lastSentMessage;
	
	//Set the time to delay thread,  0.5 seconds = 500000000L
	tim.tv_sec  = 0;
	tim.tv_nsec = d; //5000000L = 200 network updates per second
}
void UdpClient::start() {
	server = sf::IpAddress(ip);
	socket = new sf::UdpSocket();
	socket->bind(sf::Socket::AnyPort);
	socket->setBlocking(false);
	connected = true;
	
	pthread_create(&udpThreadListener, NULL, listener_helper, this);
	pthread_create(&udpThreadSender, NULL, sender_helper, this);
}
void UdpClient::stop() {
	connected = false;
	socket->unbind();
}
unsigned short int UdpClient::getPort() {
	return socket->getLocalPort();
}
ChainLink* UdpClient::getLastRecievedMessage() { return lastRecievedMessage; }
ChainLink* UdpClient::getLastProcessedMessage() { return lastProcessedMessage; }
void UdpClient::setLastProcessedMessage(ChainLink* c) {lastProcessedMessage=c;}
void* UdpClient::runListener() {
	// Endless loop that waits for new connections
	while (connected)
	{
		sf::Packet* packet = new sf::Packet();
		sf::IpAddress sender;
		unsigned short senderPort;
		while (socket->receive(*packet, sender, senderPort) == sf::Socket::Done) {
			if (sender.toInteger() == server.toInteger() && senderPort == port) {
				ChainLink* a = new ChainLink();
				a->object1 = (void *) packet;
				lastRecievedMessage->nextLink = a;
				lastRecievedMessage = a;
			}
			packet = new sf::Packet();
		}
		nanosleep(&tim, &tim2);
	}
	return 0;
}
void UdpClient::sendMsg(sf::Packet* packet) {
	ChainLink* a = new ChainLink();
	a->object1 = (void *) packet;
	lastToSendMessage->nextLink = a;
	lastToSendMessage = a;
}
void* UdpClient::runSender() {
	while (connected)
	{
		ChainLink* last = lastToSendMessage;
		while(lastSentMessage != last) {
			if (lastSentMessage->object1 != NULL) {
				sf::Packet* packet = static_cast<sf::Packet *>(lastSentMessage->object1);
				socket->send(*packet, server, port);
				
				//std::cout << "Sent UDP Packet: " << server.toString() << " port " << port << std::endl;
				//std::cout << "Sent UDP Packet" << std::endl;
			}
			ChainLink* p = lastSentMessage;
			lastSentMessage = lastSentMessage->nextLink;
			p->nextLink = NULL; //Chop of the previous link so it can be disposed of
		}
		//Now process the last message recieved and null the object
		if (last->object1 != NULL) {
			sf::Packet* packet = static_cast<sf::Packet *>(last->object1);
			socket->send(*packet, server, port);
			last->object1 = NULL;
			
			//std::cout << "Sent UDP Packet: " << server.toString() << " port " << port << std::endl;
			//std::cout << "Sent UDP Packet" << std::endl;
		}
		nanosleep(&tim, &tim2);
	}
	return 0;
}