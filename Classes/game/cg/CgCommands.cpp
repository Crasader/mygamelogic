//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "CgCommands.h"

#include "U2Facade.h"
#include "U2Context.h"
#include "CgPrerequisites.h"
#include "CgMediators.h"



StartCgCommand::StartCgCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}

StartCgCommand::~StartCgCommand()
{
}

void StartCgCommand::go(const Notification& notification)
{
    const u2::String& szNtfName = notification.getName();
    const void* pData = notification.getData();

    Mediator* pCgMediator = MediatorManager::getSingleton().createObject(OT_CgMediator, "CgMediator");
    getFacade().registerMediator(pCgMediator);
    //pCgMediator->startup(OT_CgViewComponent, "CgViewComp");
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Trans2CgCommand::Trans2CgCommand(const String& type, const String& name)
    : Trans2Command(type, name)
{
}
//-----------------------------------------------------------------------
Trans2CgCommand::~Trans2CgCommand()
{
}
//-----------------------------------------------------------------------
u2::Context* Trans2CgCommand::_createToContext()
{
    // create context tree
    u2::Context* pCg = ContextManager::getSingleton().createObject(OT_Context, "CgContext", OT_CgMediator, "CgMediator", OT_CgViewComponent, "CgViewComponent");

    return pCg;
}
//-----------------------------------------------------------------------
u2::Context* Trans2CgCommand::_retrieveFromContext()
{
    return ContextManager::getSingleton().retrieveObject("LogoContext");
}
//-----------------------------------------------------------------------
Mediator::TransType Trans2CgCommand::_retrieveTransType()
{
    return Mediator::TransType::TT_OneByOne;
}