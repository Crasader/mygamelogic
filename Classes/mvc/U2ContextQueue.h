//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2ContextQueue__
#define __U2ContextQueue__


#include "U2Prerequisites.h"
#include "U2Object.h"
#include "U2SimpleObjectManager.h"
#include "U2Singleton.h"


U2EG_NAMESPACE_BEGIN


class Context;


class ContextQueue : public Object
{
protected:
    typedef std::list<u2::Context*>         Queue;

public:
    enum class eCapacity
    {
        Cap_Infinite = 0,
        Cap_1 = 1,
        Cap_2 = 2,
        Cap_3 = 3,
        Cap_4 = 4,
        Cap_5 = 5,
    };

    enum class ePriority
    {
        Pri_0_Shade = 0,
        Pri_10 = 10,
        Pri_20 = 20,
        Pri_30 = 30,
        Pri_40 = 40,
        Pri_50 = 50,
        Pri_60 = 60,
        Pri_70 = 70,
        Pri_80 = 80,
        Pri_90 = 90,
        Pri_100_Dialog = 100,
        Pri_110 = 110,
        Pri_120 = 120,
        Pri_130 = 130,
        Pri_140 = 140,
        Pri_150 = 150,
        Pri_160 = 160,
        Pri_170 = 170,
        Pri_180 = 180,
        Pri_190 = 190,
        Pri_200_Scene = 200,
        Pri_210 = 210,
    };

    enum class eTransType
    {
        TT_None,
        TT_Overlay,
        TT_OneByOne,
        TT_Cross
    };

public:
    ContextQueue(const String& type, const String& name);
    virtual ~ContextQueue();

    inline ContextQueue::ePriority getPriority() const { return m_ePriority; };
    u2::Context* top();

    virtual void initialize(eTransType defaultTransType, ePriority priority) = 0;
    virtual void pushBack(u2::Context* context, eTransType transType = eTransType::TT_None) = 0;
    virtual void pushFront(u2::Context* context, eTransType transType = eTransType::TT_None) = 0;
    virtual void pop(eTransType transType = eTransType::TT_None) = 0;
    virtual void replace(u2::Context* from, u2::Context* to, eTransType transType = eTransType::TT_None) = 0;

protected:
    void _switch(u2::Context* from, eTransType transType, u2::Context* to);

protected:
    eTransType  m_eDefaultTransType;
    eCapacity   m_eCapacity;
    ePriority   m_ePriority;
    Queue       m_queue;
};


class SingleContextQueue : public ContextQueue
{
public:
    SingleContextQueue(const String& type, const String& name);
    virtual ~SingleContextQueue();

    virtual void initialize(eTransType defaultTransType, ePriority priority) override;
    virtual void pushBack(u2::Context* context, eTransType transType = eTransType::TT_None) override;
    virtual void pushFront(u2::Context* context, eTransType transType = eTransType::TT_None) override;
    virtual void pop(eTransType transType = eTransType::TT_None) override;
    virtual void replace(u2::Context* from, u2::Context* to, eTransType transType = eTransType::TT_None) override;

};


class InfiniteContextQueue : public ContextQueue
{
public:
    InfiniteContextQueue(const String& type, const String& name);
    virtual ~InfiniteContextQueue();

    virtual void initialize(eTransType defaultTransType, ePriority priority) override;
    virtual void pushBack(u2::Context* context, eTransType transType = eTransType::TT_None) override;
    virtual void pushFront(u2::Context* context, eTransType transType = eTransType::TT_None) override;
    virtual void pop(eTransType transType = eTransType::TT_None) override;
    virtual void replace(u2::Context* from, u2::Context* to, eTransType transType = eTransType::TT_None) override;

};


class ContextQueueManager : public SimpleObjectManager<ContextQueue>, public Singleton < ContextQueueManager >
{
protected:
    /** Default constructor - should never get called by a client app.
    */
    ContextQueueManager();

public:
    /** Default destructor.
    */
    virtual ~ContextQueueManager();

    ContextQueue* createContextQueue(const String& type, const String& name
        , ContextQueue::eTransType defaultTransType, ContextQueue::ePriority priority);

protected:
    virtual ContextQueue* createObject(const String& type, const String& name);

public:
    /** Override standard Singleton retrieval.
    @remarks
    Why do we do this? Well, it's because the Singleton
    implementation is in a .h file, which means it gets compiled
    into anybody who includes it. This is needed for the
    Singleton template to work, but we actually only want it
    compiled into the implementation of the class based on the
    Singleton, not all of them. If we don't change this, we get
    link errors when trying to use the Singleton-based class from
    an outside dll.
    @par
    This method just delegates to the template version anyway,
    but the implementation stays in this single compilation unit,
    preventing link errors.
    */
    static ContextQueueManager& getSingleton(void);

    /** Override standard Singleton retrieval.
    @remarks
    Why do we do this? Well, it's because the Singleton
    implementation is in a .h file, which means it gets compiled
    into anybody who includes it. This is needed for the
    Singleton template to work, but we actually only want it
    compiled into the implementation of the class based on the
    Singleton, not all of them. If we don't change this, we get
    link errors when trying to use the Singleton-based class from
    an outside dll.
    @par
    This method just delegates to the template version anyway,
    but the implementation stays in this single compilation unit,
    preventing link errors.
    */
    static ContextQueueManager* getSingletonPtr(void);
};


U2EG_NAMESPACE_END

#endif /* defined(__U2ContextQueue__) */
