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
const String NTF_Application_Startup            = "NTF_Application_Startup";
const String NTF_Application_Trans2Shade        = "NTF_Application_Trans2Shade";
const String NTF_Application_Trans2Logo         = "NTF_Application_Trans2Logo";

// context
extern const char* OT_ShadeContext;
extern const char* OT_SceneContext;
extern const char* OT_TabContext;
extern const char* OT_DialogContext;
extern const char* OT_CommonContext;

// context queue name
const String ON_ContextQueue_Shade              = "ON_ContextQueue_Shade";
const String ON_ContextQueue_Scene              = "ON_ContextQueue_Scene";
const String ON_ContextQueue_Tab                = "ON_ContextQueue_Tab";
const String ON_ContextQueue_Dialog             = "ON_ContextQueue_Dialog";
const String ON_ContextQueue_Common             = "ON_ContextQueue_Common";

#endif /* defined(__ApplicationPrerequisites__) */
