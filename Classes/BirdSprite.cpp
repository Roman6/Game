#include "BirdSprite.h"

BirdSprite::BirdSprite(){}

BirdSprite::~BirdSprite(){}

BirdSprite* BirdSprite::m_birdSprite = nullptr;

BirdSprite* BirdSprite::getInstance(){
// 	if(m_birdSprite == NULL){
// 		m_birdSprite = new BirdSprite();
// 		if(!m_birdSprite->init()){
// 			CC_SAFE_DELETE(m_birdSprite);
// 			CCLOG("ERROR: Could not init m_birdSprite");
// 		}
// 	}

	m_birdSprite = new BirdSprite();
	if(m_birdSprite->init()){
		m_birdSprite->autorelease();
		return m_birdSprite;
	}
//	m_birdSprite = new BirdSprite();
	return NULL;;
}

bool BirdSprite::init(){
	this->isFirstTime = 3;
	return true;
}

bool BirdSprite::createBird(){
	bool bRet = false;
	//随机颜色创建小鸟
	this->createBirdByRandom();
	if(Sprite::initWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(this->birdName))){
		//创建小鸟挥动翅膀的动画
		Animation* animation = this->createAnimation(this->birdNameFormat.c_str(),3,10);
		Animate* animate = Animate::create(animation);
		this->idleAction = RepeatForever::create(animate);
		//创建小鸟上下飞的动画
		ActionInterval* up = CCMoveBy::create(0.5f,Point(0,10));
		ActionInterval *upBack = up->reverse();
		this->swingAction = RepeatForever::create(Sequence::create(up,upBack,NULL));
		bRet = true;
	}
	return bRet;
}

void BirdSprite::idle(){
	if(changeState(ACTION_STATE_IDLE)){
		this->runAction(idleAction);
		this->runAction(swingAction);
	}
}
void BirdSprite::fly(){
	if(changeState(ACTION_STATE_FLY)){
		this->stopAction(swingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

void BirdSprite::die(){
	if(changeState((ACTION_STATE_DIE))){
		this->stopAllActions();
	}
}
Animation* BirdSprite::createAnimation(const char* fmt,int count ,float fps){//创建小鸟挥动翅膀的动画
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(1/fps);
	for(int i = 0; i < count; i++){
		const char* filename = String::createWithFormat(fmt,i)->getCString();
		SpriteFrame* frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

bool BirdSprite::changeState(ActionState state){
	this->curState = state;
	return true;
}

void BirdSprite::createBirdByRandom(){
	if(this->isFirstTime & 1){
		this->isFirstTime &= 2;
	}else if(this->isFirstTime & 2){
		this->isFirstTime &= 1;
		return ;
	}
	srand(unsigned(time(NULL)));
	int type = ((int)rand())%3;
	switch (type)
	{
	case 0:
		this->birdName = "bird0_0";
		this->birdNameFormat = "bird0_%d";
		break;
	case 1:
		this->birdName = "bird1_0";
		this->birdNameFormat = "bird1_%d";
		break;
	case 2:
		this->birdName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	default:
		this->birdName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	}
	
}
void BirdSprite::destroyInstance(){
	if(this->m_birdSprite != NULL){
		delete m_birdSprite;
		m_birdSprite = NULL;
	}
}





