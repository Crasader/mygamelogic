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
    u2::Context* pTo = ContextManager::getSingleton().createObject(OT_Context, "RootContext", OT_ShadeMediator, "ShadeMediator", OT_ShadeViewComponent, "ShadeViewComponent");
    Mediator::TransData data = std::make_tuple(nullptr, Mediator::TransType::TT_Overlay, pTo);
    Notification ntf(NTF_Application_SceneTrans, &data);
    getFacade().broadcastNotification(ntf);

    Notification ntfLogo(NTF_Application_Trans2Logo);
    getFacade().broadcastNotification(ntfLogo);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
SceneTransCommand::SceneTransCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
SceneTransCommand::~SceneTransCommand()
{
}
//-----------------------------------------------------------------------
void SceneTransCommand::go(const Notification& notification)
{
    const u2::String& szNtfName = notification.getName();
    const void* pData = notification.getData();
    const Mediator::TransData data = *((const Mediator::TransData*)pData);

    u2::Context* pFromContext = std::get<0>(data);
    Mediator::TransType eTransType = std::get<1>(data);
    u2::Context* pToContext = std::get<2>(data);

    _createMediator(pFromContext, eTransType, pToContext);
}
//-----------------------------------------------------------------------
void SceneTransCommand::_createMediator(const u2::Context* from, Mediator::TransType type, const u2::Context* to)
{
    Mediator* pMediator = MediatorManager::getSingleton().createObject(to->getMediatorClass(), to->getMediatorName());
    getFacade().registerMediator(pMediator);
    pMediator->startup(from, type, to);

    u2::Context::ConstContextListIterator it = to->getConstContextIterator();
    while (it.hasMoreElements())
    {
        _createMediator(to, Mediator::TransType::TT_Overlay, it.getNext());
    }
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
DestroyContextCommand::DestroyContextCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
DestroyContextCommand::~DestroyContextCommand()
{
}
//-----------------------------------------------------------------------
void DestroyContextCommand::go(const Notification& notification)
{
    const u2::String& szNtfName = notification.getName();
    const void* pData = notification.getData();

    u2::Context* pContext = (u2::Context*)pData;
    if (pContext != nullptr)
    {
        _destroyContext(pContext);
    }
}
//-----------------------------------------------------------------------
void DestroyContextCommand::_destroyContext(u2::Context* context)
{
    u2::Context::ContextListIterator it = context->getContextIterator();
    while (it.hasMoreElements())
    {
        _destroyContext(it.getNext());
    }

    ContextManager::getSingleton().destoryObject(context);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Trans2LogoCommand::Trans2LogoCommand(const String& type, const String& name)
    : Trans2Command(type, name)
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
    u2::Context* pLogo = ContextManager::getSingleton().createObject(OT_Context, "LogoContext", OT_LogoMediator, "LogoMediator", OT_LogoViewComponent, "LogoViewComponent");

    return pLogo;
}
//-----------------------------------------------------------------------
u2::Context* Trans2LogoCommand::_retrieveFromContext()
{
    return ContextManager::getSingleton().retrieveObject("RootContext");
}
//-----------------------------------------------------------------------
Mediator::TransType Trans2LogoCommand::_retrieveTransType()
{
    return Mediator::TransType::TT_Overlay;
}