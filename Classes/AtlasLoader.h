#pragma once

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

/**
 * @file         AtlasLoader.h    
 * @date         2014-3-29
 * @author       shun_fzll
 * @brief   	 ����atlas.txt�ļ�
 * 
 */

//atlas.txt��ʽ
//����       ��    ��   ��ʼ����                       ��������
//bg_day    288    512   0.0 0.0                        0.28125 0.5

typedef struct _atlas{
	char name [255];
	int width;
	int height;
	Point startPos;
	Point endPos;
	
}Atlas;

class AtlasLoader{
public:
	static AtlasLoader* getInstance();

	static void destroyInstance();

	void loadAtlas(string filename);
	
	void loadAtlas(string filename,Texture2D* texture);

	SpriteFrame* getSpriteFrameByName(string name);

protected:
	AtlasLoader();
	
	virtual bool init();

protected:
	static AtlasLoader* m_atlasLoader;
	
	Map<string,SpriteFrame*> m_spriteFrames;
};