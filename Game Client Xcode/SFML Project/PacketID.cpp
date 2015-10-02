//
//  PacketID.cpp
//  Game Server
//
//  Created by Matthew French on 1/4/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include "PacketID.h"

/*
sf::Packet* PacketID::Client::gpUdpPort(Networking* networking) {
	//std::cout << "Sent Connect" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::UdpPort;
	*p<<(unsigned short int)networking->getUdpPort();
	return p;
}
 */
sf::Packet* PacketID::Client::gpUdpConnect(Networking* networking) {
	//std::cout << "Sent Connect" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::UdpConnect;
	*p<<(uint32)networking->getClientID();
	return p;
}
sf::Packet* PacketID::Client::gpLogin(std::string name) {
	//std::cout << "Sent Login" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::Login;
	*p<<name;
	return p;
}
sf::Packet* PacketID::Client::gpRightArrow(bool pressed) {
	//std::cout << "Sent Right Arrow" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::RightArrow;
	*p<<pressed;
	return p;
}
sf::Packet* PacketID::Client::gpLeftArrow(bool pressed) {
	//std::cout << "Sent Left Arrow" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::LeftArrow;
	*p<<pressed;
	return p;
}
sf::Packet* PacketID::Client::gpUpArrow(bool pressed) {
	//std::cout << "Sent Up Arrow" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::UpArrow;
	*p<<pressed;
	return p;
}
sf::Packet* PacketID::Client::gpDownArrow(bool pressed) {
	//std::cout << "Sent Down Arrow" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::DownArrow;
	*p<<pressed;
	return p;
}
sf::Packet* PacketID::Client::gpSpaceBar(bool pressed) {
	//std::cout << "Sent Space bar" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::SpaceBar;
	*p<<pressed;
	return p;
}
sf::Packet* PacketID::Client::gpMouse(bool pressed) {
	//std::cout << "Sent Mouse" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::Mouse;
	*p<<pressed;
	return p;
}
sf::Packet* PacketID::Client::gpMousePos(float x, float y) {
	//std::cout << "Sent Mouse Pos" << std::endl;
	sf::Packet *p = new sf::Packet();
	*p<<(uint16)PacketID::Client::Packet::MousePos;
	*p << x << y;
	return p;
}







