//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2CocosTransMediator.h"



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
CocosTransMediator::CocosTransMediator(const String& type, const String& name)
    : TransMediator(type, name)
    , m_pScheduler(nullptr)
{
}
//-----------------------------------------------------------------------
CocosTransMediator::~CocosTransMediator(void)
{
}
//-----------------------------------------------------------------------
void CocosTransMediator::_registerFrameListener()
{
    if (m_pScheduler == nullptr)
    {
        m_pScheduler = cocos2d::Director::getInstance()->getScheduler();
        m_pScheduler->schedule(schedule_selector(CocosTransMediator::onUpdate), this, 0.1f, CC_REPEAT_FOREVER, 0.1f, false);
    }
}
//-----------------------------------------------------------------------
void CocosTransMediator::_unregisterFrameListener()
{
    if (m_pScheduler != nullptr)
    {
        m_pScheduler->unschedule(schedule_selector(CocosTransMediator::onUpdate), this);
        m_pScheduler = nullptr;
    }
}