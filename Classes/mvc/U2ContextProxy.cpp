﻿//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2ContextProxy.h"

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
void ContextProxy::pushBack(const String& type, u2::Context* context, ContextQueue::eTransType transType)
{
    ContextQueue* pQueue = _retrieveContextQueue(type);
    if (pQueue)
    {
        pQueue->pushBack(context, transType);
    }
}
//-----------------------------------------------------------------------
void ContextProxy::pushFront(const String& type, u2::Context* context, ContextQueue::eTransType transType)
{
    ContextQueue* pQueue = _retrieveContextQueue(type);
    if (pQueue)
    {
        pQueue->pushFront(context, transType);
    }
}
//-----------------------------------------------------------------------
void ContextProxy::pop(const String& type, ContextQueue::eTransType transType)
{
    ContextQueue* pQueue = _retrieveContextQueue(type);
    if (pQueue)
    {
        pQueue->pop(transType);
    }
}
//-----------------------------------------------------------------------
void ContextProxy::replace(const String& type, u2::Context* from, u2::Context* to, ContextQueue::eTransType transType)
{
    ContextQueue* pQueue = _retrieveContextQueue(type);
    if (pQueue)
    {
        pQueue->replace(from, to, transType);
    }
}
//-----------------------------------------------------------------------
ContextQueue* ContextProxy::_retrieveContextQueue(const String& type)
{
    ContextQueue* pQueue = ContextQueueManager::getSingleton().retrieveObject(type);
    if (pQueue == nullptr)
    {
        assert(0);
    }
    return pQueue;
}
//-----------------------------------------------------------------------
ContextQueue* ContextProxy::createContextQueue(const String& type
    , ContextQueue::eTransType defaultTransType, ContextQueue::eCapacity capacity
    , ContextQueue::ePriority priority)
{
    ContextQueue* pQueue = ContextQueueManager::getSingleton().retrieveObject(type);
    if (pQueue == nullptr)
    {
        pQueue = ContextQueueManager::getSingleton().createContextQueue(type, defaultTransType, capacity, priority);
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