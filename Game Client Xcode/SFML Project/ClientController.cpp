//
//  ServerController.cpp
//  Game Server
//
//  Created by Matthew French on 1/2/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#include "ClientController.h"

ClientController::ClientController() {
	map = new Map(networking);
	player = NULL;
	mouseDown = false;
	rightArrow = false;
	leftArrow = false;
	downArrow = false;
	upArrow = false;
	spaceBar = false;
	connected = false;
	
	networking = new Networking();
	networking->setCallback(this);
	networking->start();
	delta = 0.0f;
	cameraView = new sf::View();
	cameraView->reset(sf::FloatRect(0, 0, gameWidth, gameHeight));
	mapView = new sf::View();
	mapView->reset(sf::FloatRect(0, 0, gameWidth, gameHeight));
	//mapView->reset(sf::FloatRect(gameWidth - 100 - 10, gameHeight - 100 - 10, 100, 100));
	mapView->setViewport(sf::FloatRect(0.79f, 0.79f, 0.2f, 0.2f));
	//texture = new sf::RenderTexture();
	//texture->create(gameWidth, gameHeight);
	//texture->setSmooth(true);
	
	rectangle = new sf::RectangleShape();
	rectangle->setSize(sf::Vector2f(200, 140));
	rectangle->setOutlineColor(sf::Color::Black);
	rectangle->setOutlineThickness(5);
	rectangle->setPosition(gameWidth - 210, gameHeight - 147);
	
#if defined(SFML_SYSTEM_MACOS)
	font.loadFromFile(resourcePath() + "sansation.ttf");
#else
	font.loadFromFile("sansation.ttf");
#endif
}
ClientController::~ClientController() {
	networking->stop();
}
void ClientController::logic() {
	networking->processMessages();
	
	if (player != NULL) {
		map->logic();
	}
	
	//Track time between logic calls
	delta = clock.restart().asSeconds();
	//std::cout << to_string(1.0/delta)+"\n";
}
void ClientController::draw(sf::RenderTarget* window) {
	if (player != NULL) {
		window->clear(sf::Color(100,100,255, 255));

		//cameraView->setCenter(getCameraX(),getCameraY());
		//window->setView(*cameraView);
		cameraView->setCenter(getCameraX(),getCameraY());
		window->setView(*cameraView);
        map->draw(window);
		window->setView(window->getDefaultView());
		window->draw(*rectangle);
		
		//Gamewidth/gameheight ratio
		float ratio1 = gameWidth/gameHeight;
		float width = map->getHighestX() - map->getLowestX();
		float height = map->getHighestY() - map->getLowestY();
		float ratio2 = width/height;
		float newWidth = 0;
		float newHeight = 0;
		float offsetX = 0;
		float offsetY = 0;
		if (ratio2 > ratio1) {
			newHeight = ratio2 / ratio1 * height;
			newWidth = width;
			offsetY = (height - newHeight)/2;
		} else {
			newWidth = width / (ratio2 / ratio1);
			newHeight = height;
			offsetX = (width - newWidth)/2;
		}
		mapView->setSize(newWidth, newHeight);
		mapView->setCenter(map->getLowestX()+mapView->getSize().x/2.0f + offsetX,map->getLowestY()+mapView->getSize().y/2.0f + offsetY);
		window->setView(*mapView);
		map->draw(window);
		window->setView(window->getDefaultView());
	} else {
		window->clear(sf::Color(0, 0, 0, 255));
        //background(0);
		//fill(255);
		//textAlign(LEFT);
		if (connected) {
			//fill(0,255,0);ellipse(30,93,20,20);fill(255);text("Online", 60,100);
		} else {
			//fill(255,0,0);ellipse(30,93,20,20);fill(255);text("Offline", 60,100);
		}
	}
	
	//textAlign(LEFT);
	//fill(255);
	//text(frameRate,15,20);
	//fill(200);
	//text(int(frameRate),20,60);
	
	if (player != NULL) {
        //textAlign(CENTER);
        //fill(255);
		std::stringstream s;
		s << "Time: " << floor((mapRotaterTimeLeft- (mapRotaterClock.getElapsedTime().asMilliseconds()))/1000);
		sf::Text text(s.str(), font);
		text.setColor(sf::Color::White);
		text.setPosition(gameWidth/2.0f, 30);
		text.setOrigin(text.getLocalBounds().width/2 ,0);
		window->draw(text);
        //text("Time: "+ floor((mapRotaterTimeLeft- (System.currentTimeMillis()-mapRotaterSince))/1000), width/2.0, 30);
        
        //Draw score board
        //textFont(fontArial, 10);
        //stroke(150,150,150,180);
        //fill(0,0,0,180);
        //rectMode(CORNER);
        //rect(width-210, 10, 200, 20 + 20*map.players.size());
        //fill(255);
        //textAlign(LEFT);
        //text("Name", width-210+13, 22); text("Deaths", width-210+110, 22);  text("Wins", width-210+160, 22);
        //line(width-210+10, 25, width-210+185, 25);
		
        //for (int i = 0; i< map.players.size(); i++) {
		//	Player p = map.players.get(i);
			//int y = 40+20*i;
			//String n = p.name;
			//if (n.length() > 18) {n = n.substring(0,18);}
			//text(n, width-210+13, y);
			//text(p.deathCount, width-210+120, y);
			//text(p.winCount, width-210+165, y);
        //}
	}
	//textFont(fontArial, 20);
}

