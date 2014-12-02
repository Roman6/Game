#include "WelcomeScene.h"
#include "WelcomeLayer.h"

WelcomeScene::WelcomeScene(){

}

WelcomeScene::~WelcomeScene(){

	}

bool WelcomeScene::init(){
	bool bRet=false;
	do {
		CC_BREAK_IF(!Scene::init());
		auto welcomeLayer = WelcomeLayer::create();
		CC_BREAK_IF(!welcomeLayer);
		this->addChild(welcomeLayer);
		bRet = true;
	} while (0);
	return true;
}

