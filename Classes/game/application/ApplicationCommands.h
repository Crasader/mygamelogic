//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __ApplicationCommands__
#define __ApplicationCommands__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "U2SimpleCommand.h"
#include "U2Mediator.h"
#include "Trans2Command.h"


U2EG_NAMESPACE_USING


class Context;


class StartupCommand : public SimpleCommand
{
public:
    StartupCommand(const String& type, const String& name);
    virtual ~StartupCommand();

    virtual void go(const Notification& notification) override;
};


class SceneTransCommand : public SimpleCommand
{
public:
    SceneTransCommand(const String& type, const String& name);
    virtual ~SceneTransCommand();

    virtual void go(const Notification& notification) override;

protected:
    void _createMediator(const u2::Context* context, Mediator::TransType type, const u2::Context* to);
};


class DestroyContextCommand : public SimpleCommand
{
public:
    DestroyContextCommand(const String& type, const String& name);
    virtual ~DestroyContextCommand();

    virtual void go(const Notification& notification) override;

protected:
    void _destroyContext(u2::Context* context);
};


class Trans2LogoCommand : public Trans2Command
{
public:
    Trans2LogoCommand(const String& type, const String& name);
    virtual ~Trans2LogoCommand();

protected:
    virtual u2::Context* _createToContext() override;
    virtual u2::Context* _retrieveFromContext() override;
    virtual Mediator::TransType _retrieveTransType() override;
};


#endif /* defined(__ApplicationCommands__) */
