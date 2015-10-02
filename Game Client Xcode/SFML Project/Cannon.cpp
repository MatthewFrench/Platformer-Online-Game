//
//  Cannon.cpp
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include "Cannon.h"

Cannon::Cannon(int eID, Map* m, float s) {
	entityID = eID;
	physicsBody = NULL;
	map = m;
	size = s;
	sprite = new sf::Sprite();
	if (size == 30) {
		sprite->setTexture( *(map->getGfx(2)) );
    } else {
		sprite->setTexture( *(map->getGfx(5)) );
	}
	sprite->setOrigin(sprite->getTexture()->getSize().x / 2.0f, sprite->getTexture()->getSize().y / 2.0f);
}
Cannon::~Cannon() {
	
}
void Cannon::draw(sf::RenderTarget* window) {
	//std::cout<< "Drawin Cannon: " << getX() << ", " << getY() << std::endl;
	sprite->setPosition(getX(), getY());
	sprite->setRotation(getAngle()*180.0f/3.14159f);
	window->draw(*sprite);
	//pushMatrix();
	//translate(getX(), getY());
	//rotate(getAngle());
	//image(img, -size/2.0, -size/2.0);
    //popMatrix();
}
float Cannon::getX() {
    b2Vec2 position = physicsBody->GetPosition();
    return position.x*pixelPerMeter;
}
float Cannon::getY() {
    b2Vec2 position = physicsBody->GetPosition();
    return gameHeight-position.y*pixelPerMeter;
}
float Cannon::getAngle() {
	return physicsBody->GetAngle();
}
b2Body* Cannon::getPhysicsBody() {
	return physicsBody;
}
void Cannon::setPhysicsBody(b2Body* b) {
	physicsBody = b;
}
float Cannon::getSize() {
	return size;
}
void Cannon::setSize(float s) {
	size = s;
}
void Cannon::setPosition(float x, float y, float angle, float xVel, float yVel, float aVel) {
	physicsBody->SetTransform( b2Vec2(x, y), angle);
    physicsBody->SetLinearVelocity( b2Vec2(xVel, yVel));
    physicsBody->SetAngularVelocity(aVel);
}