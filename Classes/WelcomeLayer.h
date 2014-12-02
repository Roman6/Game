#pragma once

/**
 * @file         WelcomeLayer.h    
 * @date         2014-3-30
 * @author       shun_fzll
 * @brief   	 背景 地面 游戏名 版权描述 开始游戏的按钮 小鸟
 * 
 */

#include "cocos2d.h"
#include "BirdSprite.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "AtlasLoader.h"
#include "time.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

const int START_BUTTON_TAG = 100;

class WelcomeLayer : public  Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);

private:
	/** The start button has been pressed will call this function  */
	void menuStartCallBack(Object* pSender);
	/** This method is make the land have a scroll animation  */
	void scrollLand(float dt);

private:
	Sprite* m_land1;
	Sprite* m_land2;
	BirdSprite* m_bird;
};