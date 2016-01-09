//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2InstanceManager__
#define __U2InstanceManager__


#include "cocos2d.h"
#include "IObserver.h"
#include "Controller.h"
#include "Model.h"
#include "View.h"
#include "Facade.h"


template<typename _Type, char const _Name[] = "PureMVC">
class MultiInstance
{
private:
    typedef std::map<std::string, _Type*> StringTypeMap;

    StringTypeMap*      m_pInstanceMap;
    std::mutex          m_mtx;

public:
    MultiInstance(void)
        : m_pInstanceMap(NULL)
        , _mutex(NULL)
    { }

    ~MultiInstance(void)
    {
        cleanCache();
    }

    void createCache(void)
    {
        if (m_pInstanceMap != NULL) return;

        std::lock_guard<std::mutex> lck(m_mtx);
        if (m_pInstanceMap != NULL) return;
        m_pInstanceMap = new StringTypeMap;
    }

    void insert(std::pair<std::string, _Type*> const& item)
    {
        createCache();

        std::lock_guard<std::mutex> lck(m_mtx);
        m_pInstanceMap->insert(item);
    }

    void insert(_Type* const& value)
    {
        createCache();
        char buff[20] = { 0 };
        sprintf(buff, "%lx", (unsigned long)value);
        std::pair<std::string, _Type*> item(buff, value);
        std::lock_guard<std::mutex> lck(m_mtx);
        m_pInstanceMap->insert(item);
    }

    void insert(std::string const& key, _Type* const& value)
    {
        createCache();
        std::pair<std::string, _Type*> item(key, value);
        std::lock_guard<std::mutex> lck(m_mtx);
        m_pInstanceMap->insert(item);
    }

    _Type* remove(std::string const& key)
    {
        _Type * result = NULL;
        if (m_pInstanceMap == NULL) return result;
        std::lock_guard<std::mutex> lck(m_mtx);
        if (m_pInstanceMap == NULL) return result;
        typename StringTypeMap::iterator iter = m_pInstanceMap->find(key);
        if (iter != m_pInstanceMap->end())
        {
            result = iter->second;
            m_pInstanceMap->erase(iter);
        }
        return result;
    }

    _Type* remove(_Type* const& value)
    {
        char buff[20] = { 0 };
        sprintf(buff, "%lx", (unsigned long)value);
        return remove(buff);
    }

    _Type* find(std::string const& key)
    {
        _Type * result = NULL;
        if (m_pInstanceMap == NULL) return result;
        std::lock_guard<std::mutex> lck(m_mtx);
        if (m_pInstanceMap == NULL) return result;
        typename StringTypeMap::const_iterator iter = m_pInstanceMap->find(key);
        if (iter != m_pInstanceMap->end())
            result = iter->second;
        return result;
    }

    _Type* find(_Type* const& value) const
    {
        char buff[20] = { 0 };
        sprintf(buff, "%lx", (unsigned long)value);
        return find(buff);
    }

    void cleanCache(void)
    {
        if (m_pInstanceMap == NULL) return;
        std::lock_guard<std::mutex> lck(m_mtx);
        if (m_pInstanceMap == NULL) return;

        StringTypeMap * instance = m_pInstanceMap;
        m_pInstanceMap = NULL;
        typename StringTypeMap::iterator result = instance->begin();
        for (; result != instance->end(); ++result)
            delete result->second;
        instance->clear();
        delete instance;
    }

};



extern char const __OBSERVER_NAME__[];
typedef MultiInstance<IObserver, __OBSERVER_NAME__> InstanceMapObserver;
extern InstanceMapObserver puremvc_observer_instance_map;

extern char const __CONTROLLER_NAME__[];
typedef MultiInstance<Controller, __CONTROLLER_NAME__> InstanceMapController;
extern InstanceMapController puremvc_controller_instance_map;

extern char const __MODEL_NAME__[];
typedef MultiInstance<Model, __MODEL_NAME__> InstanceMapModel;
extern InstanceMapModel puremvc_model_instance_map;

extern char const __VIEW_NAME__[];
typedef MultiInstance<View, __VIEW_NAME__> InstanceMapView;
extern InstanceMapView puremvc_view_instance_map;

extern char const __FACADE_NAME__[];
typedef MultiInstance<Facade, __FACADE_NAME__> InstanceMapFacade;
extern InstanceMapFacade puremvc_facade_instance_map;



#endif /* defined(__U2InstanceManager__) */