void PacketID::Server::ppClientID(sf::Packet* p, Networking* n) {
	uint32 clientID;
	*p >> clientID;
	//std::cout << "Recieved client ID: " << clientID << std::endl;
	n->beginUdpConnect(clientID);
}
void PacketID::Server::ppUdpConnected(sf::Packet* p, Networking* n) {
	//std::cout << "Recieved map scale" << std::endl;
	n->connectedToUdpAndTCP();
}
void PacketID::Server::ppMap(sf::Packet* p, Map* m) {
	//std::cout << "Recieved map scale" << std::endl;
	uint16 scale;
	*p >> scale;
	m->setScale(scale);
}
void PacketID::Server::ppClearBlocks(sf::Packet* p, Map* m) {
	//std::cout << "Recieved clear blocks" << std::endl;
	m->clearBlocks();
}
void PacketID::Server::ppTimeLeft(sf::Packet* p, ClientController* c) {
	//std::cout << "Recieved time left" << std::endl;
	uint32 timeLeft;
	*p >> timeLeft;
	c->setTimeLeft(timeLeft);
}
void PacketID::Server::ppBlock(sf::Packet* p, Map* m) {
	//std::cout << "Recieved block" << std::endl;
	float x, y;
	uint32 g;
	*p >> x >> y >> g;
	m->addBlock(g, x, y);
}
void PacketID::Server::ppCreateCannon(sf::Packet* p, Map* m) {
	//std::cout << "Recieved create cannon" << std::endl;
	float x, y, angle, xVel, yVel, size;
	uint32 eID;
	*p >> eID >> x >> y >> angle >> xVel >> yVel >> size;
	m->addCannon(eID, x, y, angle, xVel, yVel, size);
}
void PacketID::Server::ppCreatePlayer(sf::Packet* p, Map* m) {
	//std::cout << "Recieved create player" << std::endl;
	float x, y;
	std::string name;
	int deathCount, winCount;
	uint32 eID;
	*p >> eID >> x >> y >> name >> deathCount >> winCount;
	m->addPlayer(eID, name, x, y, deathCount, winCount);
}
void PacketID::Server::ppCannonPosUpdate(sf::Packet* p, Map* m) {
	//std::cout << "Recieved cannon pos update" << std::endl;
	uint32 eID;
	float x, y, angle, xVel, yVel, aVel;
	*p >> eID >> x >> y >> angle >> xVel >> yVel >> aVel;
	if (m != NULL) {
		Cannon* c = m->getCannon(eID);
		if (c != NULL) {
			c->setPosition(x, y, angle, xVel, yVel, aVel);
		}
	}
}
void PacketID::Server::ppPlayerPosUpdate(sf::Packet* p, Map* m) {
	//std::cout << "Recieved player pos update" << std::endl;
	uint32 eID;
	float x, y, xVel, yVel;
	*p >> eID >> x >> y >> xVel >> yVel;
	if (m != NULL) {
		Player* p = m->getPlayer(eID);
		if (p != NULL) {
			p->setPosition(x, y, xVel, yVel);
		}
	}
}
void PacketID::Server::ppPlayerUltiUpdate(sf::Packet* p, Map* m) {
	//std::cout << "Recieved player ulti update" << std::endl;
	uint32 eID, ultimateTimer, ultimateTimerMax;
	*p >> eID >> ultimateTimer >> ultimateTimerMax;
	if (m != NULL) {
		Player* p = m->getPlayer(eID);
		if (p != NULL) {
			p->setUltiCount(ultimateTimer);
			p->setUltiCount(ultimateTimerMax);
		}
	}
}
void PacketID::Server::ppPlayerInAirUpdate(sf::Packet* p, Map* m) {
	//std::cout << "Recieved player in air update" << std::endl;
	uint32 eID;
	bool inAir;
	*p >> eID >> inAir;
	if (m != NULL) {
		Player* p = m->getPlayer(eID);
		if (p != NULL) {
			//std::cout << "In Air: " << inAir <<std::endl;
			p->setInAir(inAir);
		}
	}
}
void PacketID::Server::ppPlayerDeathCount(sf::Packet* p, Map* m) {
	//std::cout << "Recieved player death count" << std::endl;
	uint32 eID, deathCount;
	*p >> eID >> deathCount;
	if (m != NULL) {
		Player* p = m->getPlayer(eID);
		if (p != NULL) {
			p->setDeathCount(deathCount);
		}
	}
}
void PacketID::Server::ppPlayerWinCount(sf::Packet* p, Map* m) {
	//std::cout << "Recieved player win count" << std::endl;
	uint32 eID, winCount;
	*p >> eID >> winCount;
	if (m != NULL) {
		Player* p = m->getPlayer(eID);
		if (p != NULL) {
			p->setWinCount(winCount);
		}
	}
}
void PacketID::Server::ppPlayerSelf(sf::Packet* p, Map* m, ClientController* c) {
	//std::cout << "Recieved Player Self" << std::endl;
	uint32 eID;
	*p >> eID;
	if (m != NULL) {
		//std::cout << "Map is not null" << std::endl;
		Player* p = m->getPlayer(eID);
		if (p != NULL) {
			//std::cout << "Player is not null" << std::endl;
			m->setClientPlayer(p);
			c->setPlayer(p);
		}
	}
}
void PacketID::Server::ppDeletePlayer(sf::Packet* p, Map* m) {
	//std::cout << "Recieved delete player" << std::endl;
	uint32 eID;
	*p >> eID;
	if (m != NULL) {
		m->removePlayer(eID);
	}
}
void PacketID::Server::ppDeleteCannon(sf::Packet* p, Map* m) {
	//std::cout << "Recieved delete cannon" << std::endl;
	uint32 eID;
	*p >> eID;
	if (m != NULL) {
		m->removeCannon(eID);
	}
}