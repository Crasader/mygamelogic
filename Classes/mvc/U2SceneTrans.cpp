//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//


#include "U2SceneTrans.h"

#include "U2ViewComponent.h"
#include "U2FactoryManager.h"
#include <boost/coroutine/all.hpp>



U2EG_NAMESPACE_USING


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
BaseStep::Key::Key() 
: m_pViewComp(nullptr)
, m_state(ViewComponent::ViewCompState::VCS_Unloaded)
{

}
BaseStep::Key::Key(ViewComponent* viewComp, ViewComponent::ViewCompState state)
: m_pViewComp(viewComp)
, m_state(state)
{

}
//-----------------------------------------------------------------------
bool BaseStep::Key::operator== (const Key &that) const
{
    return m_pViewComp == that.m_pViewComp && m_state == that.m_state;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
BaseStep::BaseStep(const String& type, const String& name) 
: Object(type, name)
{

}
//-----------------------------------------------------------------------
BaseStep::~BaseStep()
{

}
//-----------------------------------------------------------------------
void BaseStep::_initialize(const Key& key)
{
    m_Key = key;
}
//-----------------------------------------------------------------------
bool BaseStep::isThisStep(const Key& key)
{
    return m_Key == key;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
VoidStep::VoidStep(const String& type, const String& name)
    : BaseStep(type, name)
{

}
//-----------------------------------------------------------------------
VoidStep::~VoidStep()
{

}
//-----------------------------------------------------------------------
void VoidStep::_initialize(const Key& key)
{
    BaseStep::_initialize(key);
}
//-----------------------------------------------------------------------
void VoidStep::initialize(const BaseStep::Key& key, CallbackFun func)
{
    _initialize(key);
    m_func = func;
}
//-----------------------------------------------------------------------
void VoidStep::call()
{
    if (m_func != nullptr)
    {
        m_func();
    }
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
ParamStep::ParamStep(const String& type, const String& name)
    : BaseStep(type, name)
{

}
//-----------------------------------------------------------------------
ParamStep::~ParamStep()
{

}
//-----------------------------------------------------------------------
void ParamStep::_initialize(const Key& key)
{
    BaseStep::_initialize(key);
}
//-----------------------------------------------------------------------
void ParamStep::initialize(const BaseStep::Key& key, CallbackFun func)
{
    _initialize(key);
    m_func = func;
}
//-----------------------------------------------------------------------
void ParamStep::call(void* param)
{
    if (m_func != nullptr)
    {
        m_func(param);
    }
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
template<> SceneTrans* Singleton<SceneTrans>::msSingleton = 0;
SceneTrans* SceneTrans::getSingletonPtr(void)
{
    if (msSingleton == nullptr)
    {
        msSingleton = new SceneTrans;
    }
    return msSingleton;
}
SceneTrans& SceneTrans::getSingleton(void)
{
    return (*getSingletonPtr());
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
SceneTrans::SceneTrans() 
: m_pTrans(nullptr)
{
    CREATE_FACTORY(VoidStep);
    CREATE_FACTORY(ParamStep);
}
//-----------------------------------------------------------------------
SceneTrans::~SceneTrans(void)
{ }
//-----------------------------------------------------------------------
void SceneTrans::trans(ViewComponent* from, ViewComponent* to, TransType type)
{
    if (m_pTrans != nullptr)
    {
        return;
    }

    if (from == nullptr)
    {
        // to do
    }
    else if (to == nullptr)
    {
        assert(0);
    }
    else
    {
        switch (type)
        {
        case TransType::TT_Overlay:
            m_pTrans = new OverlayTrans(std::bind(&SceneTrans::_onFinish, this));
            break;
        case TransType::TT_OneByOne:
            m_pTrans = new OneByOneTrans(std::bind(&SceneTrans::_onFinish, this));
            break;
        case TransType::TT_Cross:
            m_pTrans = new CrossTrans(std::bind(&SceneTrans::_onFinish, this));
            break;
        default:
            assert(0);
            break;
        }
    }

    m_pTrans->trans(from, to);
}
//-----------------------------------------------------------------------
void SceneTrans::_onFinish()
{
    if (m_pTrans != nullptr)
    {
        delete m_pTrans;
        m_pTrans = nullptr;
    }
}
//-----------------------------------------------------------------------
VoidStep* SceneTrans::_createVoidStep(const BaseStep::Key& key, VoidStep::CallbackFun func)
{
    VoidStep* pVoidStep = dynamic_cast<VoidStep*>(FactoryManager::getSingleton().createObject(GET_OBJECT_TYPE(VoidStep), BLANK));
    if (pVoidStep != nullptr)
    {
        pVoidStep->initialize(key, func);
    }
    return pVoidStep;
}
//-----------------------------------------------------------------------
ParamStep* SceneTrans::_createParamStep(const BaseStep::Key& key, ParamStep::CallbackFun func)
{
    ParamStep* pParamStep = dynamic_cast<ParamStep*>(FactoryManager::getSingleton().createObject(GET_OBJECT_TYPE(ParamStep), BLANK));
    if (pParamStep != nullptr)
    {
        pParamStep->initialize(key, func);
    }
    return pParamStep;
}
//-----------------------------------------------------------------------
void SceneTrans::_destroyBaseStep(BaseStep* step)
{
    FactoryManager::getSingleton().destroyObject(step);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
SceneTrans::Trans::Trans(CallbackFun func)
    : m_pFrom(nullptr)
    , m_pTo(nullptr)
    , m_pParent(nullptr)
    , m_func(func)
{

}
//-----------------------------------------------------------------------
SceneTrans::Trans::~Trans()
{
    if (m_pFrom != nullptr)
    {
        m_pFrom->addListener(this);
    }
    if (m_pTo != nullptr)
    {
        m_pTo->addListener(this);
    }

    for (std::vector<BaseStep*>::iterator it = m_steps.begin();
        it != m_steps.end(); 
        it++)
    {
        SceneTrans::getSingleton()._destroyBaseStep(*it);
    }
    m_steps.clear();
}
//-----------------------------------------------------------------------
void SceneTrans::Trans::trans(ViewComponent* from, ViewComponent* to)
{
    if (from != nullptr)
    {
        from->addListener(this);
    }
    if (to != nullptr)
    {
        to->addListener(this);
    }
}
//-----------------------------------------------------------------------
void SceneTrans::Trans::onViewCompStateChanged(ViewComponent* viewComp, ViewComponent::ViewCompState newState)
{
    /*
    BaseStep::Key key(viewComp, newState);

    std::vector<BaseStep*>::const_iterator it = m_steps.begin();
    if (it != m_steps.end())
    {
        BaseStep* pStep = *it;
        if (pStep->isThisStep(key))
        {
            u2::String szType = pStep->getType();
            if (szType == GET_OBJECT_TYPE(VoidStep))
            {
                VoidStep* pVoidStep = (VoidStep*)pStep;
                pVoidStep->call();
                m_steps.erase(it);
                SceneTrans::getSingleton()._destroyBaseStep(pVoidStep);
            }
            else if (szType == GET_OBJECT_TYPE(ParamStep))
            {
                ParamStep* pParamStep = (ParamStep*)pStep;
                pParamStep->call(m_pParent);
                m_steps.erase(it);
                SceneTrans::getSingleton()._destroyBaseStep(pParamStep);
            }
            else
            {
                assert(0);
            }
        }
    }
    */
}
//-----------------------------------------------------------------------
void SceneTrans::Trans::_onToEntered()
{
    m_pTo = nullptr;
    m_pFrom = nullptr;
    m_pParent = nullptr;
    m_func();
}
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
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
SceneTrans::OneByOneTrans::OneByOneTrans(CallbackFun func) 
    : Trans(func)
{

}
//-----------------------------------------------------------------------
void SceneTrans::OneByOneTrans::trans(ViewComponent* from, ViewComponent* to)
{
    SceneTrans::Trans::trans(from, to);

    m_pTo = to;
    m_pFrom = from;

    if (m_pFrom == nullptr)
    {
        m_pParent = nullptr;
        
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loading), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createParamStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attaching), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&ViewComponent::enter, m_pTo)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entering), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&SceneTrans::OneByOneTrans::_onToEntered, this)));

        m_pTo->loadUi();
    }
    else
    {
        m_pParent = m_pFrom->getParent();
        
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Exiting), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createParamStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Exited), std::bind(&ViewComponent::detach, from, std::placeholders::_1)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Detaching), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Detached), std::bind(&ViewComponent::unloadUi, m_pFrom)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Unloading), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Unloaded), std::bind(&ViewComponent::loadUi, m_pTo)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loading), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createParamStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attaching), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&ViewComponent::enter, m_pTo)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entering), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&SceneTrans::OneByOneTrans::_onToEntered, this)));

        m_pFrom->exit();

        // ===== 下面这部分弄好协程后要删除
        m_pFrom->detach(m_pParent);
        m_pFrom->unloadUi();
        m_pTo->loadUi();
        m_pTo->attach(m_pParent);
        m_pTo->enter();
        _onToEntered();
        // =====
    }
}
/**
-- CHILD load()
-- CHILD loading
-- CHILD loaded
-- CHILD attach()
-- CHILD enter()
-- CHILD didEnter
-- callback()
*/
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
SceneTrans::OverlayTrans::OverlayTrans(CallbackFun func)
    : Trans(func)
{

}
//-----------------------------------------------------------------------
void SceneTrans::OverlayTrans::trans(ViewComponent* parent, ViewComponent* child)
{
    SceneTrans::Trans::trans(parent, child);

    m_pTo = child;
    m_pParent = parent;

    if (m_pTo == nullptr)
    {
        _onToEntered();
    }
    else
    {
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loading), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createParamStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attaching), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&ViewComponent::enter, m_pTo)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entering), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&SceneTrans::OverlayTrans::_onToEntered, this)));

        m_pTo->loadUi();
    }
}
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
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
SceneTrans::CrossTrans::CrossTrans(CallbackFun func)
    : Trans(func)
{

}
//-----------------------------------------------------------------------
void SceneTrans::CrossTrans::trans(ViewComponent* from, ViewComponent* to)
{
    SceneTrans::Trans::trans(from, to);

    m_pTo = to;
    m_pFrom = from;
    m_pParent = m_pFrom->getParent();

    if (m_pTo == nullptr)
    {
        _onToEntered();
    }
    else
    {
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loading), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createParamStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attaching), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&SceneTrans::CrossTrans::_onToAttached, this)));
        m_steps.push_back(SceneTrans::getSingleton()._createParamStep(BaseStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&ViewComponent::detach, m_pFrom, std::placeholders::_1)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Detaching), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Detached), std::bind(&ViewComponent::unloadUi, m_pFrom)));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Unloading), nullptr));
        m_steps.push_back(SceneTrans::getSingleton()._createVoidStep(BaseStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Unloaded), std::bind(&SceneTrans::CrossTrans::_onToEntered, this)));

        m_pTo->loadUi();
    }
}
//-----------------------------------------------------------------------
void SceneTrans::CrossTrans::_onToAttached()
{
    m_pFrom->exit();
    m_pTo->enter();
}