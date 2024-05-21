#pragma once
#ifndef __GIFPLAYER_CLASS_H__
#define __GIFPLAYER_CLASS_H__

#include "axmol.h"
USING_NS_AX;

class GifPlayer {
public:
    //fym by inaccessible
    static Sprite* createWithScream(std::string name, float delay = 1 / 60, int repeat = -1);
    /// <summary>
    /// this is peak laziness
    /// </summary>
    static Sprite* createWithSpriteFrames(Vector<SpriteFrame*> frames, float delay = 1 / 60, int repeat = -1);
    // helper func but somehow it's defined in EndScreen???
    static std::string pad(std::string s, int n) {
        return std::string(n - std::min(n, static_cast<int>(s.length())), '0') + s;
    }
};
#endif
