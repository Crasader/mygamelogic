//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2PredefinedCommand__
#define __U2PredefinedCommand__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "U2SimpleCommand.h"


U2EG_NAMESPACE_USING


class Context;


/** Destroy Context and it's children, the Mediator and the ViewComponent 
    which attached to this context will be destroyed also.
    @note do not call this command directly, you should control contexts with ContextProxy.
*/
class DestoryContextCommand : public SimpleCommand
{
public:
    DestoryContextCommand(const String& type, const String& name);
    virtual ~DestoryContextCommand();

    virtual void go(const Notification& notification) override;

protected:
    void _destroyContext(u2::Context* context);
};


class BackKeyCommand : public SimpleCommand
{
public:
    BackKeyCommand(const String& type, const String& name);
    virtual ~BackKeyCommand();

    virtual void go(const Notification& notification) override;

protected:
    bool _dispatchBack(u2::Context* context);
};


#endif /* defined(Trans2Command) */
