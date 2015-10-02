//
//  PhysicsEngine.cpp
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {
	velocityIterations = 10;
	positionIterations = 10;
	precision = 2; //Great precision = less performance
	//Problem with precision, it's like velocities get lowered the smaller steps taken
	WORLD_BITS =          0x0001;
	PLAYER_BITS=     0x0002;
	ULTIMATE_BITS =        0x0004;
	
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
    world = new b2World(gravity);
    world->SetAutoClearForces(false);
}
PhysicsEngine::~PhysicsEngine() {
	
}
void PhysicsEngine::logic() {
	for (int i = 0; i < precision; i++) {
		world->Step(1.0f / fps / ((float)precision), velocityIterations, positionIterations);
	}
	world->ClearForces();
}
void PhysicsEngine::makeBodyForPlayer(Player* p, float x, float y) {
	b2Body* b = makeCircle(x, y, 24, true, 0.5f , 1.0f, 0.0f, PLAYER_BITS, PLAYER_BITS | ULTIMATE_BITS | WORLD_BITS);
    b->SetUserData(p);
	
	p->setPhysicsBody(b);
}
void PhysicsEngine::makeBodyForCannon(Cannon* c, float x, float y, float angle, float size) {
	if (c->getSize() > 30) {
        c->setPhysicsBody( makeCircle(x,y, angle, size, false, 1.0f, 20.0f, 1.0f, ULTIMATE_BITS, PLAYER_BITS) );
        c->getPhysicsBody()->SetGravityScale(0.0f);
    } else {
		c->setPhysicsBody( makeCircle(x,y, angle, size, false, 0.05f, 3.0f, 0, WORLD_BITS, PLAYER_BITS | WORLD_BITS) );
    }
    c->getPhysicsBody()->SetUserData(c);
}
void PhysicsEngine::makeBodyForBlock(Block* b) {
	b->setPhysicsBody( makeStaticBox(b->getX(),b->getY(),b->getMap()->getScale(),b->getMap()->getScale(), 0.5f, WORLD_BITS, PLAYER_BITS | WORLD_BITS) );
}
void PhysicsEngine::removeBody(b2Body* b) {
	if (b != NULL) {
		world->DestroyBody( b );
	}
}
b2Body* PhysicsEngine::makeCircle(float x,float y, float angle, float r, bool fixedRotation, float f, float d, float restitution, int categoryBits, int maskBits) {
	b2BodyDef* bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody; // dynamic means it is subject to forces
    bodyDef->position.Set(x, y);
    bodyDef->angle = angle;
    bodyDef->fixedRotation = fixedRotation;
    b2Body* body = world->CreateBody(bodyDef);
    
    b2FixtureDef* fd = new b2FixtureDef();
	b2CircleShape* cd = new b2CircleShape();
	cd->m_radius = r/2.0f/pixelPerMeter;
	fd->shape = cd;
	fd->density = d;
	fd->restitution = restitution;
	fd->friction = f;
	
	//fd->filter.categoryBits = categoryBits;
	//fd->filter.maskBits = maskBits;
	
	body->CreateFixture(fd);
    
    return body;
}
b2Body* PhysicsEngine::makeCircle(float x,float y,float r, bool fixedRotation, float friction, float d, float restitution,  int categoryBits, int maskBits) {
	return makeCircle( x, y, 0.0f,  r,  fixedRotation, friction, d, restitution, categoryBits, maskBits);
}
b2Body* PhysicsEngine::makeStaticBox(float x,float y,float w,float h, float friction, int categoryBits, int maskBits) {
	b2BodyDef bodyDef; // body definition
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(x/pixelPerMeter, (gameHeight-y)/pixelPerMeter); // set bodydef position
	
	b2Body* body = world->CreateBody(&bodyDef); // create body based on definition
	b2PolygonShape* polyShape = new b2PolygonShape(); // make a shape representing ground
	polyShape->SetAsBox(w/2.0f/pixelPerMeter, h/2.0f/pixelPerMeter); // shape is a rect: 100 wide, 20 high
	b2FixtureDef* fd = new b2FixtureDef();
	fd->shape = polyShape; fd->density = 0.0f;fd->friction = friction;
	//fd->filter.categoryBits = categoryBits;
	//fd->filter.maskBits = maskBits;
	body->CreateFixture(fd); // bind shape to ground body
	
	return body;
}
b2Fixture* PhysicsEngine::addJumpSensor(b2Body* body, float s) {
	b2FixtureDef* fd = new b2FixtureDef();
    b2PolygonShape* polyShape = new b2PolygonShape(); // make a shape representing ground
    polyShape->SetAsBox(4.0f/pixelPerMeter, 6.0f/pixelPerMeter, b2Vec2(0.0f,-s/2.0f/pixelPerMeter), 0);
    fd->shape = polyShape;
    fd->isSensor = true;
    //fd->filter.categoryBits = PLAYER_BITS;
    //fd->filter.maskBits = PLAYER_BITS | WORLD_BITS;
    return body->CreateFixture(fd); // bind shape to ground body
}