//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __ApplicationPrerequisites__
#define __ApplicationPrerequisites__


#include "U2Prerequisites.h"


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
const String CQN_Shade          = "CQN_Shade";
const String CQN_Scene          = "CQN_Scene";
const String CQN_Tab            = "CQN_Tab";
const String CQN_Dialog         = "CQN_Dialog";
const String CQN_Common         = "CQN_Common";

#endif /* defined(__ApplicationPrerequisites__) */
