//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __LogoFacade__
#define __LogoFacade__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "LogoPrerequisites.h"
#include "U2Facade.h"


U2EG_NAMESPACE_USING


class LogoFacade : public Facade
{
public:
	/**
	* Constructor.
	*
	* <P>
	* This <code>Facade</code> implementation is a Multiton,
	* so you should not call the constructor
	* directly, but instead call the static Factory method,
	* passing the unique key for this instance
	* <code>Facade.getInstance( multitonKey )</code>
	*
	* @throws Error Error if instance for this Multiton key has already been constructed
	*
	*/
    explicit LogoFacade(const String& type, const String& name);

    /**
    * Virtual destructor.
    */
    virtual ~LogoFacade(void);

    static LogoFacade& getInstance(void);

    virtual void initializeController(void) override;
	
    void startup();
};


#endif /* defined(__LogoFacade__) */
