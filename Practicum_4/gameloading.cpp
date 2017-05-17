#include "gameloading.h"
#include "gamewidget.h"
#include "mainmenu.h"

GameLoading::GameLoading( GameWidget *gw ) : gw( gw ), load( 0 )
{
    timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( loading() ) );
    timer->start( 1 );

    gw->update();
}

GameLoading::~GameLoading()
{
    delete timer;
}

void GameLoading::paint()
{
    qDebug() << "GL paint";
    gw->painter->begin( gw );
    gw->painter->drawPixmap( gw->rect(), QPixmap( ":/images/Images/main_pic.png" ) );
    QPoint lStart( 206, 725 );
    QPoint lFinish( 612, 25 );

    gw->painter->setRenderHint( QPainter::Antialiasing, true );
    gw->painter->setPen( QPen( QColor( 255, 255, 255 ), 2 ) );

    gw->painter->drawRect( lStart.x(), lStart.y(), lFinish.x(), lFinish.y() );

    QBrush lBrush( QColor( 140, 255, 98 ) );
    gw->painter->setBrush( lBrush );

    if ( load < lFinish.x() ) {
        gw->painter->drawRect( lStart.x(), lStart.y(), load, 25 );
        gw->painter->end();
    }
    else {
        timer->stop();
        gw->painter->end();
        nextState();
    }
}

void GameLoading::nextState()
{
    gw->setState( new MainMenu( gw ) );
}

void GameLoading::loading()
{
    load++;
    gw->update();
}
