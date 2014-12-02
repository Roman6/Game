#pragma once

#include "cocos2d.h"
#include "AtlasLoader.h"
USING_NS_CC;

typedef enum{
	ACTION_STATE_IDLE,	//�Ӷ�����������ڣ���������Լ��
	ACTION_STATE_FLY,	//���еĹ��̵��У���������Ӱ��
	ACTION_STATE_DIE	//���ص�״̬
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
	/** ����С��Ķ���  */
	static Animation* createAnimation(const char* fmt,int count ,float fps);
	/**  ÿ����Ϸ���ѡ��һֱ��ɫ��С�� */
	void createBirdByRandom();
	/** �ı䵱ǰ״̬  */
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