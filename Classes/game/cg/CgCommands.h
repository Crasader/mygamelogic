//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __CgCommands__
#define __CgCommands__


#include "U2GameBase.h"


U2EG_NAMESPACE_USING


class Trans2CgCommand : public SimpleCommand
{
public:
    Trans2CgCommand(const String& type, const String& name);
    virtual ~Trans2CgCommand();

    virtual void go(const Notification& notification) override;
};


class Trans2StartPageCommand : public SimpleCommand
{
public:
    Trans2StartPageCommand(const String& type, const String& name);
    virtual ~Trans2StartPageCommand();

    virtual void go(const Notification& notification) override;
};


#endif /* defined(__CgCommands__) */
