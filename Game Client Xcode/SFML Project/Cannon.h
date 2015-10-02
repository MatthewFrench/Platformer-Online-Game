//
//  Cannon.h
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_Cannon_h
#define Game_Server_Cannon_h

#include "Global.h"

#include "Map.h"
#include "PacketID.h"

class Map;

class Cannon
{
protected:
	int entityID;
	b2Body* physicsBody;
	Map* map;
	float size;
	sf::Sprite* sprite;
public:
	Cannon(int eID, Map* m, float s);
	~Cannon();
	void draw(sf::RenderTarget* window);
	float getX();
	float getY();
	float getAngle();
	b2Body* getPhysicsBody();
	void setPhysicsBody(b2Body* b);
	float getSize();
	void setSize(float s);
	int getEntityID();
	void setPosition(float x, float y, float angle, float xVel, float yVel, float aVel);
private:
	
};

#endif
