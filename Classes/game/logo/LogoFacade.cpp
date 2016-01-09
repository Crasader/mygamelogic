//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "LogoFacade.h"


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
LogoFacade::LogoFacade(const String& type, const String& name)
    : Facade(type, name)
{
}
//-----------------------------------------------------------------------
LogoFacade& LogoFacade::getInstance(void)
{
    Facade* pFacade = FacadeManager::getSingleton().retrieveObject("LogoFacade");
    if (pFacade == nullptr)
    {
        pFacade = FacadeManager::getSingleton().createObject(ObjectTypeLogoFacade, "LogoFacade");
    }
    return *(dynamic_cast<LogoFacade*>(pFacade));
}
//-----------------------------------------------------------------------
LogoFacade::~LogoFacade(void)
{
}
//-----------------------------------------------------------------------
void LogoFacade::initializeController(void)
{
    Facade::initializeController();
    //registerCommand();
}
//-----------------------------------------------------------------------
void LogoFacade::startup()
{
    sendNotification(Ntf_Logo_Startup);
    removeCommand(Ntf_Logo_Startup); //PureMVC初始化完成，注销STARUP命令
}