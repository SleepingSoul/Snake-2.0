#ifndef GAMEPLAYOBJECT_H
#define GAMEPLAYOBJECT_H

#include "gamewidget.h"

enum OBJECT_ID{ WALL = 0, FIELD, SNAKE, APPLE, WORMHOLE };

class GameplayObject {
public:
    virtual void paintGameplayObject() = 0;
    static GameplayObject *createObject( OBJECT_ID, GameWidget * );
};

#endif // GAMEPLAYOBJECT_H
