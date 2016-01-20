//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2PredefinedPrerequisites__
#define __U2PredefinedPrerequisites__


#include "U2Prerequisites.h"


U2EG_NAMESPACE_USING


extern const char* OT_Facade;
extern const char* OT_Model;
extern const char* OT_View;
extern const char* OT_Observer;
extern const char* OT_Controller;
extern const char* OT_Notification;
extern const char* OT_Context;

// facade
extern const char* OT_PredefinedFacade;

// proxy
extern const char* OT_ContextProxy;

// command
extern const char* OT_DestoryContextCommand;
extern const char* OT_BackKeyCommand;
extern const char* OT_TransCommand;

// mediator
extern const char* OT_TransMediator;

// view

// context queue
extern const char* OT_SingleContextQueue;
extern const char* OT_InfiniteContextQueue;


// notification
const String NTF_Predefined_DestroyContext = "NTF_Predefined_DestroyContext";
const String NTF_Predefined_BackKey = "NTF_Predefined_BackKey";
const String NTF_Predefined_Trans = "NTF_Predefined_Trans";

// facade name
const String ON_Facade_Predefined = "ON_Facade_Predefined";

// proxy name
const String ON_Proxy_Context = "ON_Proxy_Context";



#endif /* defined(__PredefinedPrerequisites__) */
