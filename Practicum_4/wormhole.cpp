#include "wormhole.h"
#include <ctime>
#include <cstdlib>

Wormhole::Wormhole( GameWidget *gw ) : gw( gw )
{
    srand( ::time( 0 ) + 1 );
    int x = rand() % 32;
    int y = rand() % 22;
    coords = QPoint( x * 30 + 32, y * 30 + 74 );
}

Wormhole::~Wormhole()
{

}

void Wormhole::paintGameplayObject()
{
    gw->painter->begin( gw );
    gw->painter->setBrush( QBrush( Qt::black ) );
    gw->painter->drawEllipse( coords.x(), coords.y(), 40, 40 );
    gw->painter->end();
}

QPoint Wormhole::getCoords() const
{
    return coords;
}
