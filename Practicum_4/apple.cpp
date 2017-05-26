#include "apple.h"
#include <cassert>

Apple::Apple( GameWidget *gw ) : gw( gw ), coords( QPoint( -1, -1 ) )
{
    startColorValue = rand() % 255;
    blackHole.load( ":/images/Images/black_hole.png" );
}

Apple::~Apple()
{

}

void Apple::setColorOffset( unsigned offset )
{
    colorOffset = offset;
}

void Apple::paintGameplayObject()
{
    if ( coords == QPoint( -1, -1 ) )
        assert( "try to paint apple without set coords!" );
    gw->painter->begin( gw );
    appleBrush = QBrush( QColor( 255, 255, ( 51 + colorOffset ) % 255 ) );
    gw->painter->setRenderHint( QPainter::Antialiasing, true );
    gw->painter->setPen( Qt::NoPen );
    gw->painter->setBrush( appleBrush );
    gw->painter->translate( coords.x() + 15, coords.y() + 15 );
    gw->painter->rotate( colorOffset );
    gw->painter->drawImage( -30, -30, blackHole );
    gw->painter->drawEllipse( QPoint( 0, 0 ), 8, 8 );
    gw->painter->end();
}

QPoint Apple::getCoords() const
{
    return coords;
}

void Apple::setCoords( QPoint newPoint )
{
    coords = newPoint;
}
