#include "EndScreen.h"
#include "AudioEngine.h"
#include "iostream"
#include "AssetPath.h"
#include "ui/UIMediaPlayer.h"
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

	auto endCredits = Sprite::create(kys::assetPath("endCredits.png"));
	//endCredits->setName("h");
    //endCredits->setScale(20);
    endCredits->setAnchorPoint(Vec2(0,1));
	endCredits->setContentSize(resizePreserve2(endCredits->getContentSize(),ds.width,-1));
    endCredits->setPosition(Vec2(0,0));
	this->addChild(endCredits);
	float h = ds.height;
    auto m = ui::MediaPlayer::create();
    m->addEventListener([](Object* j, ui::MediaPlayer::EventType type) {
        if (type == ui::MediaPlayer::EventType::COMPLETED)
        {
            Director::getInstance()->end(); 
        }
    });
    this->addChild(m,7);
    m->setContentSize(ds);
    m->setFileName(kys::assetPath("honorable mention.mp4"));
    m->setPosition(ds/2);
	auto seq = Sequence::create(
		DelayTime::create(0.25), // transition
	    CallFunc::create([](){AudioEngine::play2d(kys::assetPath("wade ld short.mp3"));}),
		EaseSineOut::create(MoveBy::create(4, Vec2(0, h))),
		DelayTime::create(3),

		MoveBy::create(49.316, Vec2(0, endCredits->getContentSize().height - h)),
		DelayTime::create(6.29),
		FadeOut::create(0),

		DelayTime::create(3),
		CallFunc::create([m]() {
            //m->setFullScreenEnabled(true);
            m->play();
        }),
		nullptr // what
	);
	std::cout<<ds.width<<std::endl;
	endCredits->runAction(seq);
	//this->scheduleUpdate();
	return true;
}

void EndScreen::update(float idk) {
	auto j = this->getChildByName("h")->getPosition();
	std::cout << j.width << " " << j.height << std::endl;

}
