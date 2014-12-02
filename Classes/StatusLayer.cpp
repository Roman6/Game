#include "StatusLayer.h"

StatusLayer::StatusLayer(){}

StatusLayer::~StatusLayer(){}

bool StatusLayer::init(){
	if(!Layer::init()){
		return false;
	}
	
	this->bestScore = 0;
	this->currentScore = 0;
	this->isNewRecord = false;
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->originPoint = Director::getInstance()->getVisibleOrigin();
	
	//������Դ ����1 number_score 0-9
	Number::getInstance()->loadNumber(Number_Score.c_str(), "number_score_%02d");
	//������Դ ����2 font_  ������Ϸ�����з�����ʾ
	Number::getInstance()->loadNumber(Number_Font.c_str(),"font_0%02d",48);

	//׼��״̬
	this->showReadyStatus();

	this->loadWhiteSprite();

	return true;
}

void StatusLayer::loadWhiteSprite(){
	//this white sprite is used for blinking the screen for a short while
	whiteSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("white"));
	whiteSprite->setScale(100);
	//��͸���� 1��͸�� 0��ȫ͸��
	whiteSprite->setOpacity(0);
	this->addChild(whiteSprite,10000);
}

void StatusLayer::showReadyStatus(){
	//��Ϸ��������ʾ�ķ�����
	scoreSprite = (Sprite*)Number::getInstance()->convert(Number_Font.c_str(),0);
	scoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width/2, this->originPoint.y + this->visibleSize.height * 5/6));
	this->addChild(scoreSprite);

	//Get Ready ����
	getreadySprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_ready"));
	getreadySprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height *2/3));
	this->addChild(getreadySprite);

	//����˵��ͼƬ
	tutorialSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("tutorial"));
	tutorialSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height * 1/2));
	this->addChild(tutorialSprite);
}

void StatusLayer::showStartStatus(){
	//����
	this->tutorialSprite->runAction( FadeOut::create(0.4f));
	this->getreadySprite->runAction( FadeOut::create(0.4f));
}

void StatusLayer::showOverStatus(int curScore, int bestScore){
	this->currentScore = curScore;
	this->bestScore = bestScore;
	if(curScore > bestScore){
		this->bestScore = curScore;
		this->isNewRecord = true;
	}else{
		this->isNewRecord = false;
	}
	this->removeChild(scoreSprite);

	this->blinkFullScreen();
}

void StatusLayer::onGameOver(int curScore, int bestScore){
	this->showOverStatus(curScore,bestScore);
}

void StatusLayer::onGamePlaying(int score){
	//���µ÷�
	this->removeChild(scoreSprite);
	this->scoreSprite = (Sprite*)Number::getInstance()->convert(Number_Font.c_str(),score);
	scoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2,this->originPoint.y + this->visibleSize.height *5/6));
	this->addChild(scoreSprite);

}

void StatusLayer::onGameStart(){
	this->showStartStatus();
}

void StatusLayer::blinkFullScreen(){
	//�׹�һ��
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	auto blinkAction = Sequence::create(fadeIn,fadeOut,NULL);
	CallFunc* actionDone = CallFunc::create(CC_CALLBACK_0(StatusLayer::fadeInGameOver,this));
	auto sequence = Sequence::createWithTwoActions(blinkAction,actionDone);
	whiteSprite->stopAllActions();
	whiteSprite->runAction(sequence);
}


void StatusLayer::fadeInGameOver(){   //game voer panel
	//game over ����
	Sprite* gameOverSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameOverSprite->setPosition(Point(originPoint.x + visibleSize.width/2, originPoint.y + visibleSize.height * 2/3));
	this->addChild(gameOverSprite);
	auto gameOverFadeIn = FadeIn::create(0.5f);

	//�ص�
	CallFunc* actionDone = CallFunc::create(CC_CALLBACK_0(StatusLayer::jumpToScorePanel,this));
	auto sequence = Sequence::createWithTwoActions(gameOverFadeIn,actionDone);
	gameOverSprite->stopAllActions();
	gameOverSprite->runAction(sequence);

}

