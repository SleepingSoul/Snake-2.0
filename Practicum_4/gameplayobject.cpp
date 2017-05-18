#include "gameplayobject.h"
#include "wall.h"
#include "snake.h"
#include "field.h"
#include "apple.h"
#include "wormhole.h"
#include <cassert>

GameplayObject *GameplayObject::createObject( OBJECT_ID id, GameWidget *gw )
{
    GameplayObject *object;
    switch ( id ) {
    case WALL:
        object = new Wall( gw );
        break;
    case FIELD:
        object = new Field( gw );
        break;
    case SNAKE:
        object = new Snake( gw );
        break;
    case APPLE:
        object = new Apple( gw );
        break;
    case WORMHOLE:
        object = new Wormhole( gw );
        break;
    default:
        assert( false );
    }
    return object;
}
