//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2PredefinedCommands.h"

#include "U2Context.h"
#include "U2Mediator.h"
#include "U2Facade.h"
#include "U2PredefinedProxies.h"
#include "U2PredefinedPrerequisites.h"
#include "U2PredefinedMediators.h"
#include "U2NameGenerator.h"



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
DestoryContextCommand::DestoryContextCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
DestoryContextCommand::~DestoryContextCommand()
{
}
//-----------------------------------------------------------------------
void DestoryContextCommand::go(const Notification& notification)
{
    const void* pData = notification.getData();
    _destroyContext((u2::Context*)pData);
}
//-----------------------------------------------------------------------
void DestoryContextCommand::_destroyContext(u2::Context* context)
{
    if (context == nullptr)
    {
        return;
    }

    u2::Context::ContextListIterator it = context->getContextIterator();
    while (it.hasMoreElements())
    {
        _destroyContext(it.getNext());
    }

    Mediator* pMediator = MediatorManager::getSingleton().retrieveObject(context->getMediatorName());
    if (pMediator != nullptr)
    {
        pMediator->end();
        MediatorManager::getSingleton().destoryObject(pMediator);
    }
    ContextManager::getSingleton().destoryObject(context);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
TransCommand::TransCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
TransCommand::~TransCommand()
{
}
//-----------------------------------------------------------------------
void TransCommand::go(const Notification& notification)
{
    _createMediator(_retrieveFromContext(), _retrieveTransType(), _createToContext());
}
//-----------------------------------------------------------------------
void TransCommand::_createMediator(const u2::Context* from, TransMediator::TransType type, const u2::Context* to)
{
    // to mediator
    Mediator* pMediator = MediatorManager::getSingleton().createObject(to->getMediatorClass(), to->getMediatorName());
    if (pMediator)
    {
        getFacade().registerMediator(pMediator);
    }
    
    // trans mediator name
    NameGeneratorManager::getSingleton().registerNameGenerator("TransMediator");
    u2::String szTransName = NameGeneratorManager::getSingleton().generator("TransMediator");
    TransMediator* pTransMediator = dynamic_cast<TransMediator*>(
        MediatorManager::getSingleton().createObject(OT_TransMediator, szTransName));
    if (pTransMediator)
    {
        getFacade().registerMediator(pTransMediator);
    }
    
    // children
    u2::Context::ConstContextListIterator it = to->getConstContextIterator();
    while (it.hasMoreElements())
    {
        _createMediator(to, TransMediator::TransType::TT_Overlay, it.getNext());
    }
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
BackKeyCommand::BackKeyCommand(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
BackKeyCommand::~BackKeyCommand()
{
}
//-----------------------------------------------------------------------
void BackKeyCommand::go(const Notification& notification)
{
    ContextProxy* pProxy = dynamic_cast<ContextProxy*>(ProxyManager::getSingleton().retrieveObject("ContextProxy"));
    if (pProxy == nullptr)
    {
        return;
    }

    ContextProxy::ContextQueueVectorIterator it = pProxy->getContextQueueIterator();
    while (it.hasMoreElements())
    {
        ContextQueue* pQueue = it.getNext();
        if (pQueue == nullptr)
        {
            continue;
        }
        u2::Context* pContext = pQueue->top();
        if (pContext == nullptr)
        {
            continue;
        }

        if (_dispatchBack(pContext))
        {
            break;
        }
    }
}
//-----------------------------------------------------------------------
bool BackKeyCommand::_dispatchBack(u2::Context* context)
{
    if (context == nullptr)
    {
        return false;
    }

    Mediator* pMediator = MediatorManager::getSingleton().retrieveObject(context->getMediatorName());
    if (pMediator == nullptr)
    {
        return false;
    }

    bool bCanEnd = pMediator->preEnd(true);
    if (bCanEnd)
    {
        getFacade().sendNotification(NTF_Application_DestroyContext, context);
    }
    else
    {
        u2::Context::ContextListIterator it = context->getContextIterator();
        while (it.hasMoreElements())
        {
            return _dispatchBack(it.getNext());
        }
    }
}