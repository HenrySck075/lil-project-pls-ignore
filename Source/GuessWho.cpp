#include "GuessWho.h"
#include "AudioEngine.h"
#include "ui/UIVBox.h"
#include "ui/UILayoutParameter.h"
#include "ui/UIImageView.h"
#include "iostream"
#include "EndScreen.h"
#include "GifPlayer.h"
USING_NS_AX;


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GuessWho.cpp\n");
}

/// <summary>
///  my determination method might be sucks so
/// </summary>
/// <param name="menu">the menu itself</param>
/// <returns>the size</returns>
Size getPossibleMenuSize(Menu* menu) {
	float x = 0;
	float y = 0;
	for (auto* i : menu->getChildren()) {
		float w = i->getContentSize().width + i->getPositionX();
		float h = i->getContentSize().height + i->getPositionY();
		if (w > x) { x = w; }
		if (h > y) { h = y; }
	}
	return Size(x,y);
}

Size resizePreserve(Size dim, float width, float height) {
	if (width == -1) {
		width = (dim.width/ dim.height) * height;
	}
	if (height == -1) {
		height = (dim.height / dim.width) * width;
	}
	return Size(width, height);
}

// on "init" you need to initialize your instance
bool GuessWho::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Scene::init() )
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto l = GifPlayer::createWithScream("idk", 1 / 60);
	l->setPosition(visibleSize/2);
	//l->setAnchorPoint(Vec2(1, 0));
	this->addChild(l);

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//	you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	Vector<MenuItem*> yipee;
	float ld = 0;
	for (int i = 1; i<=10; i++) {
		// replace with a box
		auto sprite = Sprite::create("CloseNormal.png");

		//sprite->setSize(Size(150,150));
		auto s = resizePreserve(sprite->getContentSize(), -1, 70);
		sprite->setContentSize(s);
		//sprite->setLayoutParameter(lp1);
		auto j = MenuItemSprite::create(sprite, nullptr, AX_CALLBACK_1(GuessWho::optionCallback, this));
		j->setName("guess (" + std::to_string(i) + ")");
		j->setPosition(Vec2(ld, 0));
		ld += s.width+20;
		yipee.pushBack(j);
	}
	auto j = MenuItemSprite::create(Sprite::create("CloseNormal.png"), nullptr, AX_CALLBACK_1(GuessWho::jumpToCredits, this));
	j->setPosition(0, 200);
	yipee.pushBack(j);
	// create menu, it's an autorelease object
	auto menu = Menu::createWithArray(yipee);
	menu->setName("j");
	menu->setAnchorPoint(Vec2(0.5, 0));
	auto dim = Director::getInstance()->getVisibleSize();
	
	menu->setPosition(Vec2(dim.width/2-getPossibleMenuSize(menu).width/2, 80));
	this->addChild(menu, 1);


	// Loop audio
	
	AudioEngine::preload("abstract loop.mp3");
	
	this->loopId = AudioEngine::play2d("abstract static.mp3");
	AudioEngine::setFinishCallback(this->loopId, [&](int j, std::string_view fn) {
		this->loopId = AudioEngine::play2d("abstract loop.mp3", true);
	});
	return true;
}

