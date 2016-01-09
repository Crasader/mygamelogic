//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "CgMediators.h"

#include "U2ViewComponent.h"
#include "U2Facade.h"
#include "U2Context.h"
#include "CgViewComponents.h"
#include "../application/ApplicationPrerequisites.h"



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
CgMediator::CgMediator(const String& type, const String& name)
    : CocosMediator(type, name)
{
}
//-----------------------------------------------------------------------
CgMediator::~CgMediator(void)
{

}
//-----------------------------------------------------------------------
Mediator::NotificationNames CgMediator::listNotificationInterests(void) const
{
    std::list<std::string> ntfs;
    ntfs.push_back(NTF_Cg_SceneTrans_2_Cg);
    
    return ntfs;
}
//-----------------------------------------------------------------------
void CgMediator::handleNotification(const Notification& notification)
{
    const u2::String& szNtfName = notification.getName();
    const void* pData = notification.getData();

}
//-----------------------------------------------------------------------
void CgMediator::onCommonStateChanged(ViewComponent* viewComp, const String& objName, const String& msg)
{
    if (objName == CgViewComponent::AN_CgAction)
    {
        if (msg == "ActionEnd")
        {
            // trans
            u2::Context* pFrom = ContextManager::getSingleton().retrieveObject("CgContext");
            u2::Context* pTo = ContextManager::getSingleton().createObject(OT_Context, "StartPageContext", OT_StartPageMediator, "StartPageMediator", OT_StartPageViewComponent, "StartPageViewComponent");
            Mediator::TransData data = std::make_tuple(pFrom, Mediator::TransType::TT_OneByOne, pTo);
            Notification ntf(NTF_Application_SceneTrans, &data);
            getFacade().broadcastNotification(ntf);
        }
    }
}
//-----------------------------------------------------------------------
void CgMediator::_onTransOver()
{
    CgViewComponent* pCgViewComponent = dynamic_cast<CgViewComponent*>(m_pViewComp);
    if (pCgViewComponent == nullptr)
    {
        return;
    }

    pCgViewComponent->runCgAction();
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
StartPageMediator::StartPageMediator(const String& type, const String& name)
    : CocosMediator(type, name)
{
}
//-----------------------------------------------------------------------
StartPageMediator::~StartPageMediator(void)
{

}
//-----------------------------------------------------------------------
Mediator::NotificationNames StartPageMediator::listNotificationInterests(void) const
{
    std::list<std::string> ntfs;

    return ntfs;
}
//-----------------------------------------------------------------------
void StartPageMediator::handleNotification(const Notification& notification)
{
    const u2::String& szNtfName = notification.getName();
    const void* pData = notification.getData();

}
//-----------------------------------------------------------------------
void StartPageMediator::_onTransOver()
{
    StartPageViewComponent* pStartPageViewComponent = dynamic_cast<StartPageViewComponent*>(m_pViewComp);
    if (pStartPageViewComponent == nullptr)
    {
        return;
    }

//     cocos2d::ui::Button* pStartButton = dynamic_cast<cocos2d::ui::Button*>(pStartPageViewComponent->seekNodeByName(""));
//     if (pStartButton != nullptr)
//     {
//         pStartButton->addClickEventListener();
//     }
}