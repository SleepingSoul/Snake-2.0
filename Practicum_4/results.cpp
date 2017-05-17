#include "results.h"
#include "mainmenu.h"

Results::Results( GameWidget *gw ) : gw( gw )
{
    button_back.load( ":/images/Images/button_back.png" );

    gw->update();
}

Results::~Results()
{

}

void Results::paint()
{
    gw->painter->begin( gw );
    gw->painter->drawPixmap( gw->rect(), QPixmap( ":/images/Images/scrreen_results.png" ) );
    gw->painter->drawImage( 15, 15, button_back );
    gw->painter->end();
}

void Results::mouseReleased( QMouseEvent *event )
{
    int x = event->pos().x();
    int y = event->pos().y();
    if ( x >= 15 && x <= 213 && y >= 15 && y <= 64 )
        gw->setState( new MainMenu( gw ) );
}
