#pragma once
/**
 * @file         BackgroundLayer.h    
 * @date         2014-4-8
 * @author       shun_fzll
 * @brief   	 œ‘ æ”Œœ∑±≥æ∞
 * 
 */
#include "cocos2d.h"
#include "AtlasLoader.h"
#include "time.h"
using namespace cocos2d;

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	virtual bool init();
	static float getLandHeight();
protected:
private:
};