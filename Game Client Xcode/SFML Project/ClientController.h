//
//  ServerController.h
//  Game Server
//
//  Created by Matthew French on 1/2/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_ServerController_h
#define Game_Server_ServerController_h

#include "Global.h"
#include "Networking.h"
#include "PacketID.h"
#include "Map.h"

class Networking;
class Map;
class Player;

class ClientController
{
protected:
	Networking* networking;
	sf::Clock clock;
	float delta;
	
	Map* map;
	Player* player;
	bool mouseDown, rightArrow, leftArrow, upArrow, downArrow, spaceBar;
	float mouseX, mouseY;
	long mapRotaterTimeLeft;
	sf::Clock mapRotaterClock;
	bool connected;
	sf::View* cameraView;
	sf::View* mapView;
	//sf::RenderTexture* texture;
	sf::RectangleShape* rectangle;
	sf::Font font;
public:
	ClientController();
	~ClientController();
	void logic();
	void draw(sf::RenderTarget* window);
	void onConnect();
	void onDisconnect();
	void onMessage(sf::Packet* p);
	
	void pressedRight();
	void pressedUp();
	void pressedLeft();
	void pressedDown();
	void pressedSpace();
	void releasedRight();
	void releasedUp();
	void releasedLeft();
	void releasedDown();
	void releasedSpace();
	void pressedMouse(float x, float y);
	void releasedMouse();
	void draggedMouse(float x, float y);
	void login();
	int getMouseXRelativeToPlayer();
	int getMouseYRelativeToPlayer();
	float getCameraX();
	float getCameraY();
	void setTimeLeft(int timeLeft);
	void setPlayer(Player* p);
private:
	
};

#endif
