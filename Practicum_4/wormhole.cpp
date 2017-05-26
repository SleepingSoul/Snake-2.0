#include "wormhole.h"
#include <cassert>

Wormhole::Wormhole( GameWidget *gw ) : gw( gw ), colorOffset( 0 ), coords( QPoint( -1, -1 ) )
{
    wormholeImage.load( ":/images/Images/wormhole.png" );
}

Wormhole::~Wormhole()
{

}

void Wormhole::paintGameplayObject()
{
    if ( coords == QPoint( -1, -1 ) )
        assert( "try to paint wormhole without set coords!" );
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

void Wormhole::setCoords( QPoint newCoords )
{
    coords = newCoords;
}
