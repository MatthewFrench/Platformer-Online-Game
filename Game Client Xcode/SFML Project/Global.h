//
//  Global.h
//  Game Server
//
//  Created by Matthew French on 1/3/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_Global_h
#define Game_Server_Global_h

#include <tgmath.h>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2d.h"
#include "ResourcePath.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>

const float fps = 60;
const float pixelPerMeter = 128;
const float gameWidth = 1000;
const float gameHeight = 700;

//const std::string serverAddress = "127.0.0.1";
const std::string serverAddress = "174.70.154.67";
const int serverPort = 7777;

const long networkThreadDelay = 5000000L; //5000000L = 200 network updates per second


#endif
