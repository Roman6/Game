#pragma once
/**
 * @file         WelcomeScene.h    
 * @date         2014-3-30
 * @author       shun_fzll
 * @brief   	 ╪сть WelcomeLayer
 * 
 */
#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public Scene{
public:
	WelcomeScene(); 
	~WelcomeScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
};