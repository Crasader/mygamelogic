//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __ApplicationCommands__
#define __ApplicationCommands__


#include "U2Prerequisites.h"
#include "U2SimpleCommand.h"
#include "U2Mediator.h"
#include "U2PredefinedCommands.h"
#include "U2PredefinedMediators.h"


U2EG_NAMESPACE_USING


class Context;


class StartupCommand : public SimpleCommand
{
public:
    StartupCommand(const String& type, const String& name);
    virtual ~StartupCommand();

    virtual void go(const Notification& notification) override;
};


class Trans2ShadeCommand : public TransCommand
{
public:
    Trans2ShadeCommand(const String& type, const String& name);
    virtual ~Trans2ShadeCommand();

protected:
    virtual u2::Context* _createToContext() override;
    virtual u2::Context* _retrieveFromContext() override;
    virtual TransMediator::TransType _retrieveTransType() override;
};


class Trans2LogoCommand : public TransCommand
{
public:
    Trans2LogoCommand(const String& type, const String& name);
    virtual ~Trans2LogoCommand();

protected:
    virtual u2::Context* _createToContext() override;
    virtual u2::Context* _retrieveFromContext() override;
    virtual TransMediator::TransType _retrieveTransType() override;
};


#endif /* defined(__ApplicationCommands__) */
