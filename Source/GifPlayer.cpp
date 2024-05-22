#include "AssetPath.h"
#include "GifPlayer.h"
#include <string>
#include "filesystem"
#include "iostream"

Sprite* GifPlayer::createWithSpriteFrames(Vector<SpriteFrame*> frames, float delay, int repeat) {
    auto spr  = Sprite::createWithTexture(frames.at(0)->getTexture());
	auto anim = Animate::create(Animation::createWithSpriteFrames(frames, 0.05f));
	if (repeat == -1) {
		spr->runAction(RepeatForever::create(anim));
	}
	else {
		spr->runAction(Repeat::create(anim, repeat));
	}
	return spr;
}

Sprite* GifPlayer::createWithScream(std::string name, float delay, int repeat) {
    Vector<SpriteFrame*> j;
    auto inst = FileUtils::getInstance();
    // ffmpeg starts with 1
    int dex = 1;
    while (true) {
        std::string assetPath   = kys::assetPath(name + "/frame" +GifPlayer::pad(std::to_string(dex),4)+ ".png");  // preferably
        //std::cout << assetPath;

        bool w = inst->isFileExist(assetPath);
        //std::cout << " (file reported its existence as " << w << ")" << std::endl;
        if (!w) break;
        auto ture = Sprite::create(assetPath);
        j.pushBack(SpriteFrame::createWithTexture(ture->getTexture(), ture->getTextureRect()));
        dex++;
    }

    return GifPlayer::createWithSpriteFrames(j, delay, repeat);

}
