//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2PredefinedProxies__
#define __U2PredefinedProxies__


#include "cocos2d.h"
#include "U2Object.h"
#include "U2Proxy.h"
#include "U2ContextQueue.h"
#include "U2IteratorWrapper.h"


U2EG_NAMESPACE_BEGIN


class Context;


class ContextProxy : public Proxy
{
protected:
    typedef std::vector<ContextQueue*>  PriorityQueueList;

public:
    ContextProxy(const String& type, const String& name);
    virtual ~ContextProxy(void);

    ContextQueue* createContextQueue(const String& type, const String& name
        , ContextQueue::eTransType defaultTransType, ContextQueue::ePriority priority);

    void pushBack(const String& name, u2::Context* context, ContextQueue::eTransType transType = ContextQueue::eTransType::TT_None);
    void pushFront(const String& name, u2::Context* context, ContextQueue::eTransType transType = ContextQueue::eTransType::TT_None);
    void pop(const String& name, ContextQueue::eTransType transType = ContextQueue::eTransType::TT_None);
    void replace(const String& name, u2::Context* from, u2::Context* to, ContextQueue::eTransType transType = ContextQueue::eTransType::TT_None);

    typedef VectorIterator<PriorityQueueList>       ContextQueueVectorIterator;

    ContextQueueVectorIterator getContextQueueIterator()
    {
        return ContextQueueVectorIterator(m_priorityQueues.begin(), m_priorityQueues.end());
    }

protected:
    ContextQueue* _retrieveContextQueue(const String& name);

protected:
    PriorityQueueList           m_priorityQueues;
};


U2EG_NAMESPACE_END

#endif /* defined(__U2PredefinedProxies__) */
