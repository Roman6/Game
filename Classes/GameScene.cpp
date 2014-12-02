#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init(){
	if(!Scene::initWithPhysics()){//������������
		return false;
	}
	this->getPhysicsWorld()->setGravity(Vect(0,-900));

	//��ӱ�����
	auto backgroundLayer = BackgroundLayer::create();
	if(backgroundLayer){
		this->addChild(backgroundLayer);
	}
	//���״̬��
	auto statusLayer = StatusLayer::create();
	
	//�����Ϸ��
	auto gameLayer = GameLayer::create();
	if(gameLayer){
		gameLayer->setPhyWorld(this->getPhysicsWorld());
		gameLayer->setDelegator(statusLayer);
		this->addChild(gameLayer);
	}
	//��gamelayer֮�����statusLayer����gamelayerԪ����statusLayerԪ����
	if(statusLayer){
		this->addChild(statusLayer);
	}
	//��Ӳ�����
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