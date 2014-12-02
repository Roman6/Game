#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init(){
	if(!Scene::initWithPhysics()){//启用物理引擎
		return false;
	}
	this->getPhysicsWorld()->setGravity(Vect(0,-900));

	//添加背景层
	auto backgroundLayer = BackgroundLayer::create();
	if(backgroundLayer){
		this->addChild(backgroundLayer);
	}
	//添加状态层
	auto statusLayer = StatusLayer::create();
	
	//添加游戏层
	auto gameLayer = GameLayer::create();
	if(gameLayer){
		gameLayer->setPhyWorld(this->getPhysicsWorld());
		gameLayer->setDelegator(statusLayer);
		this->addChild(gameLayer);
	}
	//在gamelayer之后添加statusLayer，即gamelayer元素在statusLayer元素下
	if(statusLayer){
		this->addChild(statusLayer);
	}
	//添加操作层
	auto optionLayer = OptionLayer::create();
	if(optionLayer){
		optionLayer->setDelegator(gameLayer);
		this->addChild(optionLayer);
	}

	return true;
}

void GameScene::restart(){
	this->removeAllChildrenWithCleanup(true);
	this->init();
}

void GameScene::onExit(){
	this->removeAllChildrenWithCleanup(true);
	CCLOG("gamescene onexit");
}