#pragma once

#ifndef __ENDSCREEN__SCENE_H__
#define __ENDSCREEN__SCENE_H__

#include "axmol.h"

class EndScreen : public axmol::Scene
{
public:
    //static axmol::Scene* createScene();

    virtual bool init();

    void update(float idk) override;

};

#endif // __ENDSCREEN__SCENE_H__
