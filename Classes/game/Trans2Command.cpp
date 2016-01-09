//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "Trans2Command.h"

#include "U2Context.h"
#include "U2Facade.h"



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
Trans2Command::Trans2Command(const String& type, const String& name)
    : SimpleCommand(type, name)
{
}
//-----------------------------------------------------------------------
Trans2Command::~Trans2Command()
{
}
//-----------------------------------------------------------------------
void Trans2Command::go(const Notification& notification)
{
    _createMediator(_retrieveFromContext(), _retrieveTransType(), _createToContext());
}
//-----------------------------------------------------------------------
void Trans2Command::_createMediator(const u2::Context* from, Mediator::TransType type, const u2::Context* to)
{
    Mediator* pMediator = MediatorManager::getSingleton().createObject(to->getMediatorClass(), to->getMediatorName());
    getFacade().registerMediator(pMediator);
    pMediator->startup(from, type, to);

    u2::Context::ConstContextListIterator it = to->getConstContextIterator();
    while (it.hasMoreElements())
    {
        _createMediator(to, Mediator::TransType::TT_Overlay, it.getNext());
    }
}