void GuessWho::idk(Object* sender) {
	auto node = static_cast<MenuItemSprite*>(sender);
	node->runAction(Sequence::create(
		TintTo::create(0, 255.f, 255.f, 255.f),
		FadeOut::create(0.25),
		CallFunc::create([node]() {node->removeFromParent(); }),
		nullptr
	));
	this->tilesOpened++;
}
void GuessWho::resultImageCallback(Object* sender) {
	auto node = static_cast<MenuItemSprite*>(sender);
	if (this->tilesOpened < 9) {
		//auto j = this->getChildByName<Menu*>("silhouTilesMenu")->getChildren();
		//for (auto* h : j) {
		//	MenuItemSprite* i = static_cast<MenuItemSprite*>(h);
		//	i->activate();
		//}
	}
	else {
		auto m = static_cast<Menu*>(node->getParent());
		auto uwu = m->getChildByName("this fraud");
		this->runAction(Sequence::create(
			CallFunc::create([&]() {
				this->getChildByName<Menu*>("j")->runAction(EaseOut::create(MoveBy::create(0.5, Vec2(0, 160)), 2));
				}
			),
			DelayTime::create(0.5),
			CallFunc::create([m,uwu]() {
				uwu->runAction(
					Sequence::createWithTwoActions(
						Spawn::createWithTwoActions(
							TintTo::create(0, Color3B(255.f,255.f,255.f)), FadeOut::create(0.5)
						),
						CallFunc::create([m]() { m->removeFromParentAndCleanup(true); })
					)
				);
			}),
			nullptr
		));
		this->tilesOpened = 0;
		this->unlocked++;
		if (this->unlocked == 10){
            auto h    = Sprite::create("h.png");
            h->setPosition(Director::getInstance()->getVisibleSize()/2);
            //h->setOpacity(0);
            this->addChild(h,79);
            auto loop = this->loopId;
            this->runAction(Sequence::create(
                ActionFloat::create(5, 1, 0, [loop, this, h](float j) {
                    //std::cout << loop << " " << j << std::endl;
                    AudioEngine::setVolume(loop, j);
                    h->setOpacity(1-j);

                }),
                CallFunc::create([&]() {
                    AudioEngine::stopAll();
                    Director::getInstance()->pushScene(TransitionFade::create(0.25,utils::createInstance<EndScreen>()));
                }),
                nullptr
            ));
		}
	}
}

void GuessWho::displaySilhouette(Object* pSender) {
	auto j = static_cast<MenuItemSprite*>(pSender);
	auto normalSprite = Sprite::create(std::string(j->getName()) + ".jpg");
	auto silhou = Sprite::create(std::string(j->getName()) + " - Silhouette.jpg");
	auto k = silhou->getContentSize();
	auto size = resizePreserve(k,-1,400);
	silhou->setScale(size.width / k.width);
	float segWidth = k.width / 3;
	float segHeight = k.height / 3;

	
	auto menu = Menu::create();
	menu->setName("horny");
	auto menu2 = Menu::create();
	menu2->setName("silhouTilesMenu");
	for (int w = 0; w < 3; w++) {
		for (int h = 0; h < 3; h++) {
			Rect j = { segWidth * w, segHeight * h, segWidth, segHeight };
			auto s = Sprite::createWithTexture(silhou->getTexture(), j);
			s->setScale(size.width/3/segWidth);
			//s->setContentSize(size);
			auto d = MenuItemSprite::create(s, nullptr, AX_CALLBACK_1(GuessWho::idk, this));
			//d->setColor(Color3B(255.f, 0.f, 0.f));
			d->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			d->setContentSize(size/3);
			d->setPosition(size.width/3 * w, (size.height/3 * (2-h)));
			menu2->addChild(d,7);
		}
	}
	menu2->setPosition(Director::getInstance()->getVisibleSize() / 2 - (size / 3));
	menu->setPosition(Director::getInstance()->getVisibleSize() / 2);
	menu2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	menu->setContentSize(getPossibleMenuSize(menu));
	menu2->setContentSize(getPossibleMenuSize(menu2));
	this->addChild(menu);
	this->addChild(menu2);

	auto b = MenuItemSprite::create(normalSprite, nullptr, AX_CALLBACK_1(GuessWho::resultImageCallback, this));
	b->setName("this fraud");
	b->setContentSize(size);
	normalSprite->setContentSize(size);
	menu->addChild(b,-7);
}
void GuessWho::jumpToCredits(Object* pSender)
{
	AudioEngine::stopAll();
	Director::getInstance()->pushScene(utils::createInstance<EndScreen>());
}
void GuessWho::optionCallback(Object* pSender)
{
	//Close the menu
	this->getChildByName<Menu*>("j")->runAction(EaseIn::create(MoveBy::create(0.5, Vec2(0, -160)),2));
	this->displaySilhouette(pSender);


	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
