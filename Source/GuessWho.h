/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.axmol-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

//#include <string_view>
#include "axmol.h"
//#include "base/Vector.h"

class GuessWho: public axmol::Scene
{
public:
    virtual bool init();
    int tilesOpened = 0;
    int unlocked = 0;
    //int unlocked = 9;
    int loopId = 0;

    //ax::Vector<std::string_view> unlockedBoxes;

    // a selector callback
    void optionCallback(axmol::Object* pSender);
    void idk(axmol::Object* pSender);
    void resultImageCallback(axmol::Object* pSender);

    void jumpToCredits(axmol::Object* pSender);

    void displaySilhouette(axmol::Object* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
