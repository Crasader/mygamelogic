//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __CgCommands__
#define __CgCommands__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "U2SimpleCommand.h"
#include "Trans2Command.h"


U2EG_NAMESPACE_USING


class StartCgCommand : public SimpleCommand
{
public:
    StartCgCommand(const String& type, const String& name);
    virtual ~StartCgCommand();

    virtual void go(const Notification& notification) override;
};


class Trans2CgCommand : public Trans2Command
{
public:
    Trans2CgCommand(const String& type, const String& name);
    virtual ~Trans2CgCommand();

protected:
    virtual u2::Context* _createToContext() override;
    virtual u2::Context* _retrieveFromContext() override;
    virtual Mediator::TransType _retrieveTransType() override;
};


#endif /* defined(__CgCommands__) */
