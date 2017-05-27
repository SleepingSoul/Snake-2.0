#include "mainmenu.h"
#include "gameplay.h"
#include "results.h"
#include <QDebug>
#include <QtMath>

MainMenu::MainMenu( GameWidget *gw ) : gw( gw ), load( 0 ), oscillationCount_newgame( 0 ),
    oscillationCount_results( 0 ), oscillationCount_exit( 0 ), coeff_newgame( 100 ),
    coeff_results( 100 ), coeff_exit( 100 )
{
    background.load( ":/images/Images/loaded_pic.png" );
    button_newgame.load( ":/images/Images/button_newgame.png" );
    button_results.load( ":/images/Images/button_results.png" );
    button_exit.load( ":/images/Images/button_exit.png" );
    rect_newgame.setCoords( 311, 260, 724, 343 );
    rect_results.setCoords( 311, 395, 724, 478 );
    rect_exit.setCoords( 311, 530, 724, 613 );

    timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( btnloading() ) );
    timer->start( 0.5 );

    gw->update();
}

MainMenu::~MainMenu()
{
    delete timer;
}

void MainMenu::paint()
{
    //qDebug() << "MM paint";
    gw->painter->begin( gw );
    gw->painter->drawImage( gw->rect(), background );

    if ( load <= rect_newgame.width() )
        gw->painter->drawImage( rect_newgame.x(), rect_newgame.y(), button_newgame, 0, 0, load, rect_newgame.height() );
    else if ( oscillationCount_newgame++ < 100 ) {
        gw->painter->drawImage( rect_newgame.x() + coeff_newgame * qSin( 0.035 * ( load - rect_newgame.width() ) ) , rect_newgame.y(), button_newgame );
        coeff_newgame -= 1;
    }
    else
        gw->painter->drawImage( rect_newgame, button_newgame );

    if ( load <= rect_newgame.width() * 4.0 / 3.0 && load > rect_newgame.width() / 3 )
        gw->painter->drawImage( rect_results.x(), rect_results.y(), button_results, 0, 0, load - rect_results.width() / 3, rect_results.height() );
    else if ( load > rect_newgame.width() * 4.0 / 3.0 && oscillationCount_results++ < 100 ) {
        gw->painter->drawImage( rect_results.x() + coeff_results * qSin( 0.035 * ( load - rect_results.width() * 4.0 / 3.0 ) ) ,
                           rect_results.y(), button_results );
        coeff_results -= 1;
    }
    else if ( load > rect_newgame.width() * 4.0 / 3.0 )
        gw->painter->drawImage( rect_results, button_results );

    if ( load <= rect_newgame.width() * 5.0 / 3.0 && load > rect_newgame.width() / 1.5 )
        gw->painter->drawImage( rect_exit.x(), rect_exit.y(), button_exit, 0, 0, load - rect_exit.width() / 1.5, rect_exit.height() );
    else if ( load > rect_newgame.width() * 5.0 / 3.0 && oscillationCount_exit++ < 100 ) {
        gw->painter->drawImage( rect_exit.x() + coeff_exit * qSin( 0.05 * ( load - rect_results.width() * 5.0 / 3.0 ) ) , rect_exit.y(), button_exit );
        coeff_exit -= 1;
    }
    else if ( load > rect_newgame.width() * 5.0 / 3.0 ) {
        gw->painter->drawImage( rect_exit, button_exit );
        timer->stop();
    }
    gw->painter->end();
}

void MainMenu::nextState()
{
    gw->setState( new Gameplay( gw ) );
}

void MainMenu::mouseReleased( QMouseEvent *event )
{
    QPoint point = event->pos();
    if ( rect_newgame.contains( point ) )
        gw->setState( new Gameplay( gw ) );
    else if ( rect_results.contains( point ) )
        gw->setState( new Results( gw ) );
    else if ( rect_exit.contains( point ) )
        gw->close();
}

void MainMenu::btnloading()
{
    load++;
    gw->update();
}
