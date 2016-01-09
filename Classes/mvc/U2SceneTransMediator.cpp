//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//


#include "U2SceneTransMediator.h"

#include "U2ViewComponent.h"



U2EG_NAMESPACE_USING


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
SceneTrans::SceneTrans()
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
    m_pTo = to;
    m_pFrom = from;

    if (to == nullptr)
    {
        assert(0);
    }

    _registerFrameListener();

    if (from == nullptr)
    {
        // to do
    }
    else
    {
        switch (type)
        {
        case TransType::TT_Overlay:
        {
            m_pParent = m_pFrom;

            m_steps.push_back(_createParamStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&ViewComponent::enter, m_pTo)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&SceneTrans::_onTransOver, this)));

            m_pTo->loadUi();
            break;
        }
        case TransType::TT_OneByOne:
        {
            m_pParent = m_pFrom->getParent();

            m_steps.push_back(_createParamStep(TransStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Exited), std::bind(&ViewComponent::detach, from, std::placeholders::_1)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Detached), std::bind(&ViewComponent::unloadUi, m_pFrom)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Unloaded), std::bind(&ViewComponent::loadUi, m_pTo)));
            m_steps.push_back(_createParamStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&ViewComponent::enter, m_pTo)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&SceneTrans::_onTransOver, this)));
            
            m_pFrom->exit();
            break;
        }
        case TransType::TT_Cross:
        {
            m_pParent = m_pFrom->getParent();

            m_steps.push_back(_createParamStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&SceneTrans::_onCrossToAttached, this)));
            m_steps.push_back(_createParamStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&ViewComponent::detach, m_pFrom, std::placeholders::_1)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Detached), std::bind(&ViewComponent::unloadUi, m_pFrom)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Unloaded), std::bind(&SceneTrans::_onTransOver, this)));

            m_pTo->loadUi();
            break;
        }
        default:
            assert(0);
            break;
        }
    }
}
//-----------------------------------------------------------------------
void SceneTrans::_onCrossToAttached()
{
    m_pFrom->exit();
    m_pTo->enter();
}
//-----------------------------------------------------------------------
void SceneTrans::_onTransOver()
{
}
//-----------------------------------------------------------------------
VoidStep* SceneTrans::_createVoidStep(const TransStep::Key& key, VoidStep::CallbackFun func)
{
    VoidStep* pVoidStep = dynamic_cast<VoidStep*>(FactoryManager::getSingleton().createObject(GET_OBJECT_TYPE(VoidStep), BLANK));
    if (pVoidStep != nullptr)
    {
        pVoidStep->initialize(key, func);
    }
    return pVoidStep;
}
//-----------------------------------------------------------------------
ParamStep* SceneTrans::_createParamStep(const TransStep::Key& key, ParamStep::CallbackFun func)
{
    ParamStep* pParamStep = dynamic_cast<ParamStep*>(FactoryManager::getSingleton().createObject(GET_OBJECT_TYPE(ParamStep), BLANK));
    if (pParamStep != nullptr)
    {
        pParamStep->initialize(key, func);
    }
    return pParamStep;
}
//-----------------------------------------------------------------------
void SceneTrans::_destroyTransStep(TransStep* step)
{
    FactoryManager::getSingleton().destroyObject(step);
}
//-----------------------------------------------------------------------
void SceneTrans::_onUpdate(float dt)
{
    if (m_pTo == nullptr)
    {
        return;
    }

    std::vector<TransStep*>::const_iterator it = m_steps.begin();
    if (it != m_steps.end())
    {
        TransStep* pStep = *it;
        if (pStep->isThisStep(m_curKey))
        {
            u2::String szType = pStep->getType();
            if (szType == GET_OBJECT_TYPE(VoidStep))
            {
                VoidStep* pVoidStep = (VoidStep*)pStep;
                pVoidStep->call();
                m_steps.erase(it);
                _destroyTransStep(pVoidStep);
            }
            else if (szType == GET_OBJECT_TYPE(ParamStep))
            {
                ParamStep* pParamStep = (ParamStep*)pStep;
                pParamStep->call(m_pParent);
                m_steps.erase(it);
                _destroyTransStep(pParamStep);
            }
            else
            {
                assert(0);
            }
        }
    }
    
    if (m_steps.empty())
    {
        m_pFrom     = nullptr;
        m_pTo       = nullptr;
        m_pParent   = nullptr;
        m_curKey    = TransStep::Key(nullptr, ViewComponent::ViewCompState::VCS_Unloaded);
        _unregisterFrameListener();
    }
}
//-----------------------------------------------------------------------
void SceneTrans::onViewCompStateChanged(ViewComponent* viewComp, ViewComponent::ViewCompState newState)
{
    m_curKey = TransStep::Key(viewComp, newState);
}