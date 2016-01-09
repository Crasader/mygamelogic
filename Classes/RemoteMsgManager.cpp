//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "RemoteMsgManager.h"

#include "Command.h"


CRemoteMsgManager::CRemoteMsgManager()
{
}

CRemoteMsgManager::~CRemoteMsgManager()
{
}

void CRemoteMsgManager::pushRequest(Command* pMsg)
{
    std::lock_guard<std::mutex> lck(m_mtxReq);

    // 加入全队列
    pMsg->retain();
    m_allReqs.insert(make_pair(pMsg->getGuid(), pMsg));

    // 加入分类队列
    RemoteMsgQueueMap::iterator itr = m_typedReqs.find(pMsg->getType());
    if (itr == m_typedReqs.end())
    {
        RemoteMsgQueue queue;
        queue.push_back(pMsg);
        m_typedReqs.insert(make_pair(pMsg->getType(), queue));
    }
    else
    {
        RemoteMsgQueue& queue = itr->second;
        queue.push_back(pMsg);
    }
}

void CRemoteMsgManager::popRequest(Command::eCmdType type)
{
    std::lock_guard<std::mutex> lck(m_mtxReq);

    RemoteMsgQueueMap::iterator itr = m_typedReqs.find(type);
    if (itr != m_typedReqs.end())
    {
        // 从分类队列中删除
        RemoteMsgQueue& queue = itr->second;
        if (!queue.empty())
        {
            Command* pMsg = queue.front();
            queue.pop_front();

            // 从全队列中删除
            RemoteMsgMap::iterator itrInAll = m_allReqs.find(pMsg->getGuid());
            if (itrInAll != m_allReqs.end())
            {
                m_allReqs.erase(pMsg->getGuid());
                pMsg->release();
            }
        }
    }
}

void CRemoteMsgManager::popRequest()
{
    std::lock_guard<std::mutex> lck(m_mtxReq);

    Command* pMsg = nullptr;

    RemoteMsgMap::iterator itrFirst = m_allReqs.begin();
    if (itrFirst != m_allReqs.end())
    {
        pMsg = itrFirst->second;

        // 从分类队列中删除
        if (pMsg != nullptr)
        {
            RemoteMsgQueueMap::iterator itr = m_typedReqs.find(pMsg->getType());
            if (itr != m_typedReqs.end())
            {
                RemoteMsgQueue& queue = itr->second;
                for (RemoteMsgQueue::iterator itr = queue.begin(); itr != queue.end(); itr++)
                {
                    if (pMsg == *itr)
                    {
                        queue.erase(itr);
                        break;
                    }
                }
            }
        }

        // 从全队列中删除
        m_allReqs.erase(pMsg->getGuid());
        pMsg->release();
    }
}

const Command* CRemoteMsgManager::getFrontRequest(Command::eCmdType type)
{
    std::lock_guard<std::mutex> lck(m_mtxReq);

    RemoteMsgQueueMap::iterator itr = m_typedReqs.find(type);
    if (itr == m_typedReqs.end())
    {
        return nullptr;
    }
    else
    {
        RemoteMsgQueue& queue = itr->second;
        if (queue.empty())
        {
            return nullptr;
        }
        else
        {
            Command* pMsg = queue.front();
            return pMsg;
        }
    }
}

const Command* CRemoteMsgManager::getFrontRequest()
{
    std::lock_guard<std::mutex> lck(m_mtxReq);

    Command* pMsg = nullptr;

    RemoteMsgMap::iterator itrFirst = m_allReqs.begin();
    if (itrFirst != m_allReqs.end())
    {
        pMsg = itrFirst->second;
    }

    return pMsg;
}

size_t CRemoteMsgManager::getRequestCount(Command::eCmdType type)
{
    std::lock_guard<std::mutex> lck(m_mtxReq);

    RemoteMsgQueueMap::iterator itr = m_typedReqs.find(type);
    if (itr == m_typedReqs.end())
    {
        return 0;
    }
    else
    {
        RemoteMsgQueue& queue = itr->second;
        return queue.size();
    }
}

size_t CRemoteMsgManager::getRequestCount()
{
    std::lock_guard<std::mutex> lck(m_mtxReq);

    return m_allReqs.size();
}

void CRemoteMsgManager::clearRequest()
{
    std::lock_guard<std::mutex> lck(m_mtxReq);

    Command* pMsg = nullptr;

    // 清空全队列
    for (RemoteMsgMap::iterator itr = m_allReqs.begin();
        itr != m_allReqs.end();
        ++itr)
    {
        pMsg = itr->second;
        m_allReqs.erase(pMsg->getGuid());
        pMsg->release();
    }

    // 清空分类队列
    m_typedReqs.clear();
}

