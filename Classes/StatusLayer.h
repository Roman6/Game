#pragma once

#include "cocos2d.h"
#include "GameLayer.h"
#include "Number.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

using namespace std;
using namespace CocosDenshion;
using namespace cocos2d;

const string Number_Score = "number_score";
const string Number_Font = "font";
const int Current_Score_Sprite_Tag = 10001;

class StatusLayer : public Layer, public StatusDelegate
{
public:
	StatusLayer();
	~StatusLayer();
	CREATE_FUNC(StatusLayer);

public:
	virtual bool init();
	//When the game start, this method will be called
	void onGameStart(void) ;
	//During paying, after the score changed, this method will be called
	void onGamePlaying(int score);
	//When game is over ,this method will be called
	void onGameOver(int curScore, int bestScore);
private:
	void showReadyStatus();

	void showStartStatus();

	void showOverStatus(int curScore, int bestScore);

	void loadWhiteSprite();

	void blinkFullScreen();

	void fadeInGameOver();

	void jumpToScorePanel();

	void fadeInRestartBtn();

	void refreshScoreCallback();

	void refreshScoreExecutor(float dt);

	string getModalsName(int score);

	Sprite* blink;

	void setBlinkSprite();

	void blinkAction();

	void menuRestartCallback(Object* pSender);

	Sprite* scoreSprite;

	Sprite* getreadySprite;

	Sprite* tutorialSprite;

	Sprite* whiteSprite;

	int currentScore;

	int bestScore;

	int tmpScore;

	bool isNewRecord;

	Point originPoint;

	Size visibleSize;

};