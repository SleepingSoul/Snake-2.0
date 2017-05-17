#include "apple.h"
#include <cstdlib>
#include <ctime>

Apple::Apple( GameWidget *gw ) : gw( gw )
{
    srand( ::time( 0 ) );
    int x = rand() % 32;
    int y = rand() % 22;
    coords = QPoint( x * 30 + 32, y * 30 + 74 );
    startColorValue = rand() % 255;
    blackHole = QImage( ":/images/Images/black_hole.png" );
}

unsigned Apple::count = 0;

Apple::~Apple()
{

}

void Apple::setColorOffset( unsigned offset )
{
    colorOffset = offset;
}

void Apple::paintGameplayObject()
{
    gw->painter->begin( gw );
    appleBrush = QBrush( QColor( 255, 255, ( 51 + colorOffset ) % 255 ) );
    gw->painter->setRenderHint( QPainter::Antialiasing, true );
    gw->painter->setPen( Qt::NoPen );
    gw->painter->setBrush( appleBrush );
    gw->painter->drawImage( coords.x() - 15, coords.y() - 15, blackHole );
    gw->painter->drawEllipse( QPoint( coords.x() + 15, coords.y() + 15 ), 8, 8 );
    gw->painter->end();
}

QPoint Apple::getCoords()
{
    return coords;
}
