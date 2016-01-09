//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __CgMediators__
#define __CgMediators__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "U2CocosMediator.h"
#include "CgPrerequisites.h"


U2EG_NAMESPACE_USING


class CgMediator : public CocosMediator
{
public:
	CgMediator(const String& type, const String& name);

	virtual ~CgMediator(void);

    virtual Mediator::NotificationNames listNotificationInterests(void) const override;

    virtual void handleNotification(const Notification& notification) override;

protected:
    virtual void _onTransOver() override;
    virtual void onCommonStateChanged(ViewComponent* viewComp, const String& objName, const String& msg) override;
};


class StartPageMediator : public CocosMediator
{
public:
    StartPageMediator(const String& type, const String& name);

    virtual ~StartPageMediator(void);

    virtual Mediator::NotificationNames listNotificationInterests(void) const override;

    virtual void handleNotification(const Notification& notification) override;

protected:
    virtual void _onTransOver() override;
};


#endif /* defined(__CgMediators__) */
