#include "EndScreen.h"
#include "AudioEngine.h"
#include "iostream"
USING_NS_AX;

Size resizePreserve2(Size dim, float width, float height) {
	if (width == -1) {
		width = (dim.width / dim.height) * height;
	}
	if (height == -1) {
		height = (dim.height / dim.width) * width;
	}
	return Size(width, height);
}
bool EndScreen::init() {
    if (!Scene::init())
    {
        return false;
    }
	auto ds = Director::getInstance()->getVisibleSize();
	
	auto endCredits = Sprite::create("endCredits.png");
	//endCredits->setName("h");
    //endCredits->setScale(20);
    endCredits->setAnchorPoint(Vec2(0,1));
	endCredits->setContentSize(resizePreserve2(endCredits->getContentSize(),ds.width,-1));
    endCredits->setPosition(Vec2(0,0));
	this->addChild(endCredits);
	float h = ds.height;
	auto seq = Sequence::create(
		DelayTime::create(0.25), // transition
	    CallFunc::create([](){AudioEngine::play2d("wade ld short.mp3");}),
		EaseSineOut::create(MoveBy::create(4, Vec2(0, h))),
		DelayTime::create(3),

		MoveBy::create(126, Vec2(0, endCredits->getContentSize().height - h)),
		DelayTime::create(4.29),
		FadeOut::create(0),

		DelayTime::create(5),
		CallFunc::create([]() {Director::getInstance()->end(); }),
		nullptr // what
	);
	std::cout<<ds.width<<std::endl;
	auto j = endCredits->getContentSize();
    std::cout << j.x << " " << j.y;
	endCredits->runAction(seq);
	//this->scheduleUpdate();
	return true;
}

void EndScreen::update(float idk) {
	auto j = this->getChildByName("h")->getPosition();
	std::cout << j.width << " " << j.height << std::endl;

}
