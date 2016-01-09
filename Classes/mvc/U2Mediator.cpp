//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2Mediator.h"

#include "U2ViewComponent.h"
#include "U2Context.h"


U2EG_NAMESPACE_USING


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Mediator::Mediator(const String& type, const String& name)
    : Object(type, name)
    , m_pViewComp(nullptr)
	, m_bCreator(false)
    , m_pFrom(nullptr)
    , m_pTo(nullptr)
    , m_pParent(nullptr)
    , m_pFromContext(nullptr)
{
    CREATE_FACTORY(VoidStep);
    CREATE_FACTORY(ParamStep);
}
//-----------------------------------------------------------------------
Mediator::~Mediator(void)
{
}
//-----------------------------------------------------------------------
void Mediator::startup(const u2::Context* from, Mediator::TransType type, const u2::Context* to)
{
    m_pFromContext = (u2::Context*)from;

	m_bCreator = false;
    m_pViewComp = ViewComponentManager::getSingleton().retrieveObject(to->getViewCompClass(), to->getViewCompName());
	if (m_pViewComp == nullptr)
	{
        m_pViewComp = ViewComponentManager::getSingleton().createObject(to->getViewCompClass(), to->getViewCompName());
		m_bCreator = true;
	}
    m_pViewComp->addListener(this);

    _registerFrameListener();

    if (m_bCreator)
    {
        ViewComponent* pFromViewComp = nullptr;
        if (from != nullptr)
        {
            pFromViewComp = ViewComponentManager::getSingleton().retrieveObject(from->getViewCompClass(), from->getViewCompName());
            pFromViewComp->addListener(this);
        }
        _trans(pFromViewComp, type, m_pViewComp);
    }
}
//-----------------------------------------------------------------------
void Mediator::end()
{
    if (m_pViewComp != nullptr)
    {
        m_pViewComp->removeListener(this);

        if (m_bCreator)
        {
            ViewComponentManager::getSingleton().destoryObject(m_pViewComp);
        }
        else
        {
            m_pViewComp = nullptr;
        }
    }

    _unregisterFrameListener();
}
//-----------------------------------------------------------------------
inline void Mediator::setViewComponent(ViewComponent* view_component)
{
    m_pViewComp = view_component;
}
//-----------------------------------------------------------------------
inline void const* Mediator::getViewComponent(void) const
{
    return m_pViewComp;
}
//-----------------------------------------------------------------------
inline Mediator::NotificationNames Mediator::listNotificationInterests(void) const
{
    return std::list<std::string>();
}
//-----------------------------------------------------------------------
inline void Mediator::handleNotification(const Notification& notification)
{
    (void)notification;
}
//-----------------------------------------------------------------------
inline void Mediator::onRegister(void)
{ }
//-----------------------------------------------------------------------
inline void Mediator::onRemove(void)
{ }
//-----------------------------------------------------------------------
void Mediator::_trans(ViewComponent* from, TransType type, ViewComponent* to)
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
void Mediator::_onOneByOneFromExited()
{
    m_pFrom->detach(m_pParent);
    m_pFrom->unloadUi();
    m_pTo->loadUi();
    m_pTo->attach(m_pParent);
}
//-----------------------------------------------------------------------
void Mediator::_onCrossToAttached()
{
    m_pFrom->exit();
    m_pTo->enter();
}
//-----------------------------------------------------------------------
void Mediator::_destroyContext(u2::Context* context)
{
    if (context == nullptr)
    {
        return;
    }

    u2::Context::ContextListIterator it = context->getContextIterator();
    while (it.hasMoreElements())
    {
        _destroyContext(it.getNext());
    }

    Mediator* pMediator = MediatorManager::getSingleton().retrieveObject(context->getMediatorName());
    if (pMediator != nullptr)
    {
        pMediator->end();
        MediatorManager::getSingleton().destoryObject(pMediator);
    }
    ContextManager::getSingleton().destoryObject(context);
}
//-----------------------------------------------------------------------
void Mediator::_onTransOver()
{
    
}
//-----------------------------------------------------------------------
VoidStep* Mediator::_createVoidStep(const TransStep::Key& key, VoidStep::CallbackFun func)
{
    VoidStep* pVoidStep = dynamic_cast<VoidStep*>(FactoryManager::getSingleton().createObject(GET_OBJECT_TYPE(VoidStep), BLANK));
    if (pVoidStep != nullptr)
    {
        pVoidStep->initialize(key, func);
    }
    return pVoidStep;
}
//-----------------------------------------------------------------------
ParamStep* Mediator::_createParamStep(const TransStep::Key& key, ParamStep::CallbackFun func)
{
    ParamStep* pParamStep = dynamic_cast<ParamStep*>(FactoryManager::getSingleton().createObject(GET_OBJECT_TYPE(ParamStep), BLANK));
    if (pParamStep != nullptr)
    {
        pParamStep->initialize(key, func);
    }
    return pParamStep;
}
//-----------------------------------------------------------------------
void Mediator::_destroyTransStep(TransStep* step)
{
    FactoryManager::getSingleton().destroyObject(step);
}
//-----------------------------------------------------------------------
void Mediator::onUpdate(float dt)
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
        m_pFrom = nullptr;
        m_pTo = nullptr;
        m_pParent = nullptr;
        m_curKey = TransStep::Key(nullptr, ViewComponent::ViewCompState::VCS_Unloaded);
        if (m_pFromContext != nullptr)
        {
            if (m_transType == Mediator::TransType::TT_OneByOne 
                || m_transType == Mediator::TransType::TT_Cross)
            {
                _destroyContext(m_pFromContext);
            }
            m_pFromContext = nullptr;
        }
    }
}
//-----------------------------------------------------------------------
void Mediator::onViewCompStateChanged(ViewComponent* viewComp, ViewComponent::ViewCompState newState)
{
    m_curKey = TransStep::Key(viewComp, newState);
}


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
template<> MediatorManager* Singleton<MediatorManager>::msSingleton = 0;
MediatorManager* MediatorManager::getSingletonPtr(void)
{
	if (msSingleton == nullptr)
	{
		msSingleton = new MediatorManager;
	}
    return msSingleton;
}
MediatorManager& MediatorManager::getSingleton(void)
{
	return (*getSingletonPtr());
}
//-----------------------------------------------------------------------
MediatorManager::MediatorManager()
{
}
//-----------------------------------------------------------------------
MediatorManager::~MediatorManager()
{
}