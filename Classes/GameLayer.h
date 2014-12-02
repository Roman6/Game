#pragma once
/**
 * @file         GameLayer.h    
 * @date         2014-4-6
 * @author       shun_fzll
 * @brief   	 Ԫ�أ�1��С�� 2.ˮ��
 *				 ������1����Ϸ״̬�ı�ʾ   2�����С���ˮ��  3��������ʵʱͳ��  4����ײ�ļ��
 * 
 */
#include "cocos2d.h"
#include "BirdSprite.h"
#include "OptionLayer.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "UserRecord.h"

using namespace cocos2d;
using namespace CocosDenshion;

typedef enum game_status{
	GAME_STATUS_READY = 1,	//��Ϸ׼��״̬
	GAME_STATUS_START,		//��Ϸ��ʼ
	GAME_STATUS_OVER		//��Ϸ����
}GameStatus;

#define min(X,Y) ((X) < (Y) ? (X) : (Y)) 
#define max(X,Y) ((X) > (Y) ? (X) : (Y)) 

const int UP_PIP = 21;  // pip 's tag

const int DOWN_PIP = 12;

const int PIP_PASS = 30;

const int PIP_NEW = 31;

/**
 * The radius of the bird
 */
const int BIRD_RADIUS = 15;

/**
 * The height of the pips
 */
const int PIP_HEIGHT = 320;

/**
 * The width of the pips
 */
const int PIP_WIDTH = 52;

/**
 * Pip shift speed
 */
const float PIP_SHIFT_SPEED = 80.0f;

/**
 * The distance between the down pip and up pip
 */
const int PIP_DISTANCE = 100;

/**
 * The distance between the pips vertical
 */
const int PIP_INTERVAL = 180;

/**
 * The number of pip pairs display in the screen in the same time
 */
const int PIP_COUNT = 2;

/**
 * The distance that the pip will display in the screen, for player to ready
 */
const int WAIT_DISTANCE = 100;

class StatusDelegate{
public:
	//When the game start, this method will be called
	virtual void onGameStart(void) = 0;
	//During paying, after the score changed, this method will be called
	virtual void onGamePlaying(int score) = 0;
	//When game is over ,this method will be called
	virtual void onGameOver(int curScore, int bestScore) = 0;
};


class GameLayer : public Layer ,public OptionDelegate
{
public:
	GameLayer();
	~GameLayer();
	CREATE_FUNC(GameLayer);
	virtual bool init();

	//��Ϸ״̬StatusDelegate��set��get����
	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	void onTouch();

	void setPhyWorld(PhysicsWorld* world){this->m_world = world;}

	void update(float delta);

private:
	//��תС��ʹ�俴������ͷ������
	void rotateBird();
	//����ˮ��
	void createPips();
	 
	int getRandomHeight();
	//����
	void checkHit();
	/**
	 * Since the only global bird can not be addChilded to two layers
	 * we must delete it from one layer,and then add it to another layer
	 * Here we use the fadeout animation to delete it from the gamelayer, so when the player 
	 * press the restart button, the bird can be added successfully
	 */
	void birdSpriteFadeOut();
	/*
	 * After running the fadeout animation, delete the bird from current layer
	 */
	void birdSpriteRemove();
private:
	PhysicsWorld* m_world;

	GameStatus m_gameStatus;
	
	int m_score;
	
	BirdSprite *m_bird;
	
	Node* m_groundNode;

	Vector<Node*>pips;

	Sprite* m_land1;
	Sprite* m_land2;

	SEL_SCHEDULE shiftLand; //λ�ƶ�ʱ��

	

private:
	void scrollLand(float dt);
	bool onContactBegin( PhysicsContact& contact);//��ײ��ʼ
	void gameOver();
};