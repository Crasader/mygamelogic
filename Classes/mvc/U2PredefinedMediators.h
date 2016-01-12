//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2PredefinedMediators__
#define __U2PredefinedMediators__


#include "cocos2d.h"
#include "U2Prerequisites.h"
#include "U2Mediator.h"


U2EG_NAMESPACE_USING


class TransMediator : public Mediator
{
public:
    enum class TransType
    {
        TT_Overlay,
        TT_OneByOne,
        TT_Cross
    };

    /// <from name, trans type, to type>
    typedef std::tuple<u2::Context*, TransMediator::TransType, u2::Context*>   TransData;

public:
    TransMediator(const String& type, const String& name);

    virtual ~TransMediator(void);

    virtual void startup(const u2::Context* from, TransMediator::TransType type, const u2::Context* to);

	virtual void end() override;

    virtual void onUpdate(float dt);

private:
    /// don't call this method in TransMediator
    virtual void startup(const u2::Context* context) override;

protected:
    virtual void onViewCompStateChanged(ViewComponent* viewComp, ViewComponent::ViewCompState newState) override;

    void _trans(ViewComponent* from, TransType type, ViewComponent* to);
    void _onCrossToAttached();
    void _onOneByOneFromExited();
    void _onTransOver();

    void _destroyTransMediator();
    void _destroyFromContext();
    void _startupToContext(u2::Context* context);

    TransStep* _createVoidStep(const TransStep::Key& key, VoidStep::CallbackFun func = nullptr);
    TransStep* _createParamStep(const TransStep::Key& key, ParamStep::CallbackFun func = nullptr);
    void _destroyTransStep(TransStep* step);

protected:
    ViewComponent*      m_pFrom;
    ViewComponent*      m_pTo;
    u2::Context*        m_pFromContext;
    u2::Context*        m_pToContext;
    TransType           m_transType;
    void*               m_pParent;
    std::vector<TransStep*>      m_steps;
    TransStep::Key      m_curKey;
};


#endif /* defined(__U2PredefinedMediators__) */
