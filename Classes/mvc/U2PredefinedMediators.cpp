//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2PredefinedMediators.h"

#include "U2ViewComponent.h"
#include "U2Facade.h"
#include "U2Context.h"


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
TransMediator::TransMediator(const String& type, const String& name)
    : Mediator(type, name)
    , m_pFrom(nullptr)
    , m_pTo(nullptr)
    , m_pFromContext(nullptr)
    , m_pToContext(nullptr)
    , m_pParent(nullptr)
{
    CREATE_FACTORY(VoidStep);
    CREATE_FACTORY(ParamStep);
}
//-----------------------------------------------------------------------
TransMediator::~TransMediator(void)
{

}
//-----------------------------------------------------------------------
void Mediator::startup(const u2::Context* context)
{
    assert(0);
}
//-----------------------------------------------------------------------
void TransMediator::startup(const u2::Context* from, TransMediator::TransType type, const u2::Context* to)
{
    ViewComponent* pFromViewComp = nullptr;
    if (from != nullptr)
    {
        pFromViewComp = ViewComponentManager::getSingleton().retrieveObject(from->getViewCompClass(), from->getViewCompName());
        pFromViewComp->addListener(this);
    }

    ViewComponent* pToViewComp = nullptr;
    if (to == nullptr)
    {
        pToViewComp = ViewComponentManager::getSingleton().retrieveObject(to->getViewCompClass(), to->getViewCompName());
        pToViewComp->addListener(this);
    }
    
    _trans(pFromViewComp, type, m_pViewComp);
}
//-----------------------------------------------------------------------
void TransMediator::end()
{
	Mediator::end();
}
//-----------------------------------------------------------------------
void TransMediator::_trans(ViewComponent* from, TransType type, ViewComponent* to)
{
    m_pTo = to;
    m_pFrom = from;
    m_transType = type;

    if (to == nullptr)
    {
        assert(0);
    }

    if (from == nullptr)
    {
        //         m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo)));
        //         m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&ViewComponent::enter, m_pTo)));
        m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&Mediator::_onTransOver, this)));

        m_pTo->loadUi();
    }
    else
    {
        switch (type)
        {
        case TransType::TT_Overlay:
        {
            m_pParent = m_pFrom->getParent();

            m_steps.push_back(_createParamStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&ViewComponent::enter, m_pTo)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&Mediator::_onTransOver, this)));

            m_pTo->loadUi();
            break;
        }
        case TransType::TT_OneByOne:
        {
            m_pParent = m_pFrom->getParent();

            m_steps.push_back(_createVoidStep(TransStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Exited), std::bind(&Mediator::_onOneByOneFromExited, this)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&ViewComponent::enter, m_pTo)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&Mediator::_onTransOver, this)));

            m_pFrom->exit();
            break;
        }
        case TransType::TT_Cross:
        {
            m_pParent = m_pFrom->getParent();

            m_steps.push_back(_createParamStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Loaded), std::bind(&ViewComponent::attach, m_pTo, std::placeholders::_1)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Attached), std::bind(&Mediator::_onCrossToAttached, this)));
            m_steps.push_back(_createParamStep(TransStep::Key(m_pTo, ViewComponent::ViewCompState::VCS_Entered), std::bind(&ViewComponent::detach, m_pFrom, std::placeholders::_1)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Detached), std::bind(&ViewComponent::unloadUi, m_pFrom)));
            m_steps.push_back(_createVoidStep(TransStep::Key(m_pFrom, ViewComponent::ViewCompState::VCS_Unloaded), std::bind(&Mediator::_onTransOver, this)));

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
void TransMediator::_onOneByOneFromExited()
{
    m_pFrom->detach(m_pParent);
    m_pFrom->unloadUi();
    m_pTo->loadUi();
    m_pTo->attach(m_pParent);
}
//-----------------------------------------------------------------------
void TransMediator::_onCrossToAttached()
{
    m_pFrom->exit();
    m_pTo->enter();
}
//-----------------------------------------------------------------------
void TransMediator::_onTransOver()
{
    _destroyFromContext();
    _startupToContext(m_pToContext);
    _destroyTransMediator();
}
//-----------------------------------------------------------------------
void TransMediator::_destroyTransMediator()
{
    m_pFrom = nullptr;
    m_pTo = nullptr;
    m_pFromContext = nullptr;
    m_pToContext = nullptr;
    m_pParent = nullptr;
    m_curKey = TransStep::Key(nullptr, ViewComponent::ViewCompState::VCS_Unloaded);

    this->end();
    MediatorManager::getSingleton().destoryObject(this);
}
//-----------------------------------------------------------------------
void TransMediator::_destroyFromContext()
{
    if (m_pFromContext != nullptr)
    {
        if (m_transType == Mediator::TransType::TT_OneByOne
            || m_transType == Mediator::TransType::TT_Cross)
        {
            getFacade().sendNotification(NTF_Application_DestroyContext, m_pFromContext);
        }
    }
}
//-----------------------------------------------------------------------
void TransMediator::_startupToContext(u2::Context* context)
{
    if (context == nullptr)
    {
        return;
    }

    Mediator* pMediator = MediatorManager::getSingleton().retrieveObject(context->getMediatorName());
    if (pMediator != nullptr)
    {
        pMediator->startup(m_pToContext);
    }

    u2::Context::ContextListIterator it = context->getContextIterator();
    while (it.hasMoreElements())
    {
        _destroyContext(it.getNext());
    }
}
//-----------------------------------------------------------------------
TransStep* TransMediator::_createVoidStep(const TransStep::Key& key, VoidStep::CallbackFun func)
{
    VoidStep* pVoidStep = dynamic_cast<VoidStep*>(FactoryManager::getSingleton().createObject(GET_OBJECT_TYPE(VoidStep), BLANK));
    if (pVoidStep != nullptr)
    {
        pVoidStep->initialize(key, func);
    }
    return pVoidStep;
}
//-----------------------------------------------------------------------
TransStep* TransMediator::_createParamStep(const TransStep::Key& key, ParamStep::CallbackFun func)
{
    ParamStep* pParamStep = dynamic_cast<ParamStep*>(FactoryManager::getSingleton().createObject(GET_OBJECT_TYPE(ParamStep), BLANK));
    if (pParamStep != nullptr)
    {
        pParamStep->initialize(key, func);
    }
    return pParamStep;
}
//-----------------------------------------------------------------------
void TransMediator::_destroyTransStep(TransStep* step)
{
    FactoryManager::getSingleton().destroyObject(step);
}
//-----------------------------------------------------------------------
void TransMediator::onUpdate(float dt)
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

}
//-----------------------------------------------------------------------
void TransMediator::onViewCompStateChanged(ViewComponent* viewComp, ViewComponent::ViewCompState newState)
{
    m_curKey = TransStep::Key(viewComp, newState);
}