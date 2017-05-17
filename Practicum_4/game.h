#ifndef GAME_H
#define GAME_H

#include "gamewidget.h"

class Game {
public:
    static Game &Instance()
    {
        static Game instance;
        return instance;
    }
    int run( int, char *[] );
private:
    Game();
    Game( const Game & ) = delete;
    Game &operator =( const Game & ) = delete;
    GameWidget *g_wgt;
};

#endif // GAME_H
