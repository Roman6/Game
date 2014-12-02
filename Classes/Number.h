#pragma once

#include "cocos2d.h"
#include "AtlasLoader.h"

using namespace std;
using namespace cocos2d;


typedef enum _gravity
{
	GRAVITY_CENTER = 1,
	GRAVITY_LEFT,
	GRAVITY_RIGHT
}Gravity;

const int Number_Interval = 2;

class NumberSeries :public Object{

public :
	NumberSeries();
	~NumberSeries();
	virtual bool init();
	CREATE_FUNC(NumberSeries);
	/** º”‘ÿnumber  */
	void loadNumber(const char* fmt, int base = 0);
	/** ∑µªÿnumber  */
	SpriteFrame* at(int index);
private:
	Vector<SpriteFrame*> numberSeries;
};


class Number{
public:
	Number();
	~Number();
	virtual bool init();
	static Number* getInstance();
	static void destroyInstance();
	//
	virtual bool loadNumber(const char* name, const char* fmt, int base = 0);
	//
	Node* convert(const char* name, int number, Gravity gravity = GRAVITY_CENTER);
private:
	Map<string,NumberSeries*> numberContainer;
	static Number* sharedNumber;
};




