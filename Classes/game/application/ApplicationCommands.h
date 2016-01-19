//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __ApplicationCommands__
#define __ApplicationCommands__


#include "U2GameBase.h"


U2EG_NAMESPACE_USING


class Context;


class StartupCommand : public SimpleCommand
{
public:
    StartupCommand(const String& type, const String& name);
    virtual ~StartupCommand();

    virtual void go(const Notification& notification) override;
};


class Trans2ShadeCommand : public SimpleCommand
{
public:
    Trans2ShadeCommand(const String& type, const String& name);
    virtual ~Trans2ShadeCommand();

    virtual void go(const Notification& notification) override;
};


class Trans2LogoCommand : public TransCommand
{
public:
    Trans2LogoCommand(const String& type, const String& name);
    virtual ~Trans2LogoCommand();

    virtual void go(const Notification& notification) override;
};


#endif /* defined(__ApplicationCommands__) */
