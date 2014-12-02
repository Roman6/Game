#include "AtlasLoader.h"


AtlasLoader* AtlasLoader::m_atlasLoader=nullptr;

AtlasLoader::AtlasLoader(){

}

bool AtlasLoader::init(){
	return true;
}

AtlasLoader* AtlasLoader::getInstance(){
	if(m_atlasLoader == NULL){
		m_atlasLoader = new AtlasLoader();
		if(!m_atlasLoader->init()){
			delete m_atlasLoader;
			m_atlasLoader= NULL;
			CCLOG("Error: could not init AtlasLoader");
		}
	}
	return m_atlasLoader;
}

void AtlasLoader::destroyInstance(){
	CC_SAFE_DELETE(m_atlasLoader);
}

void AtlasLoader::loadAtlas(string filename){
	auto textureAltas = Director::getInstance()->getTextureCache()->addImage("atlas.png");
	this->loadAtlas(filename,textureAltas);
}

void AtlasLoader::loadAtlas(string filename,Texture2D* texture){
	Atlas atlas;
	string data = FileUtils::getInstance()->getStringFromFile(filename);
	unsigned int pos = data.find_first_of("\n");
	string line = data.substr(0,pos);
	data = data.substr(pos + 1);
	while (line != ""){
		sscanf(line.c_str(),
			"%s %d %d %f %f %f %f %f",
			&atlas.name,&atlas.width,&atlas.height,&atlas.
			startPos.x,&atlas.startPos.y,&atlas.endPos.x,&atlas.endPos.y);
		atlas.startPos.x *= 1024;
		atlas.startPos.y *= 1024;
		atlas.endPos.x *= 1024;
		atlas.endPos.y *= 1024;

		pos = data.find_first_of("\n");
		line = data.substr(0,pos);
		data = data.substr(pos+1);

		//使用data创建sprite frame
		if(atlas.name == string("land")){
			atlas.startPos.x += 1;
		}
		Rect rect = Rect(atlas.startPos.x,atlas.startPos.y,atlas.width,atlas.height);
		auto spriteFrame = SpriteFrame::createWithTexture(texture,rect);
		this->m_spriteFrames.insert(string(atlas.name),spriteFrame);	
	}
}

SpriteFrame* AtlasLoader::getSpriteFrameByName(string name){
	return this->m_spriteFrames.at(name);
}
