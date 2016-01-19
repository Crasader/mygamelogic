//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "CgCommands.h"

#include "CgPrerequisites.h"
#include "CgMediators.h"
#include "../application/ApplicationPrerequisites.h"


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Trans2CgCommand::Trans2CgCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
Trans2CgCommand::~Trans2CgCommand()
{
}
//-----------------------------------------------------------------------
void Trans2CgCommand::go(const Notification& notification)
{
    // create context tree
    u2::Context* pCg = ContextManager::getSingleton().createObject(
        OT_Context, "CgContext"
        , OT_CgMediator, "CgMediator"
        , OT_CgViewComponent, "CgViewComponent");
    ContextProxy& contextProxy = (ContextProxy&)PredefinedFacade::getSingleton().retrieveProxy(ON_Proxy_Context);
    contextProxy.pushBack(ON_ContextQueue_Scene, pCg, ContextQueue::eTransType::TT_OneByOne);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Trans2StartPageCommand::Trans2StartPageCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
Trans2StartPageCommand::~Trans2StartPageCommand()
{
}
//-----------------------------------------------------------------------
void Trans2StartPageCommand::go(const Notification& notification)
{
    // create context tree
    u2::Context* pCg = ContextManager::getSingleton().createObject(
        OT_Context, "StartPageContext"
        , OT_StartPageMediator, "StartPageMediator"
        , OT_StartPageViewComponent, "StartPageViewComponent");
    ContextProxy& contextProxy = (ContextProxy&)PredefinedFacade::getSingleton().retrieveProxy(ON_Proxy_Context);
    contextProxy.pushBack(ON_ContextQueue_Scene, pCg, ContextQueue::eTransType::TT_OneByOne);
}