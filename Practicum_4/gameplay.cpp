#include "gameplay.h"
#include "results.h"
#include "mainmenu.h"
#include "snake.h"
#include "wall.h"
#include "apple.h"
#include <cassert>
#include <string>

Gameplay::Gameplay( GameWidget *gw ) : gw( gw ), points( 0 ), keyAlreadyPressed( false ), keyAlreadyHoldedTime( 0 ),
    colorAppleTime( 0 ), MAIN_INTERVAL( 325 ), BOOST_INTERVAL( 100 ), PUSHING_TIME( 250 ), COLOR_INTERVAL( 10 ),
    gameIsOver( false ), gamePaused( false ), gameplayAlreadyStarted( false )
{
    button_back.load( ":/images/Images/button_back.png" );
    button_pause.load( ":/images/Images/button_pause.png" );
    button_continue.load( ":/images/Images/button_continue.png" );

    field = GameplayObject::createObject( FIELD, gw );
    wall = GameplayObject::createObject( WALL, gw );
    snake = GameplayObject::createObject( SNAKE, gw );

    bool intersected;
    do {
        intersected = false;
        if ( apple != nullptr )
            delete apple;
        apple = GameplayObject::createObject( APPLE, gw );
        foreach ( QPoint x, dynamic_cast<Snake *>( snake )->getSnake() )
            if ( x == dynamic_cast<Apple *>( apple )->getCoords() ) {
                intersected = true;
                break;
            }
    }
    while ( intersected );

    timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( gameStep() ) );
    timer->start( MAIN_INTERVAL );

    timer4key = new QTimer( this );
    connect( timer4key, SIGNAL( timeout() ), this, SLOT( holdingKey() ) );

    timer4Apple = new QTimer( this );
    connect( timer4Apple, SIGNAL( timeout() ), this, SLOT( appleColorChange() ) );

    backRect = QRect( 32, 15, 213, 64 );
    pauseRect = QRect( 247, 15, 213, 64 );

    gw->update();
}

Gameplay::~Gameplay()
{
    delete timer;
    delete timer4key;
    delete timer4Apple;
    delete snake;
    delete wall;
    delete field;
}

void Gameplay::paint()
{
    qDebug() << "GP paint";
    if ( !gameplayAlreadyStarted ) {
        gameplayAlreadyStarted = true;
        timer4Apple->start( COLOR_INTERVAL );
    }
    gw->painter->begin( gw );
    gw->painter->drawPixmap( gw->rect(), QPixmap( ":/images/Images/gameplay_bg.png" ) );
    gw->painter->drawImage( 32, 15, button_back );
    if ( !gamePaused )
        gw->painter->drawImage( 247, 15, button_pause );
    else
        gw->painter->drawImage( 247, 15, button_continue );
    gw->painter->setPen( Qt::white );
    gw->painter->setFont( QFont( "Times", 18, QFont::Bold ) );
    static QString str;   ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///
    gw->painter->drawText( QPoint( 600, 47 ), QString( "Points: " + str.number( points ) ) );
    gw->painter->end();

    field->paintGameplayObject();
    wall->paintGameplayObject();
    snake->paintGameplayObject();
    apple->paintGameplayObject();

    if ( gameIsOver ) {
        gw->painter->begin( gw );
        gw->painter->drawPixmap( gw->rect(), QPixmap( ":/images/Images/gameplay_bg.png" ) );
        gw->painter->drawImage( 32, 15, button_back );
        gw->painter->end();

        field->paintGameplayObject();
        wall->paintGameplayObject();
        snake->paintGameplayObject();
        apple->paintGameplayObject();

        gw->painter->begin( gw );
        gw->painter->drawImage( 350, 220, QImage( ":/images/Images/gameover.png" ) );
        gw->painter->setPen( Qt::white );
        gw->painter->setFont( QFont( "Times", 18, QFont::Bold ) );
        gw->painter->drawText( 430, 380, QString( "Points: " + str.number( points ) ) );
        gw->painter->end();
    }
}

void Gameplay::nextState()
{
    gw->setState( new Results( gw ) );
}

void Gameplay::mouseReleased( QMouseEvent *event )
{
    QPoint point = event->pos();
    if ( backRect.contains( point ) )
        gw->setState( new MainMenu( gw ) );
    if ( pauseRect.contains( point ) ) {
        if ( gamePaused )
            continueGame();
        else
            pause();
    }
}

