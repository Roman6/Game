#pragma once

/**
 * @file         OptionLayer.h    
 * @date         2014-4-6
 * @author       shun_fzll
 * @brief   	 ���Ʋ㡣�ò���Ҫ����Ӧ��ҵ�OnTouch�¼�����ʵ����Ϸ���п���С����й켣��Ŀ�ġ�
 * 
 */
#include "cocos2d.h"
using namespace cocos2d;

class OptionDelegate{ //��GameLayer �� OptionLayer ֮�䣬ͨ��OptionDelegate��������ʵ�������ߵķ����ͨ��
public :
	virtual void onTouch() = 0;
};

class OptionLayer : public Layer
{
public:
	OptionLayer();
	~OptionLayer();
	CREATE_FUNC(OptionLayer);
	virtual bool init();

	//�����¼�
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
	//OpitonDelegate���Ե�set��get����
	CC_SYNTHESIZE(OptionDelegate* ,delegator ,Delegator);

};