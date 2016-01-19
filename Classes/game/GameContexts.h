//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __GameContexts__
#define __GameContexts__


#include "U2GameBase.h"


U2EG_NAMESPACE_USING


class ShadeContext : public u2::Context
{
public:
    ShadeContext(const String& type, const String& name);
    virtual ~ShadeContext();
};


class SceneContext : public u2::Context
{
public:
    SceneContext(const String& type, const String& name);
    virtual ~SceneContext();
};


class TabContext : public u2::Context
{
public:
    TabContext(const String& type, const String& name);
    virtual ~TabContext();
};


class CommonContext : public u2::Context
{
public:
    CommonContext(const String& type, const String& name);
    virtual ~CommonContext();
};


class DialogContext : public u2::Context
{
public:
    DialogContext(const String& type, const String& name);
    virtual ~DialogContext();
};


#endif /* defined(__GameContexts__) */
