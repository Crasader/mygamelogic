//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "Root.h"

#include "U2Object.h"
#include "U2FactoryManager.h"
#include "Application/ApplicationCommands.h"






//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
template<> Root* Singleton<Root>::msSingleton = 0;
Root* Root::getSingletonPtr(void)
{
	if (msSingleton == nullptr)
	{
		msSingleton = new Root;
	}
	
	return msSingleton;
}
Root& Root::getSingleton(void)
{
	return (*getSingletonPtr());
}
//-----------------------------------------------------------------------
Root::Root()
{
}
//-----------------------------------------------------------------------
Root::~Root(void)
{
	// application
	DESTROY_FACTORY(StartupCommand);
}
//-----------------------------------------------------------------------
void Root::initialize(void)
{
	// application
	CREATE_FACTORY(StartupCommand);
}