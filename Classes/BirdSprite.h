#pragma once

#include "cocos2d.h"
#include "AtlasLoader.h"
USING_NS_CC;

typedef enum{
	ACTION_STATE_IDLE,	//挥动翅膀，上下扑腾，不受重力约束
	ACTION_STATE_FLY,	//飞行的过程当中，受重力的影响
	ACTION_STATE_DIE	//倒地的状态
}ActionState;

const int BIRD_SPRITE_TAG = 10003;

class BirdSprite : public Sprite
{
public:
	BirdSprite();
	~BirdSprite();
	static BirdSprite* getInstance();
	virtual bool init();
	bool createBird();
	void idle();
	void fly();
	void die();
	void destroyInstance();
protected:
	/** 创建小鸟的动画  */
	static Animation* createAnimation(const char* fmt,int count ,float fps);
	/**  每场游戏随机选择一直颜色的小鸟 */
	void createBirdByRandom();
	/** 改变当前状态  */
	bool changeState(ActionState state);
private:
	static BirdSprite* m_birdSprite;
	Action* idleAction;
	Action* swingAction;
	ActionState curState;
	string birdName;
	string birdNameFormat;
	unsigned int isFirstTime;
};