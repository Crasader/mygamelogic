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
#include "U2ContextProxy.h"

const char* OT_ApplicationFacade = GET_OBJECT_TYPE(ApplicationFacade);
const char* OT_ContextProxy = GET_OBJECT_TYPE(ContextProxy);
const char* OT_StartupCommand = GET_OBJECT_TYPE(StartupCommand);
const char* OT_DestroyContextCommand = GET_OBJECT_TYPE(DestroyContextCommand);
const char* OT_Trans2LogoCommand = GET_OBJECT_TYPE(Trans2LogoCommand);
const char* OT_SceneTransCommand = GET_OBJECT_TYPE(SceneTransCommand);
const char* OT_ShadeMediator = GET_OBJECT_TYPE(ShadeMediator);
const char* OT_ShadeViewComponent = GET_OBJECT_TYPE(ShadeViewComponent);
const char* OT_LogoMediator = GET_OBJECT_TYPE(LogoMediator);
const char* OT_LogoViewComponent = GET_OBJECT_TYPE(LogoViewComponent);