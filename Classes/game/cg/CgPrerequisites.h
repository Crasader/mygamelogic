//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __CgPrerequisites__
#define __CgPrerequisites__


#include "U2GameBase.h"


U2EG_NAMESPACE_USING


// facade
extern const char* OT_CgFacade;

// command
extern const char* OT_Trans2CgCommand;
extern const char* OT_Trans2StartPageCommand;

// mediator
extern const char* OT_CgMediator;
extern const char* OT_StartPageMediator;

// viewcomponent
extern const char* OT_CgViewComponent;
extern const char* OT_StartPageViewComponent;


// notification
const String NTF_Cg_Trans2Cg            = "NTF_Cg_Trans2Cg";
const String NTF_Cg_Trans2StartPage     = "NTF_Cg_Trans2StartPage";


// facade name
const String ON_Facade_Cg = "ON_Facade_Cg";

// context name
const String ON_Context_CgScene = "ON_Context_CgScene";
const String ON_Context_StartPageScene = "ON_Context_StartPageScene";


#endif /* defined(__CgPrerequisites__) */
