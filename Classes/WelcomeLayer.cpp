#include "WelcomeLayer.h"

WelcomeLayer::WelcomeLayer(){}

WelcomeLayer::~WelcomeLayer(){}

bool WelcomeLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//CCLog("WelcomeLayer::ContentSize()->:%d,%d",this->getContentSize().width ,this->getContentSize().height);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//获取当前时间
	time_t t = time(NULL);
	tm* tm = localtime(&t);
	int hour = tm->tm_hour;

	//添加背景图片
	Sprite* backGround;
	if(hour >= 6 && hour <= 17){
		backGround = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
	}else{
		backGround = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));
	}
	backGround->setAnchorPoint(Point::ZERO);
	backGround->setPosition(Point::ZERO);
	this->addChild(backGround);

	//添加标题
	Sprite* title = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
	title->setPosition(Point(visibleSize.width/2, (visibleSize.height * 5)/7));
	this->addChild(title);

	//添加开始按钮
	Sprite* startButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
//	activeStartButton->setPositionY(5);
	auto menuItem = MenuItemSprite::create(startButton,activeStartButton,NULL,CC_CALLBACK_1(WelcomeLayer::menuStartCallBack,this));
	menuItem->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 2/5));

	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(origin.x,origin.y));
	this->addChild(menu);

	//添加flappy bird
	this->m_bird = BirdSprite::getInstance();
	this->m_bird->createBird();
	this->m_bird->setTag(BIRD_SPRITE_TAG);
	this->m_bird->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 3/5 -10));
	this->m_bird->idle();	//挥动翅膀并上下扑腾
	this->addChild(m_bird);

	//添加land
	this->m_land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	m_land1->setAnchorPoint(Point::ZERO);
	m_land1->setPosition(Point::ZERO);
	this->addChild(m_land1);

	this->m_land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	m_land2->setAnchorPoint(Point::ZERO);
	m_land2->setPosition(Point(this->m_land1->getContentSize().width - 2.0f, 0));
	this->addChild(m_land2);

	//设置land滚动
	this->schedule(schedule_selector(WelcomeLayer::scrollLand),0.01f);

	//添加copyright
	Sprite* copyRight = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
	copyRight->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/6));
	this->addChild(copyRight, 10);

 	return true;

}

void WelcomeLayer::scrollLand(float dt){
	this->m_land1->setPositionX(this->m_land1->getPositionX() - 2.0f);
	this->m_land2->setPositionX(this->m_land1->getPositionX() + this->m_land1->getContentSize().width -2.0f);
	if(this->m_land2->getPositionX() <= 0){
		this->m_land1->setPositionX(0);
	}
}

void WelcomeLayer::menuStartCallBack(Object* pSender){
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene); 
	Director::getInstance()->replaceScene(transition);
}