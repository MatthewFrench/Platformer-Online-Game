//
//  Map.h
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_Map_h
#define Game_Server_Map_h

#include "Global.h"

#include "Block.h"
#include "Player.h"
#include "Cannon.h"
#include "PhysicsEngine.h"
#include "PacketID.h"
#include "Networking.h"

class Networking;
class Connection;
class PhysicsEngine;

class Map
{
protected:
	std::string mapName;
	int scale;
	float spawnX, spawnY;
	std::vector<Block*> blocks;
	std::map<int, Cannon*> cannons;
	std::map<int, Player*> players;
	PhysicsEngine* physicsEngine;
	Networking* networking;
	Player* clientPlayer;
	std::vector<sf::Texture*> gameGfx;
	float lowestX, highestX, lowestY, highestY;
	bool boundsSet;
public:
	Map(Networking* n);
	~Map();
	void logic();
	sf::Texture* loadTexture(std::string name);
	void draw(sf::RenderTarget* window);
	void addBlock(int graphic, float x, float y);
	void clearBlocks();
	void addPlayer(int entityID, std::string name, float x, float y, int deathCount, int winCount);
	void removePlayer(int entityID);
	void addCannon(int entityID, float x, float y, float angle, float xVel, float yVel, float size);
	void removeCannon(int entityID);
	void sendToTCP(sf::Packet* packet);
	void sendToUDP(sf::Packet* packet);
	float getSpawnX();
	float getSpawnY();
	int getScale();
	void setScale(int s);
	Cannon* getCannon(int eID);
	Player* getPlayer(int eID);
	void setClientPlayer(Player* p);
	std::map<int, Player*> getAllPlayers();
	sf::Texture* getGfx(int id);
	float getLowestX();
	float getLowestY();
	float getHighestX();
	float getHighestY();
private:
};

#endif
