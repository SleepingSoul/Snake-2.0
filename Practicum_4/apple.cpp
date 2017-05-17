#include "apple.h"
#include <cstdlib>
#include <ctime>

Apple::Apple( GameWidget *gw ) : gw( gw )
{
    srand( time( 0 ) );
    int x = rand() % 32;
    int y = rand() % 22;
    coords = QPoint( x * 30 + 32, y * 30 + 74 );
    appleBrush = QBrush( ( ++count % 2 == 0 )? Qt::red : Qt::green );
}

unsigned Apple::count = 0;

Apple::~Apple()
{

}

void Apple::paintGameplayObject()
{
    gw->painter->begin( gw );
    gw->painter->setPen( Qt::NoPen );
    gw->painter->setBrush( appleBrush );
    gw->painter->drawEllipse( QPoint( coords.x() + 15, coords.y() + 15 ), 15, 15 );
    gw->painter->end();
}

QPoint Apple::getCoords()
{
    return coords;
}
