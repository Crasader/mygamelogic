//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2CocosMediator.h"



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
CocosMediator::CocosMediator(const String& type, const String& name)
    : Mediator(type, name)
    , m_pScheduler(nullptr)
{
}
//-----------------------------------------------------------------------
CocosMediator::~CocosMediator(void)
{
}
//-----------------------------------------------------------------------
void CocosMediator::_registerFrameListener()
{
    if (m_pScheduler == nullptr)
    {
        m_pScheduler = cocos2d::Director::getInstance()->getScheduler();
        m_pScheduler->schedule(schedule_selector(CocosMediator::onUpdate), this, 0.1f, CC_REPEAT_FOREVER, 0.1f, false);
    }
}
//-----------------------------------------------------------------------
void CocosMediator::_unregisterFrameListener()
{
    if (m_pScheduler != nullptr)
    {
        m_pScheduler->unschedule(schedule_selector(CocosMediator::onUpdate), this);
        m_pScheduler = nullptr;
    }
}