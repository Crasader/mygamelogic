//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __CgViewComponents__
#define __CgViewComponents__


#include "U2Prerequisites.h"
#include "U2CocosViewComponent.h"
#include "CgPrerequisites.h"


U2EG_NAMESPACE_USING


class CgViewComponent : public CocosViewComponent
{
public:
	CgViewComponent(const String& type, const String& name);

	virtual ~CgViewComponent(void);

    virtual const String& getUiName() const override;

    void runCgAction();

public:
    static const String AN_CgAction;
};


class StartPageViewComponent : public CocosViewComponent
{
public:
    StartPageViewComponent(const String& type, const String& name);

    virtual ~StartPageViewComponent(void);

    virtual const String& getUiName() const override;

    void runStartAction();

public:
    static const String AN_StartAction;
};


#endif /* defined(__CgViewComponents__) */
