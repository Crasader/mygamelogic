//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2CocosTransMediator__
#define __U2CocosTransMediator__


#include "U2Core.h"
#include "U2Mvc.h"
#include "cocos2d.h"


U2EG_NAMESPACE_USING


class CocosTransMediator : public TransMediator
{
public:
    CocosTransMediator(const String& type, const String& name);

    virtual ~CocosTransMediator(void);

protected:
    virtual void _registerFrameListener() override;

    virtual void _unregisterFrameListener() override;

protected:
    cocos2d::Scheduler* m_pScheduler;
};


#endif /* defined(__U2CocosTransMediator__) */
