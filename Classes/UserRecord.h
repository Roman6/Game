#pragma once
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class UserRecord : public Object
{
public:
	UserRecord();
	~UserRecord();

	static UserRecord* getInstance();

	static void destroyInstance();

	virtual bool init();

	void saveIntegerToUserDefault(const char* key, int score);

	int readIntegerFromUserDefault(const char* key);

private:
	static UserRecord* shareUserRecord;
};
