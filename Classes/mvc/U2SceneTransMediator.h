//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2SceneTransMediator__
#define __U2SceneTransMediator__


#include "cocos2d.h"
#include "U2Object.h"
#include "U2Singleton.h"
#include "U2ViewComponent.h"
#include "U2TransStep.h"


U2EG_NAMESPACE_BEGIN



class SceneTrans : public ViewComponent::Listener
{
public:
    enum class TransType
    {
        TT_Overlay,
        TT_OneByOne,
        TT_Cross
    };

    /// <from name, trans type, to type>
    typedef std::tuple<u2::String, SceneTrans::TransType, u2::String>   TransData;

public:
    SceneTrans();
    virtual ~SceneTrans(void);

    void trans(ViewComponent* from, ViewComponent* to, TransType type);
    void _onUpdate(float dt);

protected:
    virtual void _registerFrameListener() = 0;
    virtual void _unregisterFrameListener() = 0;
    virtual void onViewCompStateChanged(ViewComponent* viewComp, ViewComponent::ViewCompState newState) override;

    VoidStep* _createVoidStep(const TransStep::Key& key, VoidStep::CallbackFun func = nullptr);
    ParamStep* _createParamStep(const TransStep::Key& key, ParamStep::CallbackFun func = nullptr);
    void _destroyTransStep(TransStep* step);
    void _onTransOver();
    void _onCrossToAttached();

protected:
    ViewComponent*      m_pFrom;
    ViewComponent*      m_pTo;
    void*               m_pParent;
    std::vector<TransStep*>      m_steps;
    TransStep::Key       m_curKey;
};


U2EG_NAMESPACE_END

#endif /* defined(__U2SceneTransMediator__) */
