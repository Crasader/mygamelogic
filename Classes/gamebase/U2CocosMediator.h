﻿//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2CocosMediator__
#define __U2CocosMediator__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "U2Mediator.h"


U2EG_NAMESPACE_USING


class CocosMediator : public Mediator
{
public:
    CocosMediator(const String& type, const String& name);

    virtual ~CocosMediator(void);

protected:
    virtual void _registerFrameListener() override;

    virtual void _unregisterFrameListener() override;

protected:
    cocos2d::Scheduler* m_pScheduler;
};


#endif /* defined(__U2CocosMediator__) */
