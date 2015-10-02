//
//  PacketID.h
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_PacketID_h
#define Game_Server_PacketID_h

#include "Global.h"

#include "Block.h"
#include "Player.h"
#include "Cannon.h"
#include "Map.h"
#include "PhysicsEngine.h"
#include "Networking.h"
#include "ClientController.h"

class Map;
class Block;
class Cannon;
class Player;
class Networking;
class ClientController;

class PacketID {
public:
	class Server {
	public:
		class Packet {
		public:
			enum ServerPacket { ClientID, UdpConnected, Map, ClearBlocks, TimeLeft, Block, CreateCannon, CreatePlayer, CannonPosUpdate, PlayerPosUpdate, PlayerUltiUpdate, PlayerInAirUpdate, PlayerDeathCount, PlayerWinCount, PlayerSelf, DeletePlayer, DeleteCannon };
		};
		static void ppClientID(sf::Packet* p, Networking* n);
		static void ppUdpConnected(sf::Packet* p, Networking* n);
		static void ppMap(sf::Packet* p, Map* m);
		static void ppClearBlocks(sf::Packet* p, Map* m);
		static void ppTimeLeft(sf::Packet* p, ClientController* c);
		static void ppBlock(sf::Packet* p, Map* m);
		static void ppCreateCannon(sf::Packet* p, Map* m);
		static void ppCreatePlayer(sf::Packet* p, Map* m);
		static void ppCannonPosUpdate(sf::Packet* p, Map* m);
		static void ppPlayerPosUpdate(sf::Packet* p, Map* m);
		static void ppPlayerUltiUpdate(sf::Packet* p, Map* m);
		static void ppPlayerInAirUpdate(sf::Packet* p, Map* m);
		static void ppPlayerDeathCount(sf::Packet* p, Map* m);
		static void ppPlayerWinCount(sf::Packet* p, Map* m);
		static void ppPlayerSelf(sf::Packet* p, Map* m, ClientController* c);
		static void ppDeletePlayer(sf::Packet* p, Map* m);
		static void ppDeleteCannon(sf::Packet* p, Map* m);
	};
	class Client {
	public:
		class Packet {
		public:
			enum ClientPacket { /*UdpPort,*/ UdpConnect, Login, RightArrow, LeftArrow, UpArrow, DownArrow, SpaceBar, Mouse, MousePos };
		};
		//static sf::Packet* gpUdpPort(Networking* networking);
		static sf::Packet* gpUdpConnect(Networking* networking);
		static sf::Packet* gpLogin(std::string name);
		static sf::Packet* gpRightArrow(bool pressed);
		static sf::Packet* gpLeftArrow(bool pressed);
		static sf::Packet* gpUpArrow(bool pressed);
		static sf::Packet* gpDownArrow(bool pressed);
		static sf::Packet* gpSpaceBar(bool pressed);
		static sf::Packet* gpMouse(bool pressed);
		static sf::Packet* gpMousePos(float x, float y);
	};
};

#endif