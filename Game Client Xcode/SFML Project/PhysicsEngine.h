//
//  PhysicsEngine.h
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_PhysicsEngine_h
#define Game_Server_PhysicsEngine_h

#include "Global.h"

#include "Block.h"
#include "Player.h"
#include "Cannon.h"

class Player;
class Cannon;
class Block;

class PhysicsEngine
{
protected:
	b2World* world;
	int velocityIterations;
	int positionIterations;
	
	int precision;
	
	int WORLD_BITS;
	int PLAYER_BITS;
	int ULTIMATE_BITS;
public:
	PhysicsEngine();
	~PhysicsEngine();
	void logic();
	void makeBodyForPlayer(Player* p, float x, float y);
	void makeBodyForCannon(Cannon* c, float x, float y, float angle, float size);
	void makeBodyForBlock(Block* b);
	void removeBody(b2Body* b);
	b2Body* makeCircle(float x,float y, float angle, float r, bool fixedRotation, float f, float d, float restitution, int categoryBits, int maskBits);
	b2Body* makeCircle(float x,float y,float r, bool fixedRotation, float friction, float d, float restitution,  int categoryBits, int maskBits);
	b2Body* makeStaticBox(float x,float y,float w,float h, float friction, int categoryBits, int maskBits);
	b2Fixture* addJumpSensor(b2Body* body, float s);
private:
	
};

#endif
