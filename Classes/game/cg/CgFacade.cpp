//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "CgFacade.h"

#include "CgCommands.h"
#include "CgMediators.h"
#include "CgViewComponents.h"


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
template<> CgFacade* Singleton<CgFacade>::msSingleton = 0;
//-----------------------------------------------------------------------
CgFacade* CgFacade::getSingletonPtr(void)
{
	if (msSingleton == nullptr)
	{
		Facade* pFacade = FacadeManager::getSingleton().retrieveObject("CgFacade");
		if (pFacade == nullptr)
		{
			pFacade = Facade::createFacade<CgFacade>("CgFacade");
		}
		msSingleton = dynamic_cast<CgFacade*>(pFacade);
	}
	
	return msSingleton;
}
//-----------------------------------------------------------------------
CgFacade& CgFacade::getSingleton(void)
{
	return (*getSingletonPtr());
}
//-----------------------------------------------------------------------
CgFacade::CgFacade(const String& type, const String& name)
    : Facade(type, name)
{
    // command factory
    CREATE_FACTORY(StartCgCommand);
    CREATE_FACTORY(Trans2CgCommand);

    // mediator factory
    CREATE_FACTORY(CgMediator);
    CREATE_FACTORY(StartPageMediator);

    // viewcomponent factory
    CREATE_FACTORY(CgViewComponent);
    CREATE_FACTORY(StartPageViewComponent);
}
//-----------------------------------------------------------------------
CgFacade::~CgFacade(void)
{
}
//-----------------------------------------------------------------------
void CgFacade::initializeController(void)
{
    Facade::initializeController();

	registerCommand(NTF_Cg_StartCg, CommandManager::getSingleton().createObject(OT_StartCgCommand, BLANK));
    registerCommand(NTF_Cg_Trans2Cg, CommandManager::getSingleton().createObject(OT_Trans2CgCommand, BLANK));
}
//-----------------------------------------------------------------------
void CgFacade::initializeModel(void)
{
	Facade::initializeModel();
}
//-----------------------------------------------------------------------
void CgFacade::initializeView(void)
{
	Facade::initializeView();
}