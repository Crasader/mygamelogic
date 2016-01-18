//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2PredefinedFacade.h"

#include "U2PredefinedCommands.h"
#include "U2PredefinedProxies.h"
#include "U2PredefinedPrerequisites.h"


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
template<> PredefinedFacade* Singleton<PredefinedFacade>::msSingleton = 0;
//-----------------------------------------------------------------------
PredefinedFacade* PredefinedFacade::getSingletonPtr(void)
{
	if (msSingleton == nullptr)
	{
		Facade* pFacade = FacadeManager::getSingleton().retrieveObject("PredefinedFacade");
		if (pFacade == nullptr)
		{
			pFacade = Facade::createFacade<PredefinedFacade>("PredefinedFacade");
		}
		msSingleton = dynamic_cast<PredefinedFacade*>(pFacade);
	}
	
	return msSingleton;
}
//-----------------------------------------------------------------------
PredefinedFacade& PredefinedFacade::getSingleton(void)
{
	return (*getSingletonPtr());
}
//-----------------------------------------------------------------------
PredefinedFacade::PredefinedFacade(const String& type, const String& name)
    : Facade(type, name)
{
    // command factory
    CREATE_FACTORY(DestoryContextCommand);
    CREATE_FACTORY(BackKeyCommand);

    // proxy factory
    CREATE_FACTORY(ContextProxy);

    // mediator factory

    // viewcomponent factory
}
//-----------------------------------------------------------------------
PredefinedFacade::~PredefinedFacade(void)
{
}
//-----------------------------------------------------------------------
void PredefinedFacade::initializeController(void)
{
    Facade::initializeController();

    registerCommand(NTF_Predefined_DestroyContext, CommandManager::getSingleton().createObject(OT_DestoryContextCommand, BLANK));
    registerCommand(NTF_Predefined_BackKey, CommandManager::getSingleton().createObject(OT_BackKeyCommand, BLANK));
}
//-----------------------------------------------------------------------
void PredefinedFacade::initializeModel(void)
{
	Facade::initializeModel();
}
//-----------------------------------------------------------------------
void PredefinedFacade::initializeView(void)
{
	Facade::initializeView();
}