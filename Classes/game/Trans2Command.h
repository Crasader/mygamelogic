//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __Trans2Command__
#define __Trans2Command__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "U2SimpleCommand.h"
#include "U2Mediator.h"


U2EG_NAMESPACE_USING


class Context;


class Trans2Command : public SimpleCommand
{
public:
    Trans2Command(const String& type, const String& name);
    virtual ~Trans2Command();

    virtual void go(const Notification& notification) override;

protected:
    void _createMediator(const u2::Context* context, Mediator::TransType type, const u2::Context* to);
    virtual u2::Context* _createToContext() = 0;
    virtual u2::Context* _retrieveFromContext() = 0;
    virtual Mediator::TransType _retrieveTransType() = 0;
};


#endif /* defined(Trans2Command) */
