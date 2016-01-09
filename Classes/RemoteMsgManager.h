//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __Piano__CRemoteMsgManager__
#define __Piano__CRemoteMsgManager__


#include "../../common/Singleton.h"
#include "cocos2d.h"
#include "RemoteMsg.h"

/** 改成非单例类，放到每个Manager里吧。
*/
class CRemoteMsgManager : public CSingleton<CRemoteMsgManager>
{
public:
    friend class CSingleton<CRemoteMsgManager>;
    
    virtual ~CRemoteMsgManager();

    void pushRequest(Command* pMsg);
    const Command* getFrontRequest(Command::eCmdType type);
    const Command* getFrontRequest();
    void popRequest(Command::eCmdType type);
    void popRequest();
    size_t getRequestCount(Command::eCmdType type);
    size_t getRequestCount();
    void clearRequest();

    void pushResponse(Command* pMsg);
    const Command* getFrontResponse(Command::eCmdType type);
    const Command* getFrontResponse();
    void popResponse(Command::eCmdType type);
    void popResponse();
    size_t getResponseCount(Command::eCmdType type);
    size_t getResponseCount();
    void clearResponse();

    void clear();
    
protected:
    CRemoteMsgManager();
    
protected:
    typedef std::list<Command*>                                 RemoteMsgQueue;
    typedef std::map<Command::eCmdType, RemoteMsgQueue>   RemoteMsgQueueMap;
    typedef std::map<uint64_t, Command*>                        RemoteMsgMap;

    RemoteMsgMap                                m_allResps;
    RemoteMsgQueueMap                           m_typedResps;
    std::mutex                                  m_mtxResp;

    RemoteMsgMap                                m_allReqs;
    RemoteMsgQueueMap                           m_typedReqs;
    std::mutex                                  m_mtxReq;
};


#define RemoteMsgManager()  CRemoteMsgManager::GetInstance()

#endif /* defined(__Piano__CRemoteMsgManager__) */
