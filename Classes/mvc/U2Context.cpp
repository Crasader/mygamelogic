//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2Context.h"


U2EG_NAMESPACE_USING


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Context::Context(const String& type, const String& name)
    : Object(type, name)
{

}
//-----------------------------------------------------------------------
Context::~Context()
{
}
//-----------------------------------------------------------------------
void Context::initialize(const u2::String& facadeName
    , const u2::String& parentContextName
    , const u2::String& mediatorClass, const u2::String& mediatorName
    , const u2::String& viewCompClass, const u2::String& viewCompName)
{
    m_szFacadeName = facadeName;
    m_szParentContextName = parentContextName;
    m_szMediatorClass = mediatorClass;
    m_szMediatorName = mediatorName;
    m_szViewCompClass = viewCompClass;
    m_szViewCompName = viewCompName;
}
//-----------------------------------------------------------------------
void Context::addChild(Context* child)
{
    for (ContextList::const_iterator it = m_children.begin();
        it != m_children.end(); 
        it++)
    {
        if (*it == child)
        {
            assert(0);
        }
    }
    m_children.push_back(child);
}
//-----------------------------------------------------------------------
void Context::removeChild(Context* child)
{
    for (ContextList::const_iterator it = m_children.begin();
        it != m_children.end();
        it++)
    {
        if (*it == child)
        {
            m_children.erase(it);
            return;
        }
    }
}
//-----------------------------------------------------------------------
Context::ConstContextListIterator Context::getConstContextIterator() const
{
    return ConstContextListIterator(m_children.begin(), m_children.end());
}
//-----------------------------------------------------------------------
Context::ContextListIterator Context::getContextIterator()
{
    return ContextListIterator(m_children.begin(), m_children.end());
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
template<> ContextManager* Singleton<ContextManager>::msSingleton = 0;
ContextManager* ContextManager::getSingletonPtr(void)
{
	if (msSingleton == nullptr)
	{
		msSingleton = new ContextManager;
	}
	return msSingleton;
}
ContextManager& ContextManager::getSingleton(void)
{
	return (*getSingletonPtr());
}
//-----------------------------------------------------------------------
ContextManager::ContextManager()
{
    CREATE_FACTORY(Context);
}
//-----------------------------------------------------------------------
ContextManager::~ContextManager()
{
}
//-----------------------------------------------------------------------
Context* ContextManager::createObject(const String& type, const String& name
    , const u2::String& facadeName
    , const u2::String& parentContextName
    , const u2::String& mediatorClass, const u2::String& mediatorName
    , const u2::String& viewCompClass, const u2::String& viewCompName)
{
    Context* pContext = createObject(type, name);
    pContext->initialize(facadeName, parentContextName
        , mediatorClass, mediatorName, viewCompClass, viewCompName);
    return pContext;
}
//-----------------------------------------------------------------------
Context* ContextManager::createObject(const String& type, const String& name)
{
    return SimpleObjectManager<Context>::createObject(type, name);
}