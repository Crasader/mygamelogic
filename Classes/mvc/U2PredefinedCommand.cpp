//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2PredefinedCommand.h"

#include "U2Context.h"
#include "U2ContextProxy.h"
#include "U2Mediator.h"
#include "U2Facade.h"



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
        getFacade().sendNotification(NTF_Application_DestroyContext);
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