//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2PredefinedProxies.h"

#include "U2Context.h"


U2EG_NAMESPACE_USING


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
ContextProxy::ContextProxy(const String& type, const String& name)
    : Proxy(type, name)
{ }
//-----------------------------------------------------------------------
ContextProxy::~ContextProxy(void)
{ }
//-----------------------------------------------------------------------
void ContextProxy::pushBack(const String& name, u2::Context* context, ContextQueue::eTransType transType)
{
    ContextQueue* pQueue = _retrieveContextQueue(name);
    if (pQueue)
    {
        pQueue->pushBack(context, transType);
    }
}
//-----------------------------------------------------------------------
void ContextProxy::pushFront(const String& name, u2::Context* context, ContextQueue::eTransType transType)
{
    ContextQueue* pQueue = _retrieveContextQueue(name);
    if (pQueue)
    {
        pQueue->pushFront(context, transType);
    }
}
//-----------------------------------------------------------------------
void ContextProxy::pop(const String& name, ContextQueue::eTransType transType)
{
    ContextQueue* pQueue = _retrieveContextQueue(name);
    if (pQueue)
    {
        pQueue->pop(transType);
    }
}
//-----------------------------------------------------------------------
void ContextProxy::replace(const String& name, u2::Context* from, u2::Context* to, ContextQueue::eTransType transType)
{
    ContextQueue* pQueue = _retrieveContextQueue(name);
    if (pQueue)
    {
        pQueue->replace(from, to, transType);
    }
}
//-----------------------------------------------------------------------
ContextQueue* ContextProxy::_retrieveContextQueue(const String& name)
{
    ContextQueue* pQueue = ContextQueueManager::getSingleton().retrieveObject(name);
    if (pQueue == nullptr)
    {
        assert(0);
    }
    return pQueue;
}
//-----------------------------------------------------------------------
ContextQueue* ContextProxy::createContextQueue(const String& type, const String& name
    , ContextQueue::eTransType defaultTransType, ContextQueue::ePriority priority)
{
    ContextQueue* pQueue = ContextQueueManager::getSingleton().retrieveObject(name);
    if (pQueue == nullptr)
    {
        pQueue = ContextQueueManager::getSingleton().createContextQueue(type, name, defaultTransType, priority);
        for (PriorityQueueList::iterator it = m_priorityQueues.begin();
            it != m_priorityQueues.end(); 
            it++)
        {
            if ((*it)->getPriority() < priority)
            {
                m_priorityQueues.insert(it, pQueue);
                break;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        assert(0);
    }
    return pQueue;
}