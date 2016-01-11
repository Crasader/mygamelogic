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
extern const char* OT_ContextProxy;

// command
extern const char* OT_StartupCommand;
extern const char* OT_DestroyContextCommand;
extern const char* OT_Trans2LogoCommand;
extern const char* OT_SceneTransCommand;

// view
extern const char* OT_ShadeMediator;
extern const char* OT_ShadeViewComponent;
extern const char* OT_LogoMediator;
extern const char* OT_LogoViewComponent;


const String NTF_Application_Startup            = "NTF_Application_Startup";
const String NTF_Application_Trans2Logo         = "NTF_Application_Trans2Logo";
const String NTF_Application_SceneTrans         = "NTF_Application_SceneTrans";

#endif /* defined(__ApplicationPrerequisites__) */
