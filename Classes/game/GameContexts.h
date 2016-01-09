//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __GameContexts__
#define __GameContexts__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "U2Context.h"


U2EG_NAMESPACE_USING


class ShadeContext : public Context
{
public:
    ShadeContext(const String& type, const String& name);
    virtual ~ShadeContext();
};


class SceneContext : public Context
{
public:
    SceneContext(const String& type, const String& name);
    virtual ~SceneContext();
};


class TabContext : public Context
{
public:
    TabContext(const String& type, const String& name);
    virtual ~TabContext();
};


class DialogContext : public Context
{
public:
    DialogContext(const String& type, const String& name);
    virtual ~DialogContext();
};


class ChildContext : public Context
{
public:
    ChildContext(const String& type, const String& name);
    virtual ~ChildContext();
};


#endif /* defined(__GameContexts__) */
