#pragma once

/**
 * @file         OptionLayer.h    
 * @date         2014-4-6
 * @author       shun_fzll
 * @brief   	 控制层。该层主要是响应玩家的OnTouch事件，以实现游戏当中控制小鸟飞行轨迹的目的。
 * 
 */
#include "cocos2d.h"
using namespace cocos2d;

class OptionDelegate{ //在GameLayer 和 OptionLayer 之间，通过OptionDelegate这座桥梁实现了两者的分离和通信
public :
	virtual void onTouch() = 0;
};

class OptionLayer : public Layer
{
public:
	OptionLayer();
	~OptionLayer();
	CREATE_FUNC(OptionLayer);
	virtual bool init();

	//触摸事件
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
	//OpitonDelegate属性的set和get方法
	CC_SYNTHESIZE(OptionDelegate* ,delegator ,Delegator);

};