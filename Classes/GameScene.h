#pragma once
/**
 * @file         GameScene.h    
 * @date         2014-4-6
 * @author       shun_fzll
 * @brief   	 ÓÎÏ·Ö÷³¡¾°
 * 
 */
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "OptionLayer.h"
#include "StatusLayer.h"

USING_NS_CC;

class GameScene : public Scene{
public:
	GameScene();
	~GameScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	
	void restart();
	
	virtual void onExit() override;
	
};