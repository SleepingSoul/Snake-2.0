#include "game.h"
#include <QWidget>
#include <QApplication>

Game::Game() {}

int Game::run( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    g_wgt = new GameWidget();
    g_wgt->setFixedHeight( 768 );
    g_wgt->setFixedWidth( 1024 );
    g_wgt->show();
    return app.exec();
}
