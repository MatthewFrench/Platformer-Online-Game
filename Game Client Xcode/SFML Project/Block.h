//
//  Block.h
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_Block_h
#define Game_Server_Block_h

#include "Global.h"

#include "Map.h"

class Map;

class Block
{
protected:
	Map* map;
	b2Body* physicsBody;
	float x, y;
	int graphic;
	sf::Sprite* sprite;
public:
	Block(Map* m, int g);
	~Block();
	void setGraphic(int g);
	int getGraphic();
	void setPosition(float xp, float yp);
	float getX();
	float getY();
	void setPhysicsBody(b2Body* b);
	b2Body* getPhysicsBody();
	void draw(sf::RenderTarget* window);
	Map* getMap();
private:
	
};

#endif
