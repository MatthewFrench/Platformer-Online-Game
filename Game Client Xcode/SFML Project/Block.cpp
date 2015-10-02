//
//  Block.cpp
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include "Block.h"

Block::Block(Map* m, int g) {
	graphic = g;
	map = m;
	physicsBody = NULL;
	x = 0;
	y = 0;
	sprite = new sf::Sprite();
	//final int BLOCK_GFX_NONE = 0, BLOCK_GFX_GRASS = 1, BLOCK_GFX_TILE = 2;
	if (graphic == 1) {
		sprite->setTexture(*(map->getGfx(1)));
	}
	if (graphic == 2) {
		sprite->setTexture(*(map->getGfx(0)));
	}
	sprite->setOrigin(sprite->getTexture()->getSize().x / 2.0f, sprite->getTexture()->getSize().y / 2.0f);
}
Block::~Block() {
	
}
void Block::setGraphic(int g) {
	graphic = g;
}
int Block::getGraphic() {
	return graphic;
}
void Block::setPhysicsBody(b2Body* b) {
	physicsBody = b;
}
b2Body* Block::getPhysicsBody() {
	return physicsBody;
}
void Block::setPosition(float xp, float yp) {
	x = xp;
	y = yp;
	sprite->setPosition(xp, yp);
}
float Block::getX() {
	return x;
}
float Block::getY() {
	return y;
}
void Block::draw(sf::RenderTarget* window) {
	window->draw(*sprite);
}
Map* Block::getMap() {
	return map;
}