void StatusLayer::jumpToScorePanel(){
	//score_panel
	auto scorePanelSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	scorePanelSprite->setPosition(Point(originPoint.x + visibleSize.width/2, originPoint.y - scorePanelSprite->getContentSize().height));
	this->addChild(scorePanelSprite);

	//best_Score
	auto bestScoreSprite = (Sprite *)Number::getInstance()->convert(Number_Score.c_str(), this->bestScore, Gravity::GRAVITY_RIGHT);
	bestScoreSprite->setAnchorPoint(Point(1, 1));
	bestScoreSprite->setPosition(scorePanelSprite->getContentSize().width - 28 ,
		50);
	scorePanelSprite->addChild(bestScoreSprite);

	//model
	string medalsName = this->getModalsName(currentScore);
	if(medalsName != ""){
		Sprite* medalsSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(medalsName));
		medalsSprite->addChild(this->blink);
		medalsSprite->setPosition(54,58);
		scorePanelSprite->addChild(medalsSprite);
	}

	//new �¼�¼
	if(this->isNewRecord){
		Sprite* newTagSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("new"));
		newTagSprite->setPosition(-16, 12);
		bestScoreSprite->addChild(newTagSprite);
	}

	//start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f,Point(originPoint.x + visibleSize.width/2, originPoint.y + visibleSize.height/2 -10.0f));
	//��ӱ����˶�
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	//�ص�
	CallFunc* actionDone = CallFunc::create(CC_CALLBACK_0(StatusLayer::fadeInRestartBtn,this));

	auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
	scorePanelSprite->stopAllActions();
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	scorePanelSprite->runAction(sequence);

}

string StatusLayer::getModalsName(int score){
	//blinkһ��һ������
	this->setBlinkSprite();

	string medalsName = "";
	if(this->currentScore >=0 && this->currentScore < 20){//iron medals ��
		medalsName = "medals_0";
	}else if(this->currentScore >= 20 && currentScore < 30){//bronze medals ͭ
		medalsName = "medals_1";
	}else if(currentScore >=30 && currentScore < 50){//silver medals ��
		medalsName = "medals_2";
	}else if(currentScore >=50){//golden medals ��
		medalsName = "medals_3";
	}
	return medalsName;
	
}
void StatusLayer::setBlinkSprite(){
	//һ��һ��������
	this->blink = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("blink_00"));
	
	//animation
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for(int i = 0; i <3; i++){
		const char* filename = String::createWithFormat("blink_%02d",i)->getCString();
		SpriteFrame* frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	for (int i = 2; i >= 0; i--){
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	auto animate = Animate::create(animation);
	
	//�ص�
	CallFunc* actionDone = CallFunc::create(CC_CALLBACK_0(StatusLayer::blinkAction,this));

	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
	blink->runAction(RepeatForever::create(sequence));

}

void StatusLayer::blinkAction(){
	//��һ��λ��
	if(this->blink && this->blink->getParent()) {
		Size activeSize = this->blink->getParent()->getContentSize();
		this->blink->setPosition(rand()%((int)(activeSize.width)), rand()%((int)(activeSize.height)));
	}
}

void StatusLayer::fadeInRestartBtn(){
	Node* tempNode = Node::create();

	//create the restart menu
	Sprite* restartBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* restartBtnActive = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	restartBtnActive->setPositionY(-4);

	auto menuItem = MenuItemSprite::create(restartBtn,restartBtnActive,NULL,CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));
	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2 - restartBtn->getContentSize().width / 2, this->originPoint.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tempNode->addChild(menu);

	//rate btn
	Sprite* rateBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_score"));
	rateBtn->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2 + rateBtn->getContentSize().width / 2, this->originPoint.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tempNode->addChild(rateBtn);

	this->addChild(tempNode);

	//fade in two button
	auto fadeIn = FadeIn::create(0.1f);
	CallFunc *actionDone = CallFunc::create(CC_CALLBACK_0(StatusLayer::refreshScoreCallback,this));
	auto sequence = Sequence::createWithTwoActions(fadeIn,actionDone);
	tempNode->stopAllActions();
	tempNode->runAction(sequence);
}

void StatusLayer::refreshScoreCallback(){ //ˢ�µ÷�sprite 0-curScore
	this->tmpScore = 0;
	this->schedule(schedule_selector(StatusLayer::refreshScoreExecutor),0.1f);
}
void StatusLayer::refreshScoreExecutor(float dt){
	if(this->getChildByTag(Current_Score_Sprite_Tag)){
		this->removeChildByTag(Current_Score_Sprite_Tag);
	}
	scoreSprite = (Sprite *)Number::getInstance()->convert(Number_Score.c_str(), this->tmpScore, Gravity::GRAVITY_RIGHT);
	scoreSprite->setAnchorPoint(Point(1,0));
	scoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width * 3 / 4 + 20.0f, this->originPoint.y + this->visibleSize.height *  1 / 2));
	scoreSprite->setTag(Current_Score_Sprite_Tag);
	this->addChild(scoreSprite,1000);
	this->tmpScore++;
	if(this->tmpScore > this->currentScore){
		this->unschedule(schedule_selector(StatusLayer::refreshScoreExecutor));
	}
}

void StatusLayer::menuRestartCallback(Object* pSender){
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}





