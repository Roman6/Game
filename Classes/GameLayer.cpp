#include "GameLayer.h"


GameLayer::GameLayer(){}

GameLayer::~GameLayer(){
	
	
}

bool GameLayer::init(){

	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	this->m_gameStatus = GAME_STATUS_READY;
	this->m_score = 0;

	//添加小鸟
	this->m_bird = BirdSprite::getInstance();
	this->m_bird->createBird();

	PhysicsBody* body = PhysicsBody::create();
	body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(false);

	body->setCategoryBitmask(1);    // 0001
	body->setContactTestBitmask(-1); // 0100
	body->setCollisionBitmask(-1);   // 0011

	this->m_bird->setPhysicsBody(body);
	this->m_bird->setPosition(origin.x + visibleSize.width*1/3, origin.y + visibleSize.height/2 + 5);
	this->m_bird->idle();
	this->addChild(this->m_bird);

	//添加ground
	this->m_groundNode = Node::create();
	
	auto groundBody = PhysicsBody::create();
	float landHeight = BackgroundLayer::getLandHeight();
	groundBody->addShape(PhysicsShapeBox::create(Size(288,landHeight)));
	groundBody->setDynamic(false);
	groundBody->setLinearDamping(0.0f);
	groundBody->setCategoryBitmask(0x01);    // 0001
	groundBody->setContactTestBitmask(-1); // 0100
	groundBody->setCollisionBitmask(-1);   // 0011
	
	this->m_groundNode->setPhysicsBody(groundBody);
	this->m_groundNode->setPosition(144,landHeight/2);
	this->addChild(m_groundNode);

	//添加land
	this->m_land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->m_land1->setAnchorPoint(Point::ZERO);
	this->m_land1->setPosition(Point::ZERO);
	this->addChild(this->m_land1, 30);

	this->m_land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->m_land2->setAnchorPoint(Point::ZERO);
	this->m_land2->setPosition(this->m_land1->getContentSize().width-2.0f,0);
	this->addChild(this->m_land2, 30);

	//定时器selector,用于滚动land
	shiftLand = schedule_selector(GameLayer::scrollLand);
	this->schedule(shiftLand,0.01f);

	this->scheduleUpdate();

	//物理碰撞 监听
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin,this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);


	return true;
}

bool GameLayer::onContactBegin(PhysicsContact& contact) {
	this->gameOver();
	return true;
}

void GameLayer::scrollLand(float dt){

	//land
	this->m_land1->setPositionX(this->m_land1->getPositionX() - 2.0f);
	this->m_land2->setPositionX(this->m_land1->getPositionX() + this->m_land1->getContentSize().width -2.0f);
	if(this->m_land2->getPositionX() <= 0){
		this->m_land1->setPositionX(0);
	}

	//move the pips
	for(auto pip: pips){
		pip->setPositionX(pip->getPositionX() - 2.0f);
		if(pip->getPositionX() + PIP_WIDTH  <= 0){
			pip->setTag(PIP_NEW);
			pip->setPositionX(Director::getInstance()->getVisibleSize().width + PIP_WIDTH/2);
			pip->setPositionY(this->getRandomHeight());
		}
	}
}
void GameLayer::onTouch(){

	if(this->m_gameStatus == GAME_STATUS_OVER){
		return ;
	}
	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if(this->m_gameStatus == GAME_STATUS_READY){
		this->delegator->onGameStart();
		this->m_bird->fly();
		this->m_bird->getPhysicsBody()->setVelocity(Vect(0,260));
		this->m_gameStatus = GAME_STATUS_START;
		this->createPips();
	}else if(this->m_gameStatus == GAME_STATUS_START){
		this->m_bird->getPhysicsBody()->setVelocity(Vect(0,260));
	}
}

void GameLayer::rotateBird(){
	float verticalSpeed = this->m_bird->getPhysicsBody()->getVelocity().y;
	//setRotation(angle) 其中angle为角度不是弧度。正数为顺时针旋转，负数为逆时针旋转。
	this->m_bird->setRotation((-1)*min(max(-90, (verticalSpeed*0.2 + 60)), 30));
}

void GameLayer::update(float delta){
	if(this->m_gameStatus == GAME_STATUS_START){
		this->rotateBird();
		this->checkHit();
		
	}
}

void GameLayer::createPips(){
	//实际只有创建两根水管
	for(int i = 0; i < PIP_COUNT; i++){
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Sprite *pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		Sprite *pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
		Node *singlePip = Node::create();

		//bind to singlePip
		pipDown->setPosition(0,PIP_HEIGHT + PIP_DISTANCE);
		singlePip->addChild(pipDown, 0, DOWN_PIP);
		singlePip->addChild(pipUp, 0, UP_PIP);
		singlePip->setPosition(visibleSize.width + i * PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());

		auto body = PhysicsBody::create();
		auto shapeDown = PhysicsShapeBox::create(pipDown->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT,Point(0,PIP_HEIGHT + PIP_DISTANCE));
		body->addShape(shapeDown);
		auto shapeUp = PhysicsShapeBox::create(pipUp->getContentSize());
		body->addShape(shapeUp);
		body->setCategoryBitmask(0x01);    // 0001
		body->setContactTestBitmask(-1); // 0100
		body->setCollisionBitmask(-1);   // 0011
		body->setDynamic(false);

		singlePip->setPhysicsBody(body);
		singlePip->setTag(PIP_NEW);

		this->addChild(singlePip);
		this->pips.pushBack(singlePip);

	}
}

int GameLayer::getRandomHeight(){
	//0到(740-512)
	return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - Director::getInstance()->getVisibleSize().height);
}

void GameLayer::checkHit(){
	for(auto pip : pips){
		if(pip->getTag() == PIP_NEW){
			if(pip->getPositionX() < this->m_bird->getPositionX()){ //飞过一根水管
				SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
				this->m_score++;
				this->delegator->onGamePlaying(this->m_score);
				pip->setTag(PIP_PASS);
			}
		}
	}
}

void GameLayer::gameOver(){
	if(this->m_gameStatus == GAME_STATUS_OVER){
		return ;
	}
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
	//保存数据
	int bestScore = UserRecord::getInstance()->readIntegerFromUserDefault("best_score");
	if(this->m_score > bestScore){
		UserRecord::getInstance()->saveIntegerToUserDefault("best_score",this->m_score);
	}
	//控制显示gameOver
	this->delegator->onGameOver(this->m_score,bestScore);
	this->unschedule(shiftLand);

	SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
	this->m_bird->die();
	this->m_bird->setRotation(-90);
	//?
	this->birdSpriteFadeOut();
	this->m_gameStatus = GAME_STATUS_OVER;
}

void GameLayer::birdSpriteFadeOut(){
	//FadeOut* animation = FadeOut::create(1.5f);
	//创建回调函数
//	CallFunc* animationDone = CallFunc::create(bind(&GameLayer::birdSpriteRemove,this));
	CallFunc* animationDone = CallFunc::create(CC_CALLBACK_0(GameLayer::birdSpriteRemove,this));
	Sequence* sequence = Sequence::createWithTwoActions(FadeOut::create(1.5f),animationDone);
	this->m_bird->stopAllActions();
	this->m_bird->runAction(sequence);
	
	
}

void GameLayer::birdSpriteRemove(){
	this->m_bird->setRotation(0);
	//this->removeChild(this->m_bird);
	//CC_SAFE_DELETE(this->m_bird);
	//this->m_bird->destroyInstance();
	//this->removeAllChildrenWithCleanup(true);
}