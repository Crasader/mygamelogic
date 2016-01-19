//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __ApplicationViewComponents__
#define __ApplicationViewComponents__


#include "U2GameBase.h"
#include "ApplicationPrerequisites.h"


U2EG_NAMESPACE_USING


class ShadeViewComponent : public CocosViewComponent
{
public:
    ShadeViewComponent(const String& type, const String& name);

    virtual ~ShadeViewComponent(void);

    virtual const String& getUiName() const override;

    virtual void loadUi() override;

    virtual void unloadUi() override;

protected:
};


class LogoViewComponent : public CocosViewComponent
{
public:
	LogoViewComponent(const String& type, const String& name);

	virtual ~LogoViewComponent(void);

    virtual const String& getUiName() const override;

    virtual void loadUi() override;

    void runLogoAction();

public:
    static const String AN_LogoAction;

protected:
};


#endif /* defined(__TabInfoViewComponent__) */
