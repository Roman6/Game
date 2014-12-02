#include "OptionLayer.h"

OptionLayer::OptionLayer(){

}

OptionLayer::~OptionLayer(){

}

bool OptionLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//实现对触摸事件的监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	
	listener->onTouchesBegan = CC_CALLBACK_2(OptionLayer::onTouchesBegan,this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void OptionLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event* event){
	this->delegator->onTouch();
}