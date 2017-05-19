#include "wormhole.h"
#include <ctime>
#include <cstdlib>

Wormhole::Wormhole( GameWidget *gw ) : gw( gw ), colorOffset( 0 )
{
    srand( ::time( 0 ) + 1 );
    int x = rand() % 32;
    int y = rand() % 22;
    coords = QPoint( x * 30 + 32, y * 30 + 74 );
    wormholeImage.load( ":/images/Images/wormhole.png" );
}

Wormhole::~Wormhole()
{

}

void Wormhole::paintGameplayObject()
{
    gw->painter->begin( gw );
    gw->painter->translate( coords.x() + 15, coords.y() + 15 );
    gw->painter->rotate( colorOffset / 3 );
    gw->painter->drawImage( -35, -35, wormholeImage );
    gw->painter->end();
}

QPoint Wormhole::getCoords() const
{
    return coords;
}

void Wormhole::setColorOffset( unsigned offset )
{
    colorOffset = offset;
}