void ClientController::onConnect() {
	std::cout << "Connected" << std::endl;
	connected = true;
	login();
}
void ClientController::onDisconnect() {
	std::cout << "Disconnected" << std::endl;
	connected = false;
}
void ClientController::onMessage(sf::Packet* p) {
	uint16 id;
	*p >> id;
	//std::cout << "Recieved Message: " << id << std::endl;
	switch (id) {
		case PacketID::Server::Packet::ClientID : {
			PacketID::Server::ppClientID(p, networking);
			//std::cout << "Recieved Client ID" <<std::endl;
			break;
		}
		case PacketID::Server::Packet::UdpConnected : {
			PacketID::Server::ppUdpConnected(p, networking);
			//std::cout << "UDP Connection Established" <<std::endl;
			break;
		}
		case PacketID::Server::Packet::Map : {
			PacketID::Server::ppMap(p, map);
			break;
		}
		case PacketID::Server::Packet::ClearBlocks : {
			PacketID::Server::ppClearBlocks(p, map);
			break;
		}
		case PacketID::Server::Packet::TimeLeft : {
			PacketID::Server::ppTimeLeft(p, this);
			break;
		}
		case PacketID::Server::Packet::Block : {
			PacketID::Server::ppBlock(p, map);
			break;
		}
		case PacketID::Server::Packet::CreateCannon : {
			PacketID::Server::ppCreateCannon(p, map);
			break;
		}
		case PacketID::Server::Packet::CreatePlayer : {
			PacketID::Server::ppCreatePlayer(p, map);
			break;
		}
		case PacketID::Server::Packet::CannonPosUpdate : {
			PacketID::Server::ppCannonPosUpdate(p, map);
			break;
		}
		case PacketID::Server::Packet::PlayerPosUpdate : {
			//std::cout << "Got player position update" << std::endl;
			PacketID::Server::ppPlayerPosUpdate(p, map);
			break;
		}
		case PacketID::Server::Packet::PlayerUltiUpdate : {
			PacketID::Server::ppPlayerUltiUpdate(p, map);
			break;
		}
		case PacketID::Server::Packet::PlayerInAirUpdate : {
			PacketID::Server::ppPlayerInAirUpdate(p, map);
			break;
		}
		case PacketID::Server::Packet::PlayerDeathCount : {
			PacketID::Server::ppPlayerDeathCount(p, map);
			break;
		}
		case PacketID::Server::Packet::PlayerWinCount : {
			PacketID::Server::ppPlayerWinCount(p, map);
			break;
		}
		case PacketID::Server::Packet::PlayerSelf : {
			PacketID::Server::ppPlayerSelf(p, map, this);
			break;
		}
		case PacketID::Server::Packet::DeletePlayer : {
			PacketID::Server::ppDeletePlayer(p, map);
			break;
		}
		case PacketID::Server::Packet::DeleteCannon : {
			PacketID::Server::ppDeleteCannon(p, map);
			break;
		}
	}
}
void ClientController::login() {
	/*
	 if (cp5.get(Textfield.class,"Username").getText().length() > 0) {
	 String name = cp5.get(Textfield.class,"Username").getText();
	 cp5.get(Textfield.class,"Username").clear();
	 cp5.remove("Username");
	 cp5.remove("login");
	 CM_Login login = new CM_Login();
	 login.name = name;
	 client.sendTCP(login);
	 }
	 */
	networking->sendTcp(PacketID::Client::gpLogin("Gan"));
}
void ClientController::pressedRight() {
	if (!rightArrow && player != NULL) {
		rightArrow = true;
		networking->sendTcp(PacketID::Client::gpRightArrow(rightArrow));
		networking->sendUdp(PacketID::Client::gpRightArrow(rightArrow));
	}
}
void ClientController::pressedUp() {
	if (!upArrow && player != NULL) {
		upArrow = true;
		networking->sendTcp(PacketID::Client::gpUpArrow(upArrow));
		networking->sendUdp(PacketID::Client::gpUpArrow(upArrow));
	}
}
void ClientController::pressedLeft() {
	if (!leftArrow && player != NULL) {
		leftArrow = true;
		networking->sendTcp(PacketID::Client::gpLeftArrow(leftArrow));
		networking->sendUdp(PacketID::Client::gpLeftArrow(leftArrow));
	}
}
void ClientController::pressedDown() {
	if (!downArrow && player != NULL) {
		downArrow = true;
		networking->sendTcp(PacketID::Client::gpDownArrow(downArrow));
		networking->sendUdp(PacketID::Client::gpDownArrow(downArrow));
	}
}
void ClientController::pressedSpace() {
	if (!spaceBar && player != NULL) {
		spaceBar = true;
		networking->sendTcp(PacketID::Client::gpSpaceBar(spaceBar));
		networking->sendUdp(PacketID::Client::gpSpaceBar(spaceBar));
	}
}
void ClientController::releasedRight() {
	if (rightArrow && player != NULL) {
		rightArrow = false;
		networking->sendTcp(PacketID::Client::gpRightArrow(rightArrow));
		networking->sendUdp(PacketID::Client::gpRightArrow(rightArrow));
	}
}
void ClientController::releasedUp() {
	if (upArrow && player != NULL) {
		upArrow = false;
		networking->sendTcp(PacketID::Client::gpUpArrow(upArrow));
		networking->sendUdp(PacketID::Client::gpUpArrow(upArrow));
	}
}
void ClientController::releasedLeft() {
	if (leftArrow && player != NULL) {
		leftArrow = false;
		networking->sendTcp(PacketID::Client::gpLeftArrow(leftArrow));
		networking->sendUdp(PacketID::Client::gpLeftArrow(leftArrow));
	}
}
void ClientController::releasedDown() {
	if (downArrow && player != NULL) {
		downArrow = false;
		networking->sendTcp(PacketID::Client::gpDownArrow(downArrow));
		networking->sendUdp(PacketID::Client::gpDownArrow(downArrow));
	}
}
void ClientController::releasedSpace() {
	if (spaceBar && player != NULL) {
		spaceBar = false;
		networking->sendTcp(PacketID::Client::gpSpaceBar(spaceBar));
		networking->sendUdp(PacketID::Client::gpSpaceBar(spaceBar));
	}
}
void ClientController::pressedMouse(float x, float y) {
	if (player != NULL && !mouseDown) {
		mouseDown = true;
		mouseX = x;
		mouseY = y;
		networking->sendTcp(PacketID::Client::gpMousePos(getMouseXRelativeToPlayer(), getMouseYRelativeToPlayer()));
		networking->sendTcp(PacketID::Client::gpMouse(mouseDown));
	}
}
void ClientController::releasedMouse() {
	if (player != NULL) {
		mouseDown = false;
		networking->sendTcp(PacketID::Client::gpMouse(mouseDown));
	}
}
void ClientController::draggedMouse(float x, float y) {
	if (player != NULL && mouseDown) {
		mouseX = x;
		mouseY = y;
		networking->sendUdp(PacketID::Client::gpMousePos(getMouseXRelativeToPlayer(), getMouseYRelativeToPlayer()));
			//std::cout << "MouseX: " << getMouseXRelativeToPlayer() << " MouseY: " << getMouseYRelativeToPlayer() << std::endl;
	}
}
//Player is always in the middle of the screen
int ClientController::getMouseXRelativeToPlayer() {
	return mouseX-gameWidth/2.0f;
	//return floorf(-(player->getX()-(mouseX-getCameraX()))+32.0f/2.0f);
}
int ClientController::getMouseYRelativeToPlayer() {
	return mouseY-gameHeight/2.0f;
	//return floorf(-(player->getY()-(mouseY-getCameraY()))+32.0f/2.0f);
}
float ClientController::getCameraX() {
	//float cameraX = floorf(-player->getX()+gameWidth/2.0f);
	//if (cameraX > 0+cameraFluffX) {cameraX = 0+cameraFluffX;}
	//if (cameraX < -map.getWidth()+width-cameraFluffX) {cameraX = -map.getWidth()+width-cameraFluffX;}
	return player->getX();
}
float ClientController::getCameraY() {
	//float cameraY = floorf(-player->getY()+gameHeight/2.0f);
	//if (cameraY > 0+cameraFluffY) {cameraY = 0+cameraFluffY;}
	//if (cameraY < -map.getHeight()+height-cameraFluffY) {cameraY = -map.getHeight()+height-cameraFluffY;}
	return player->getY();
}
void ClientController::setTimeLeft(int timeLeft) {
	mapRotaterTimeLeft = timeLeft;
	mapRotaterClock.restart();
}
void ClientController::setPlayer(Player* p) {
	player = p;
}