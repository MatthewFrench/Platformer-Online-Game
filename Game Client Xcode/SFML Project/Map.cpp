//
//  Map.cpp
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include "Map.h"

Map::Map(Networking* n) {
	networking = n;
	physicsEngine = new PhysicsEngine();
	clientPlayer = false;
	
	gameGfx.push_back( loadTexture("wall1.png") );
	gameGfx.push_back( loadTexture("ground.png") );
	gameGfx.push_back( loadTexture("Cannon.png") );
	gameGfx.push_back( loadTexture("player1.png") );
	gameGfx.push_back( loadTexture("player2.png") );
	gameGfx.push_back( loadTexture("Cannon Large.png") );
}
sf::Texture* Map::loadTexture(std::string name) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(resourcePath() + name))
	    return NULL;
	texture->setSmooth(true);
	return texture;
}
sf::Texture* Map::getGfx(int id) {
	return gameGfx[id];
}
Map::~Map() {
	
}
void Map::logic() {
	physicsEngine->logic();
}
void Map::draw(sf::RenderTarget* window) {
	for (int i = 0; i < blocks.size(); i++) {
		Block* b = blocks[i];
		b->draw(window);
    }
	for( std::map<int, Cannon*>::iterator ii=cannons.begin(); ii!=cannons.end(); ++ii) {
		Cannon* c = ii->second;
		//if (c != NULL) {
			c->draw(window);
		//}
	}
	for( std::map<int, Player*>::iterator ii=players.begin(); ii!=players.end(); ++ii) {
		Player* p = ii->second;
		//if (p != NULL) {
			p->draw(window);
		//}
	}
}
void Map::addBlock(int graphic, float x, float y) {
	Block* b = new Block(this, graphic);
    b->setPosition(x, y);
    physicsEngine->makeBodyForBlock(b);
    blocks.push_back(b);
	if (!boundsSet) {
		boundsSet = true;
		lowestX = x, highestX = x, lowestY = y, highestY = y;
	} else {
		if (x < lowestX) {lowestX = x;}
		if (x > highestX) {highestX = x;}
		if (y < lowestY) {lowestY = y;}
		if (y > highestY) {highestY = y;}
	}
}
void Map::clearBlocks() {
	for (int i = 0; i < blocks.size(); i++) {
		physicsEngine->removeBody(blocks[i]->getPhysicsBody());
	}
	blocks.clear();
	lowestX = 0, highestX = 0, lowestY = 0, highestY = 0;
	boundsSet = false;
}
void Map::addPlayer(int entityID, std::string name, float x, float y, int deathCount, int winCount) {
	if (getPlayer(entityID) == NULL) {
		Player* p = new Player(entityID, name, this);
		p->setDeathCount( deathCount );
		p->setWinCount( winCount );
		physicsEngine->makeBodyForPlayer(p, x, y);
		players.insert(std::pair<int,Player*>(entityID, p));
	}
}
void Map::removePlayer(int entityID) {
	Player* p = NULL;
	if (players.find(entityID) != players.end()) {
		p = players.find(entityID)->second;
	}
    if (p != NULL) {
		players.erase(players.find(entityID));
		physicsEngine->removeBody(p->getPhysicsBody());
    }
}
void Map::addCannon(int entityID, float x, float y, float angle, float xVel, float yVel, float size) {
	if (getCannon(entityID) == NULL) {
		Cannon* c = new Cannon(entityID, this, size);
		physicsEngine->makeBodyForCannon(c, x, y, angle, size);
		cannons.insert(std::pair<int,Cannon*>(entityID, c));
		//std::cout << "Vel " << xVel << " , " << yVel << std::endl;
		c->getPhysicsBody()->ApplyForce(b2Vec2(xVel,yVel), c->getPhysicsBody()->GetWorldCenter(), true);
	}
}
void Map::removeCannon(int entityID) {
	Cannon* c = NULL;
	if (cannons.find(entityID) != cannons.end()) {
		c = cannons.find(entityID)->second;
	}
    if (c != NULL) {
		cannons.erase(cannons.find(entityID));
		physicsEngine->removeBody(c->getPhysicsBody());
		//std::cout << cannons[entityID] << std::endl;
    }
}
float Map::getSpawnX() {
	return spawnX;
}
float Map::getSpawnY() {
	return spawnY;
}
int Map::getScale() {
	return scale;
}
void Map::sendToTCP(sf::Packet* packet) {
	networking->sendTcp(packet);
}
void Map::sendToUDP(sf::Packet* packet) {
	networking->sendUdp(packet);
}
void Map::setScale(int s) {
	scale = s;
}
Cannon* Map::getCannon(int eID) {
	if (cannons.find(eID) != cannons.end()) {
		return cannons.find(eID)->second;
	}
	return NULL;
}
Player* Map::getPlayer(int eID) {
	if (players.find(eID) != players.end()) {
		return players.find(eID)->second;
	}
	return NULL;
}
void Map::setClientPlayer(Player* p) {
	clientPlayer = p;
}
std::map<int, Player*> Map::getAllPlayers() {
	return players;
}
float Map::getLowestX() {
	return lowestX;
}
float Map::getLowestY() {
	return lowestY;
}
float Map::getHighestX() {
	return highestX;
}
float Map::getHighestY() {
	return highestY;
}