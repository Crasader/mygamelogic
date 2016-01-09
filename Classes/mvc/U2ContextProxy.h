//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2ContextProxy__
#define __U2ContextProxy__


#include "cocos2d.h"
#include "U2Object.h"
#include "U2Proxy.h"
#include "U2ContextQueue.h"


U2EG_NAMESPACE_BEGIN


class Context;


class ContextProxy : public Proxy
{
public:
    ContextProxy(const String& type, const String& name);
    virtual ~ContextProxy(void);

    ContextQueue* createContextQueue(const String& type
        , ContextQueue::eTransType defaultTransType, ContextQueue::eCapacity capacity
        , ContextQueue::ePriority priority);

    void pushBack(const String& type, u2::Context* context, ContextQueue::eTransType transType = ContextQueue::eTransType::TT_None);
    void pushFront(const String& type, u2::Context* context, ContextQueue::eTransType transType = ContextQueue::eTransType::TT_None);
    void pop(const String& type, ContextQueue::eTransType transType = ContextQueue::eTransType::TT_None);
    void replace(const String& type, u2::Context* from, u2::Context* to, ContextQueue::eTransType transType = ContextQueue::eTransType::TT_None);

protected:
    ContextQueue* _retrieveContextQueue(const String& type);

protected:
    typedef std::list<ContextQueue*>        PriorityQueueList;
    PriorityQueueList           m_priorityQueues;
};


U2EG_NAMESPACE_END

#endif /* defined(__U2ContextProxy__) */
