//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "ApplicationFacade.h"

#include "ApplicationCommands.h"
#include "ApplicationMediators.h"
#include "ApplicationViewComponents.h"
#include "U2ContextProxy.h"


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
template<> ApplicationFacade* Singleton<ApplicationFacade>::msSingleton = 0;
//-----------------------------------------------------------------------
ApplicationFacade* ApplicationFacade::getSingletonPtr(void)
{
	if (msSingleton == nullptr)
	{
		Facade* pFacade = FacadeManager::getSingleton().retrieveObject("ApplicationFacade");
		if (pFacade == nullptr)
		{
			pFacade = Facade::createFacade<ApplicationFacade>("ApplicationFacade");
		}
		msSingleton = dynamic_cast<ApplicationFacade*>(pFacade);
	}
	
	return msSingleton;
}
//-----------------------------------------------------------------------
ApplicationFacade& ApplicationFacade::getSingleton(void)
{
	return (*getSingletonPtr());
}
//-----------------------------------------------------------------------
ApplicationFacade::ApplicationFacade(const String& type, const String& name)
    : Facade(type, name)
{
    // proxy factory
    CREATE_FACTORY(ContextProxy);

    // command factory
    CREATE_FACTORY(StartupCommand);
    CREATE_FACTORY(DestroyContextCommand);
    CREATE_FACTORY(Trans2LogoCommand);
    CREATE_FACTORY(SceneTransCommand);

    // mediator factory
    CREATE_FACTORY(ShadeMediator);
    CREATE_FACTORY(LogoMediator);

    // viewcomponent factory
    CREATE_FACTORY(ShadeViewComponent);
    CREATE_FACTORY(LogoViewComponent);
}
//-----------------------------------------------------------------------
ApplicationFacade::~ApplicationFacade(void)
{
}
//-----------------------------------------------------------------------
void ApplicationFacade::initializeController(void)
{
    Facade::initializeController();

	registerCommand(NTF_Application_Startup, CommandManager::getSingleton().createObject(OT_StartupCommand, BLANK));
    registerCommand(NTF_Application_DestroyContext, CommandManager::getSingleton().createObject(OT_DestroyContextCommand, BLANK));
    registerCommand(NTF_Application_Trans2Logo, CommandManager::getSingleton().createObject(OT_Trans2LogoCommand, BLANK));
    registerCommand(NTF_Application_SceneTrans, CommandManager::getSingleton().createObject(OT_SceneTransCommand, BLANK));
}
//-----------------------------------------------------------------------
void ApplicationFacade::initializeModel(void)
{
	Facade::initializeModel();

    registerProxy(ProxyManager::getSingleton().createObject(OT_ContextProxy, "ContextProxy"));
}
//-----------------------------------------------------------------------
void ApplicationFacade::initializeView(void)
{
	Facade::initializeView();
}
//-----------------------------------------------------------------------
void ApplicationFacade::startup()
{
    sendNotification(NTF_Application_Startup);
    //removeCommand(Ntf_Application_Startup); //PureMVC初始化完成，注销STARUP命令
}