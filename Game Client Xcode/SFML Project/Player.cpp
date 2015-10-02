//
//  Player.cpp
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include "Player.h"

Player::Player(int eID, std::string n, Map* m) {
	entityID = eID;
	name = n;
	map = m;
	ultiCount = 0;
	ultiCountMax = 0;
	deathCount = 0;
	winCount = 0;
	sprite = new sf::Sprite();
	spriteJump = new sf::Sprite();
	sprite->setTexture( *(map->getGfx(3)) );
	spriteJump->setTexture( *(map->getGfx(4)) );
	sprite->setOrigin(sprite->getTexture()->getSize().x / 2.0f, sprite->getTexture()->getSize().y / 2.0f);
	spriteJump->setOrigin(sprite->getTexture()->getSize().x / 2.0f, sprite->getTexture()->getSize().y / 2.0f);
	
#if defined(SFML_SYSTEM_MACOS)
	font.loadFromFile(resourcePath() + "sansation.ttf");
#else
	font.loadFromFile("sansation.ttf");
#endif
}
Player::~Player() {
	
}
void Player::draw(sf::RenderTarget* window) {
	sprite->setPosition(getX(), getY());
	spriteJump->setPosition(getX(), getY());
	
	if (ultiCount > 0) {ultiCount -= 1;}
    //textAlign(CENTER);
    //if (map.clientPlayer == this) {
	//	fill(255);
    //} else {
	//	if (map.clientPlayer.ultiCount != 0) {
	//		fill(255, 0, 0);
	//	} else {
	//		fill(0, 255, 0);
	//	}
    //}
	sf::Text text(name, font);
	text.setColor(sf::Color::White);
	text.setPosition(getX(), round(getY())-50);
	text.setOrigin(text.getLocalBounds().width/2 ,0);
	window->draw(text);
    //text(name,floor(getX()),floor(getY())-25);
    if (!inAir) {
		window->draw(*sprite);
	//	image(img, getX()-32/2.0, getY()-32/2.0);
    } else {
		window->draw(*spriteJump);
	//	image(imgJump, getX()-32/2.0, getY()-32/2.0);
    }
    //rectMode(CORNER);
    //if (ultiCountMax != 0) {
	//	if (ultiCount !=0) {stroke(0);}else{stroke(255);}
	//	fill(0);
	//	rect(floor(getX()-25), floor(getY()+20), 50, 8);
	//	if (ultiCount !=0) {
	//		fill(255,0,0);
	//	} else {fill(0,255,0);}
	//	rect(floor(getX()-25), floor(getY()+20), 50*((float)(ultiCountMax-ultiCount))/((float)ultiCountMax), 8);
    //}
}
float Player::getX() {
	b2Vec2 position = physicsBody->GetPosition();
    return position.x*pixelPerMeter;
}
float Player::getY() {
	b2Vec2 position = physicsBody->GetPosition();
    return gameHeight-position.y*pixelPerMeter;
}
void Player::setPosition(float x, float y, float xVel, float yVel) {
	//std::cout << "Set player's position " << x << ", " << y << std::endl;
	physicsBody->SetTransform( b2Vec2(x, y), physicsBody->GetAngle());
    physicsBody->SetLinearVelocity( b2Vec2(xVel, yVel));
}
b2Body* Player::getPhysicsBody() {
	return physicsBody;
}
void Player::setPhysicsBody(b2Body* b) {
	physicsBody = b;
}
void Player::setDeathCount(int d) {
	deathCount = d;
}
void Player::setWinCount(int w) {
	winCount = w;
}
void Player::setUltiCount(int u) {
	ultiCount = u;
}
void Player::setUltiCountMax(int u) {
	ultiCountMax = u;
}
void Player::setInAir(bool i) {
	inAir = i;
}