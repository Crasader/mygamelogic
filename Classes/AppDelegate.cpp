#include "AppDelegate.h"


#include "application/ApplicationFacade.h"
#include "cg/CgFacade.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("My Game", Rect(0, 0, 640, 1136), 0.5f);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);


    FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getWritablePath());
    cocos2d::FileUtils::getInstance()->addSearchPath("res");
    cocos2d::FileUtils::getInstance()->addSearchPath("res/ui/plist");
    cocos2d::FileUtils::getInstance()->addSearchPath("res/ui/application");
    cocos2d::FileUtils::getInstance()->addSearchPath("res/ui/cg");

    m_pFrameListenerCollection = new CocosFrameListenerCollection;

    PredefinedFacade::getSingleton();
    CgFacade::getSingleton();
	ApplicationFacade::getSingleton().startup();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
