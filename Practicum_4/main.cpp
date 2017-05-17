#include "game.h"

int main( int argc, char *argv[] )
{
    return Game::Instance().run( argc, argv );
}
