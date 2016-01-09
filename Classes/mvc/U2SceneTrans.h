//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2SceneTrans__
#define __U2SceneTrans__


#include "cocos2d.h"
#include "U2Object.h"
#include "U2Singleton.h"
#include "U2ViewComponent.h"


U2EG_NAMESPACE_BEGIN


class BaseStep : public Object
{
public:
    class Key
    {
    public:
        Key();
        Key(ViewComponent* viewComp, ViewComponent::ViewCompState state);

        bool operator== (const Key &that) const;

    protected:
        ViewComponent*      m_pViewComp;
        ViewComponent::ViewCompState              m_state;
    };

public:
    BaseStep(const String& type, const String& name = BLANK);
    virtual ~BaseStep();

    void _initialize(const Key& key);

    bool isThisStep(const Key& key);

protected:
    Key         m_Key;
};

class VoidStep : public BaseStep
{
public:
    typedef std::function<void()>           CallbackFun;

public:
    VoidStep(const String& type, const String& name = BLANK);
    virtual ~VoidStep();

    void initialize(const BaseStep::Key& key, CallbackFun func);
    void call();

protected:
    void _initialize(const Key& key);

protected:
    CallbackFun     m_func;
};

class ParamStep : public BaseStep
{
public:
    typedef std::function<void(void*)>      CallbackFun;

public:
    ParamStep(const String& type, const String& name = BLANK);
    virtual ~ParamStep();

    void initialize(const BaseStep::Key& key, CallbackFun func);
    void call(void* param);

protected:
    void _initialize(const Key& key);

protected:
    CallbackFun     m_func;
};


class SceneTrans : public Singleton < SceneTrans >
{
public:
    class Trans : public ViewComponent::Listener
    {
    public:
        typedef std::function<void()>       CallbackFun;

    public:
        Trans(CallbackFun func);
        virtual ~Trans();

        virtual void trans(ViewComponent* from, ViewComponent* to);
        void _onToEntered();

    protected:
        virtual void onViewCompStateChanged(ViewComponent* viewComp, ViewComponent::ViewCompState newState) override;
        virtual void onCommonStateChanged(ViewComponent* viewComp, const String& objName, const String& msg) override {};
        
    protected:
        ViewComponent*      m_pFrom;
        ViewComponent*      m_pTo;
        void*               m_pParent;
        std::vector<BaseStep*>      m_steps;
        CallbackFun         m_func;
    };

    /**
    -- FROM exit()
    -- FROM didExit
    -- TO load()
    -- TO loading
    -- TO loaded
    -- TO enter()
    -- TO didEnter
    -- callback()
    */
    class OneByOneTrans : public Trans
    {
    public:
        OneByOneTrans(CallbackFun func);
        virtual void trans(ViewComponent* from, ViewComponent* to) override;
    };

    /**
    -- CHILD load()
    -- CHILD loading
    -- CHILD loaded
    -- CHILD attach()
    -- CHILD enter()
    -- CHILD didEnter
    -- callback()
    */
    class OverlayTrans : public Trans
    {
    public:
        OverlayTrans(CallbackFun func);
        void trans(ViewComponent* parent, ViewComponent* child) override;
    };

    /**
    -- TO load()
    -- TO loading
    -- TO loaded
    -- FROM exit()
    -- FROM didExit
    -- TO enter()
    -- TO didEnter
    -- callback()
    */
    class CrossTrans : public Trans
    {
    public:
        CrossTrans(CallbackFun func);
        void trans(ViewComponent* from, ViewComponent* to) override;

    protected:
        void _onToAttached();
    };


private:
    /**
    * Constructor.
    */
    SceneTrans();

public:
    enum class TransType
    {
        TT_Overlay,
        TT_OneByOne,
        TT_Cross
    };

    /**
    * Virtual destructor.
    */
    virtual ~SceneTrans(void);

    void trans(ViewComponent* from, ViewComponent* to, TransType type);

protected:
    VoidStep* _createVoidStep(const BaseStep::Key& key, VoidStep::CallbackFun func = nullptr);
    ParamStep* _createParamStep(const BaseStep::Key& key, ParamStep::CallbackFun func = nullptr);
    void _destroyBaseStep(BaseStep* step);
    void _onFinish();

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
    static SceneTrans& getSingleton(void);

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
    static SceneTrans* getSingletonPtr(void);

protected:
    Trans*     m_pTrans;
};


U2EG_NAMESPACE_END

#endif /* defined(__U2SceneTrans__) */