void CRemoteMsgManager::pushResponse(Command* pMsg)
{
    std::lock_guard<std::mutex> lck(m_mtxResp);

    // 加入全队列
    pMsg->retain();
    m_allResps.insert(make_pair(pMsg->getGuid(), pMsg));

    // 加入分类队列
    RemoteMsgQueueMap::iterator itr = m_typedResps.find(pMsg->getType());
    if (itr == m_typedResps.end())
    {
        RemoteMsgQueue queue;
        queue.push_back(pMsg);
        m_typedResps.insert(make_pair(pMsg->getType(), queue));
    }
    else
    {
        RemoteMsgQueue& queue = itr->second;
        queue.push_back(pMsg);
    }
}

void CRemoteMsgManager::popResponse(Command::eCmdType type)
{
    std::lock_guard<std::mutex> lck(m_mtxResp);

    RemoteMsgQueueMap::iterator itr = m_typedResps.find(type);
    if (itr != m_typedResps.end())
    {
        // 从分类队列中删除
        RemoteMsgQueue& queue = itr->second;
        if (!queue.empty())
        {
            Command* pMsg = queue.front();
            queue.pop_front();

            // 从全队列中删除
            RemoteMsgMap::iterator itrInAll = m_allResps.find(pMsg->getGuid());
            if (itrInAll != m_allResps.end())
            {
                m_allResps.erase(pMsg->getGuid());
                pMsg->release();
            }
        }
    }
}

void CRemoteMsgManager::popResponse()
{
    std::lock_guard<std::mutex> lck(m_mtxResp);

    Command* pMsg = nullptr;

    RemoteMsgMap::iterator itrFitst = m_allResps.begin();
    if (itrFitst != m_allResps.end())
    {
        pMsg = itrFitst->second;

        // 从分类队列中删除
        if (pMsg != nullptr)
        {
            RemoteMsgQueueMap::iterator itr = m_typedResps.find(pMsg->getType());
            if (itr != m_typedResps.end())
            {
                RemoteMsgQueue& queue = itr->second;
                for (RemoteMsgQueue::iterator itr = queue.begin(); itr != queue.end(); itr++)
                {
                    if (pMsg == *itr)
                    {
                        queue.erase(itr);
                        break;
                    }
                }
            }
        }

        // 从全队列中删除
        m_allResps.erase(pMsg->getGuid());
        pMsg->release();
    }
}

const Command* CRemoteMsgManager::getFrontResponse(Command::eCmdType type)
{
    std::lock_guard<std::mutex> lck(m_mtxResp);

    RemoteMsgQueueMap::iterator itr = m_typedResps.find(type);
    if (itr == m_typedResps.end())
    {
        return nullptr;
    }
    else
    {
        RemoteMsgQueue& queue = itr->second;
        if (queue.empty())
        {
            return nullptr;
        }
        else
        {
            Command* pMsg = queue.front();
            return pMsg;
        }
    }
}

const Command* CRemoteMsgManager::getFrontResponse()
{
    std::lock_guard<std::mutex> lck(m_mtxResp);

    Command* pMsg = nullptr;

    RemoteMsgMap::iterator itrFirst = m_allResps.begin();
    if (itrFirst != m_allResps.end())
    {
        pMsg = itrFirst->second;
    }

    return pMsg;
}

size_t CRemoteMsgManager::getResponseCount(Command::eCmdType type)
{
    std::lock_guard<std::mutex> lck(m_mtxResp);

    RemoteMsgQueueMap::iterator itr = m_typedResps.find(type);
    if (itr == m_typedResps.end())
    {
        return 0;
    }
    else
    {
        RemoteMsgQueue& queue = itr->second;
        return queue.size();
    }
}

size_t CRemoteMsgManager::getResponseCount()
{
    std::lock_guard<std::mutex> lck(m_mtxResp);

    return m_allResps.size();
}

void CRemoteMsgManager::clearResponse()
{
    std::lock_guard<std::mutex> lck(m_mtxResp);

    Command* pMsg = nullptr;

    // 清空全队列
    for (RemoteMsgMap::iterator itr = m_allResps.begin();
        itr != m_allResps.end(); 
        ++itr)
    {
        pMsg = itr->second;
        m_allResps.erase(pMsg->getGuid());
        pMsg->release();
    }

    // 清空分类队列
    m_typedResps.clear();
}

void CRemoteMsgManager::clear()
{
    clearRequest();
    clearResponse();
}