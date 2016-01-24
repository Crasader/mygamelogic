//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#include "ApplicationPrerequisites.h"


#include "ApplicationFacade.h"
#include "ApplicationCommands.h"
#include "ApplicationMediators.h"
#include "ApplicationViewComponents.h"
#include "GameContexts.h"

const char* OT_ApplicationFacade = GET_OBJECT_TYPE(ApplicationFacade);

const char* OT_StartupCommand = GET_OBJECT_TYPE(StartupCommand);
const char* OT_Trans2ShadeCommand = GET_OBJECT_TYPE(Trans2ShadeCommand);
const char* OT_Trans2LogoCommand = GET_OBJECT_TYPE(Trans2LogoCommand);

const char* OT_ShadeMediator = GET_OBJECT_TYPE(ShadeMediator);
const char* OT_LogoMediator = GET_OBJECT_TYPE(LogoMediator);

const char* OT_ShadeViewComponent = GET_OBJECT_TYPE(ShadeViewComponent);
const char* OT_LogoViewComponent = GET_OBJECT_TYPE(LogoViewComponent);

const char* OT_ShadeContext = GET_OBJECT_TYPE(ShadeContext);
const char* OT_SceneContext = GET_OBJECT_TYPE(SceneContext);
const char* OT_TabContext = GET_OBJECT_TYPE(TabContext);
const char* OT_DialogContext = GET_OBJECT_TYPE(DialogContext);
const char* OT_CommonContext = GET_OBJECT_TYPE(CommonContext);
