//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "InstanceManager.h"



char const __OBSERVER_NAME__[] = "Observer";
InstanceMapObserver puremvc_observer_instance_map;

char const __CONTROLLER_NAME__[] = "Controller";
InstanceMapController puremvc_controller_instance_map;

char const __MODEL_NAME__[] = "Model";
InstanceMapModel puremvc_model_instance_map;

char const __VIEW_NAME__[] = "View";
InstanceMapView puremvc_view_instance_map;

char const __FACADE_NAME__[] = "Facade";
InstanceMapFacade puremvc_facade_instance_map;