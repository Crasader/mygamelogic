//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2ContextQueue.h"


U2EG_NAMESPACE_USING


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
ContextQueue::ContextQueue(const String& type, const String& name)
    : Object(type, name)
{

}
//-----------------------------------------------------------------------
ContextQueue::~ContextQueue()
{
}
//-----------------------------------------------------------------------
void ContextQueue::initialize(eTransType defaultTransType, eCapacity capacity, ePriority priority)
{
    m_eDefaultTransType = defaultTransType;
    m_eCapacity = capacity;
    m_ePriority = priority;
}
//-----------------------------------------------------------------------
void ContextQueue::pushBack(u2::Context* context, eTransType transType)
{
    m_queue.push_back(context);
    if (m_eCapacity != eCapacity::Cap_Infinite)
    {
        if (m_queue.size() > (size_t)m_eCapacity)
        {
            pop(transType);
        }
    }
}
//-----------------------------------------------------------------------
void ContextQueue::pushFront(u2::Context* context, eTransType transType)
{
    u2::Context* pFrom = m_queue.front();
    m_queue.push_front(context);
    u2::Context* pTo = m_queue.front();
    _switch(pFrom, (transType == eTransType::TT_None) ? m_eDefaultTransType : transType, pTo);
}
//-----------------------------------------------------------------------
void ContextQueue::pop(eTransType transType = eTransType::TT_None)
{
    u2::Context* pFrom = m_queue.front();
    m_queue.pop_front();
    u2::Context* pTo = m_queue.front();
    _switch(pFrom, (transType == eTransType::TT_None) ? m_eDefaultTransType : transType, pTo);
}
//-----------------------------------------------------------------------
void ContextQueue::replace(u2::Context* from, u2::Context* to, eTransType transType)
{
    for (Queue::iterator it = m_queue.begin(); it != m_queue.end(); it++)
    {
        if (*it == from)
        {
            *it = to;
            _switch(from, (transType == eTransType::TT_None) ? m_eDefaultTransType : transType, to);
            break;
        }
    }
}
//-----------------------------------------------------------------------
void ContextQueue::_switch(u2::Context* from, eTransType transType, u2::Context* to)
{

}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
template<> ContextQueueManager* Singleton<ContextQueueManager>::msSingleton = 0;
ContextQueueManager* ContextQueueManager::getSingletonPtr(void)
{
    if (msSingleton == nullptr)
    {
        msSingleton = new ContextQueueManager;
    }
    return msSingleton;
}
ContextQueueManager& ContextQueueManager::getSingleton(void)
{
    return (*getSingletonPtr());
}
//-----------------------------------------------------------------------
ContextQueueManager::ContextQueueManager()
{
    CREATE_FACTORY(ContextQueue);
}
//-----------------------------------------------------------------------
ContextQueueManager::~ContextQueueManager()
{
}
//-----------------------------------------------------------------------
ContextQueue* ContextQueueManager::createContextQueue(const String& type
    , ContextQueue::eTransType defaultTransType, ContextQueue::eCapacity capacity
    , ContextQueue::ePriority priority)
{
    ContextQueue* pContext = createObject(type, type);
    pContext->initialize(defaultTransType, capacity, priority);
    return pContext;
}
//-----------------------------------------------------------------------
ContextQueue* ContextQueueManager::createObject(const String& type, const String& name)
{
    return SimpleObjectManager<ContextQueue>::createObject(type, name);
}