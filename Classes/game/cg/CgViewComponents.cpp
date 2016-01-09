//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "CgViewComponents.h"


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
const String CgViewComponent::AN_CgAction = "CgAction";
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
CgViewComponent::CgViewComponent(const String& type, const String& name)
    : CocosViewComponent(type, name)
{
}
//-----------------------------------------------------------------------
CgViewComponent::~CgViewComponent(void)
{

}
//-----------------------------------------------------------------------
const String& CgViewComponent::getUiName() const
{
    static String name = "Layer_littlestar_movie.csb";
    return name;
}
//-----------------------------------------------------------------------
void CgViewComponent::runCgAction()
{
    cocostudio::timeline::ActionTimeline* pTimeline = _runTimeline(getUiName(), AN_CgAction);
    pTimeline->gotoFrameAndPlay(0, false);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
const String StartPageViewComponent::AN_StartAction = "StartAction";
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
StartPageViewComponent::StartPageViewComponent(const String& type, const String& name)
    : CocosViewComponent(type, name)
{
}
//-----------------------------------------------------------------------
StartPageViewComponent::~StartPageViewComponent(void)
{

}
//-----------------------------------------------------------------------
const String& StartPageViewComponent::getUiName() const
{
    static String name = "Layer_littlestar_movieclick.csb";
    return name;
}
//-----------------------------------------------------------------------
void StartPageViewComponent::runStartAction()
{
    cocostudio::timeline::ActionTimeline* pTimeline = _runTimeline(getUiName(), AN_StartAction);
    pTimeline->gotoFrameAndPlay(0, false);
}