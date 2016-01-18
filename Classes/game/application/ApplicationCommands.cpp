//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "ApplicationCommands.h"

#include "U2Facade.h"
#include "U2Context.h"
#include "U2SceneTransMediator.h"
#include "ApplicationPrerequisites.h"
#include "ApplicationMediators.h"



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
StartupCommand::StartupCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
StartupCommand::~StartupCommand()
{
}
//-----------------------------------------------------------------------
void StartupCommand::go(const Notification& notification)
{
    Notification ntf(NTF_Application_Trans2Shade);
    getFacade().broadcastNotification(ntf);

    Notification ntfLogo(NTF_Application_Trans2Logo);
    getFacade().broadcastNotification(ntfLogo);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Trans2ShadeCommand::Trans2ShadeCommand(const String& type, const String& name)
    : TransCommand(type, name)
{
}
//-----------------------------------------------------------------------
Trans2ShadeCommand::~Trans2ShadeCommand()
{
}
//-----------------------------------------------------------------------
u2::Context* Trans2ShadeCommand::_createToContext()
{
    // create context tree
    u2::Context* pTo = ContextManager::getSingleton().createObject(
        OT_Context, "RootContext"
        , OT_ShadeMediator, "ShadeMediator"
        , OT_ShadeViewComponent, "ShadeViewComponent"
        );

    return pTo;
}
//-----------------------------------------------------------------------
u2::Context* Trans2ShadeCommand::_retrieveFromContext()
{
    return nullptr;
}
//-----------------------------------------------------------------------
TransMediator::TransType Trans2ShadeCommand::_retrieveTransType()
{
    return TransMediator::TransType::TT_Overlay;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Trans2LogoCommand::Trans2LogoCommand(const String& type, const String& name)
    : TransCommand(type, name)
{
}
//-----------------------------------------------------------------------
Trans2LogoCommand::~Trans2LogoCommand()
{
}
//-----------------------------------------------------------------------
u2::Context* Trans2LogoCommand::_createToContext()
{
    // create context tree
    u2::Context* pLogo = ContextManager::getSingleton().createObject(
        OT_Context, "LogoContext"
        , OT_LogoMediator, "LogoMediator"
        , OT_LogoViewComponent, "LogoViewComponent"
        );

    return pLogo;
}
//-----------------------------------------------------------------------
u2::Context* Trans2LogoCommand::_retrieveFromContext()
{
    return ContextManager::getSingleton().retrieveObject("RootContext");
}
//-----------------------------------------------------------------------
TransMediator::TransType Trans2LogoCommand::_retrieveTransType()
{
    return TransMediator::TransType::TT_Overlay;
}