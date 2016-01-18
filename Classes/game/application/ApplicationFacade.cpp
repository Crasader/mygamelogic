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
#include "U2PredefinedProxies.h"


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

    // command factory
    CREATE_FACTORY(StartupCommand);
    CREATE_FACTORY(Trans2LogoCommand);

    // mediator factory
    CREATE_FACTORY(ShadeMediator);
    CREATE_FACTORY(LogoMediator);

    // viewcomponent factory
    CREATE_FACTORY(ShadeViewComponent);
    CREATE_FACTORY(LogoViewComponent);

    // context
    initializeContextQueue();
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
    registerCommand(NTF_Application_Trans2Logo, CommandManager::getSingleton().createObject(OT_Trans2LogoCommand, BLANK));
}
//-----------------------------------------------------------------------
void ApplicationFacade::initializeModel(void)
{
	Facade::initializeModel();
}
//-----------------------------------------------------------------------
void ApplicationFacade::initializeView(void)
{
	Facade::initializeView();
}
//-----------------------------------------------------------------------
void ApplicationFacade::initializeContextQueue(void)
{
    ContextQueueManager::getSingleton().createContextQueue(OT_ShadeContext, CQN_Shade
        , ContextQueue::eTransType::TT_Overlay, ContextQueue::ePriority::Pri_0_Shade);
    ContextQueueManager::getSingleton().createContextQueue(OT_SceneContext, CQN_Scene
        , ContextQueue::eTransType::TT_OneByOne, ContextQueue::ePriority::Pri_10);
    ContextQueueManager::getSingleton().createContextQueue(OT_TabContext, CQN_Tab
        , ContextQueue::eTransType::TT_OneByOne, ContextQueue::ePriority::Pri_20);
    ContextQueueManager::getSingleton().createContextQueue(OT_CommonContext, CQN_Common
        , ContextQueue::eTransType::TT_Overlay, ContextQueue::ePriority::Pri_50);
    ContextQueueManager::getSingleton().createContextQueue(OT_DialogContext, CQN_Dialog
        , ContextQueue::eTransType::TT_Cross, ContextQueue::ePriority::Pri_100_Dialog);
}
//-----------------------------------------------------------------------
void ApplicationFacade::startup()
{
    sendNotification(NTF_Application_Startup);
    //removeCommand(Ntf_Application_Startup); //PureMVC初始化完成，注销STARUP命令
}