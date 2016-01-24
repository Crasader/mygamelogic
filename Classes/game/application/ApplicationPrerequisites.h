//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __ApplicationPrerequisites__
#define __ApplicationPrerequisites__


#include "U2GameBase.h"


U2EG_NAMESPACE_USING


// facade
extern const char* OT_ApplicationFacade;

// proxy

// command
extern const char* OT_StartupCommand;
extern const char* OT_Trans2ShadeCommand;
extern const char* OT_Trans2LogoCommand;

// view
extern const char* OT_ShadeMediator;
extern const char* OT_ShadeViewComponent;
extern const char* OT_LogoMediator;
extern const char* OT_LogoViewComponent;

// notification
static const char* NTF_Application_Startup = "NTF_Application_Startup";
static const char* NTF_Application_Trans2Shade = "NTF_Application_Trans2Shade";
static const char* NTF_Application_Trans2Logo = "NTF_Application_Trans2Logo";

// context
extern const char* OT_ShadeContext;
extern const char* OT_SceneContext;
extern const char* OT_TabContext;
extern const char* OT_DialogContext;
extern const char* OT_CommonContext;

// facade name
static const char* ON_Facade_Application = "ON_Facade_Application";

// context queue name
static const char* ON_ContextQueue_Shade = "ON_ContextQueue_Shade";
static const char* ON_ContextQueue_Scene = "ON_ContextQueue_Scene";
static const char* ON_ContextQueue_Tab = "ON_ContextQueue_Tab";
static const char* ON_ContextQueue_Dialog = "ON_ContextQueue_Dialog";
static const char* ON_ContextQueue_Common = "ON_ContextQueue_Common";

// context name
static const char* ON_Context_Root = "ON_Context_Root";
static const char* ON_Context_LogoScene = "ON_Context_LogoScene";

#endif /* defined(__ApplicationPrerequisites__) */
