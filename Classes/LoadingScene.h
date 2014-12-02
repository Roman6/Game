#pragma once
#ifndef __LOADINGSCENC__
#define __LOADINGSCENC__
/**
 * @file         LodingScene.h    
 * @date         2014-3-30
 * @author       shun_fzll
 * @brief   	 显示splash.png  异步加载图片资源和声音资源 进入wel界面
 * 
 */

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "WelcomeScene.h"
#include "BackgroundLayer.h"



class LoadingScene : public cocos2d::Scene
{
public :
	virtual bool init();
	
	CREATE_FUNC(LoadingScene);
	void onEnter() override;
private:
	void loadingCallBack(Texture2D* texture);
};

#endif // __HELLOWORLD_SCENE_H__