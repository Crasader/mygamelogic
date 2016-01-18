//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#include "U2PredefinedPrerequisites.h"

#include "U2PredefinedFacade.h"
#include "U2PredefinedCommands.h"
#include "U2PredefinedMediators.h"
#include "U2PredefinedProxies.h"


// facade
const char* OT_PredefinedFacade = GET_OBJECT_TYPE(PredefinedFacade);

// proxy
const char* OT_ContextProxy = GET_OBJECT_TYPE(ContextProxy);

// command
const char* OT_DestroyContextCommand = GET_OBJECT_TYPE(DestoryContextCommand);
const char* OT_BackKeyCommand = GET_OBJECT_TYPE(BackKeyCommand);

// mediator
const char* OT_TransMediator = GET_OBJECT_TYPE(TransMediator);