void Gameplay::gameStep()
{
    keyAlreadyHoldedTime = 0;
    keyAlreadyPressed = false;

    static QVector<QPoint> frontVec = dynamic_cast<Wall *>( wall )->getFronts();
    bool poss = true; //possibility to move
    switch ( dynamic_cast<Snake *>( snake )->getDirection() ) {
    case FORWARD:
        if ( frontVec[ 1 ].y() >= dynamic_cast<Snake *>( snake )->getHead().y() )
            poss = false;
        break;
    case BACKWARD:
        if ( frontVec[ 0 ].y() <= dynamic_cast<Snake *>( snake )->getHead().y() + 30 )
            poss = false;
        break;
    case LEFT:
        if ( frontVec[ 0 ].x() >= dynamic_cast<Snake *>( snake )->getHead().x() )
            poss = false;
        break;
    case RIGHT:
        if ( frontVec[ 2 ].x() <= dynamic_cast<Snake *>( snake )->getHead().x() + 30 )
            poss = false;
        break;
    default:
        assert( false );
    }

    if ( poss ) {
        dynamic_cast<Snake *>( snake )->move();
        {
            QVector<QPoint> vec = dynamic_cast<Snake *>( snake )->getSnake();
            for ( int i = 1; i < vec.size(); i++ )
                if ( vec[ 0 ] == vec[ i ] )
                    gameOver();

        }
        if ( dynamic_cast<Snake *>( snake )->getHead() == dynamic_cast<Apple *>( apple )->getCoords() ) {
            dynamic_cast<Snake *>( snake )->grow();
            points++;

            bool intersected;
            do {
                intersected = false;
                delete apple;
                apple = GameplayObject::createObject( APPLE, gw );
                foreach ( QPoint x, dynamic_cast<Snake *>( snake )->getSnake() ) {
                    if ( x == dynamic_cast<Apple *>( apple )->getCoords() ) {
                        intersected = true;
                        break;
                    }
                }
            }
            while ( intersected );
        }
    }
    else
    {
        gameOver();
    }
    gw->update();
}

void Gameplay::keyPressed( QKeyEvent *event )
{
    if ( !keyAlreadyPressed ) {
        switch ( event->key() ) {
        case Qt::Key_Left:
            if ( dynamic_cast<Snake *>( snake )->getDirection() != RIGHT ) {
                dynamic_cast<Snake *>( snake )->changeDirection( LEFT );
                keyAlreadyPressed = true;
                timer4key->start( PUSHING_TIME );
            }
            break;
        case Qt::Key_Right:
            if ( dynamic_cast<Snake *>( snake )->getDirection() != LEFT ) {
                dynamic_cast<Snake *>( snake )->changeDirection( RIGHT );
                keyAlreadyPressed = true;
                timer4key->start( PUSHING_TIME );
            }
            break;
        case Qt::Key_Up:
            if ( dynamic_cast<Snake *>( snake )->getDirection() != BACKWARD ) {
                dynamic_cast<Snake *>( snake )->changeDirection( FORWARD );
                keyAlreadyPressed = true;
                timer4key->start( PUSHING_TIME );
            }
            break;
        case Qt::Key_Down:
            if ( dynamic_cast<Snake *>( snake )->getDirection() != FORWARD ) {
                dynamic_cast<Snake *>( snake )->changeDirection( BACKWARD );
                keyAlreadyPressed = true;
                timer4key->start( PUSHING_TIME );
            }
        }
    }
}

void Gameplay::holdingKey()
{
    timer4key->stop();
    timer->setInterval( BOOST_INTERVAL );
}

void Gameplay::keyReleased( QKeyEvent * )
{
    timer4key->stop();
    if ( timer->interval() != MAIN_INTERVAL )
        timer->setInterval( MAIN_INTERVAL );
}

void Gameplay::gameOver()
{
    timer->stop();
    gameIsOver = true;
}

void Gameplay::pause()
{
    timer->stop();
    gamePaused = true;
    gw->update();
}

void Gameplay::continueGame()
{
    timer->start( MAIN_INTERVAL );
    gamePaused = false;
    gw->update();
}

void Gameplay::appleColorChange()
{
    dynamic_cast<Apple *>( apple )->setColorOffset( ++colorAppleTime );
    gw->update();
}
