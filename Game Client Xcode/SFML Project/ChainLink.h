//
//  ChainLink.h
//  Game Server
//
//  Created by Matthew French on 1/1/13.
//  Copyright (c) 2013 Matthew French. All rights reserved.
//

#ifndef Game_Server_ChainLink_h
#define Game_Server_ChainLink_h

struct ChainLink {
	void *object1, *object2;
	ChainLink* nextLink;
	ChainLink()
    {
	object1=NULL;
	object2=NULL;
	nextLink=NULL;
    }
};

#endif
