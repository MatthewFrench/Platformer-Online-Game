//
//  Player.h
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_Player_h
#define Game_Server_Player_h

#include "Global.h"

#include "Cannon.h"
#include "Map.h"
#include "PacketID.h"

class Map;

class Player
{
protected:
	int entityID;
	bool inAir;
	b2Body* physicsBody;
	std::string name;
	int ultiCount, ultiCountMax;
	Map* map;
	int deathCount, winCount;
	sf::Sprite* sprite, *spriteJump;
	sf::Font font;
public:
	Player(int eID, std::string n, Map* m);
	~Player();
	void draw(sf::RenderTarget* window);
	float getX();
	float getY();
	void setPosition(float x, float y, float xVel, float yVel);
	b2Body* getPhysicsBody();
	void setPhysicsBody(b2Body* b);
	void setDeathCount(int d);
	void setWinCount(int w);
	void setUltiCount(int u);
	void setUltiCountMax(int u);
	void setInAir(bool i);
private:
	
};

#endif
