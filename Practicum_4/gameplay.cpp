#include "gameplay.h"
#include "results.h"
#include "mainmenu.h"
#include "snake.h"
#include "wall.h"
#include "apple.h"
#include "wormhole.h"
#include "snake.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define Enter_key 16777220

Gameplay::Gameplay( GameWidget *gw ) : gw( gw ), points( 0 ), keyAlreadyPressed( false ), keyAlreadyHoldedTime( 0 ),
    colorAppleTime( 0 ), MAIN_INTERVAL( 325 ), BOOST_INTERVAL( 100 ), PUSHING_TIME( 250 ), COLOR_INTERVAL( 10 ),
    gameIsOver( false ), gamePaused( false ), gameplayAlreadyStarted( false ), gameOverCapacityNumber( 0 )
{
    srand( ::time( 0 ) );

    button_back.load( ":/images/Images/button_back.png" );
    button_pause.load( ":/images/Images/button_pause.png" );
    button_continue.load( ":/images/Images/button_continue.png" );
    game_over_image.load( ":/images/Images/gameover.png" );

    createBasicGameplayObjects();

    getAppleAndWormholeOnFreeSpace();

    timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( gameStep() ) );
    timer->start( MAIN_INTERVAL );
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    timer4key = new QTimer( this );
    connect( timer4key, SIGNAL( timeout() ), this, SLOT( holdingKey() ) );
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    timer4Apple = new QTimer( this );
    connect( timer4Apple, SIGNAL( timeout() ), this, SLOT( appleColorChange() ) );
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    timer4GameOver = new QTimer( this );
    connect( timer4GameOver, SIGNAL( timeout() ), this, SLOT( gameOverCapacity() ) );

    backRect = QRect( 32, 15, 213, 64 );
    pauseRect = QRect( 247, 15, 213, 64 );

    for ( int i = 0; i < 22; i++ )
        for ( int j = 0; j < 32; j++ )
            fieldPoints[ i ][ j ] = false;

    fieldPoints[ 21 ][ 0 ] = true;
    fieldPoints[ 21 ][ 1 ] = true;
    fieldPoints[ 21 ][ 2 ] = true;

    gw->update();
}

Gameplay::~Gameplay()
{
    delete timer;
    delete timer4key;
    delete timer4Apple;
    delete timer4GameOver;
    delete snake;
    delete wall;
    delete field;
    delete apple;
    delete wormhole;
}

void Gameplay::paint()
{
    //qDebug() << "GP paint";
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

    paintAllGameplayObjects();

    if ( gameIsOver ) {
        gw->painter->begin( gw );
        gw->painter->drawPixmap( gw->rect(), QPixmap( ":/images/Images/gameplay_bg.png" ) );
        gw->painter->drawImage( 32, 15, button_back );
        gw->painter->end();

        paintAllGameplayObjects();

        gw->painter->begin( gw );
        gw->painter->drawImage( 350, 220, game_over_image );
        gw->painter->setPen( QColor( 255, 255, 255 ) );
        gw->painter->setFont( QFont( "Times", 18, QFont::Bold ) );
        gw->painter->drawText( 430, 380, QString( "Points: " + str.number( points ) ) );
        gw->painter->setFont( QFont( "Times", 12 ) );
        gw->painter->setPen( QColor( 255, 255, 255, ( gameOverCapacityNumber < 128 )?
                                         gameOverCapacityNumber  : 255 - gameOverCapacityNumber ) );
        gameOverCapacityNumber %= 254;
        gw->painter->drawText( 360, 415, QString( "Press enter to save the results." ) );
        gw->painter->end();
    }
}

void Gameplay::nextState()
{
    gw->setState( new Results( gw, points ) );
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

    bool canMove = tryToMoveSnake(); //possibility to move

    if ( canMove ) {
        dynamic_cast<Snake *>( snake )->move();
        {
            QVector<QPoint> vec = dynamic_cast<Snake *>( snake )->getSnake();
            for ( int i = 1; i < vec.size(); i++ ) { // collision testing
                if ( vec[ 0 ] == vec[ i ] )
                    gameOver();
            }

        }
        if ( dynamic_cast<Snake *>( snake )->getHead() == dynamic_cast<Apple *>( apple )->getCoords() ) {
            dynamic_cast<Snake *>( snake )->grow();
            points++;
            dynamic_cast<Snake *>( snake )->move( dynamic_cast<Wormhole *>( wormhole )->getCoords() );

            if ( apple != nullptr )
                delete apple;
            if ( wormhole != nullptr )
                delete wormhole;
            apple = getAppleOnFreeSpace();
            wormhole = getWormholeOnFreeSpace();
        }
    }
    else
    {
        gameOver();
    }
    //gw->update();
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
            break;
        }    
    }
    if ( event->key() == Enter_key && gameIsOver )
        nextState();
    qDebug() << event->key();
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
    timer4GameOver->start( 10 );
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
    dynamic_cast<Wormhole *>( wormhole )->setColorOffset( ++colorAppleTime );
    gw->update();
}

bool Gameplay::tryToMoveSnake() const
{
    static QVector<QPoint> frontVec = dynamic_cast<Wall *>( wall )->getFronts();
    switch ( dynamic_cast<Snake *>( snake )->getDirection() ) {
    case FORWARD:
        if ( frontVec[ 1 ].y() >= dynamic_cast<Snake *>( snake )->getHead().y() )
            return false;
        break;
    case BACKWARD:
        if ( frontVec[ 0 ].y() <= dynamic_cast<Snake *>( snake )->getHead().y() + 30 )
            return false;
        break;
    case LEFT:
        if ( frontVec[ 0 ].x() >= dynamic_cast<Snake *>( snake )->getHead().x() )
            return false;
        break;
    case RIGHT:
        if ( frontVec[ 2 ].x() <= dynamic_cast<Snake *>( snake )->getHead().x() + 30 )
            return false;
        break;
    default:
        assert( false );
    }
    return true;
}

void Gameplay::updateFieldPoints()
{
    QVector<QPoint> snakeTail = dynamic_cast<Snake *>( snake )->getSnake();
    for ( int i = 0; i < 22; i++ )
        for ( int j = 0; j < 32; j++ )
            fieldPoints[ i ][ j ] = false;

    foreach ( QPoint x, snakeTail )
        fieldPoints[ ( x.x() - 32 ) / 30 ][ ( x.y() - 74 ) / 30 ] = true;
}

Apple *Gameplay::getAppleOnFreeSpace()
{
    Apple *tempApple = new Apple( gw );
    updateFieldPoints();
    QVector<int> tempVec;

    int xInd = rand() % 32;

    for ( int i = 0; i < 22; i++ ) {
        if ( fieldPoints[ xInd ][ i ] == false )
            tempVec.append( i );
    }
    if ( tempVec.isEmpty() ) {
        while ( tempVec.isEmpty() ) {
            xInd += 1;
            xInd = xInd % 32;
            for ( int i = 0; i < 22; i++ )
                if ( fieldPoints[ xInd ][ i ] == false )
                    tempVec.append( i );
        }
    }
    int yInd = tempVec[ rand() % tempVec.size() ];
    tempApple->setCoords( QPoint( 32 + xInd * 30, 74 + yInd * 30 ) );
    return tempApple;
}

Wormhole *Gameplay::getWormholeOnFreeSpace()
{
    Wormhole *tempWormhole = new Wormhole( gw );
    updateFieldPoints();
    QVector<int> tempVec;

    int xInd = rand() % 32;

    for ( int i = 0; i < 22; i++ ) {
        if ( fieldPoints[ xInd ][ i ] == false )
            tempVec.append( i );
    }
    if ( tempVec.isEmpty() ) {
        while ( tempVec.isEmpty() ) {
            xInd += 1;
            xInd = xInd % 32;
            for ( int i = 0; i < 22; i++ )
                if ( fieldPoints[ xInd ][ i ] == false )
                    tempVec.append( i );
        }
    }
    int yInd = tempVec[ rand() % tempVec.size() ];
    tempWormhole->setCoords( QPoint( 32 + xInd * 30, 74 + yInd * 30 ) );
    return tempWormhole;
}

void Gameplay::createBasicGameplayObjects()
{
    field = GameplayObject::createObject( FIELD, gw );
    wall = GameplayObject::createObject( WALL, gw );
    snake = GameplayObject::createObject( SNAKE, gw );
}

void Gameplay::getAppleAndWormholeOnFreeSpace()
{
    apple = getAppleOnFreeSpace();
    wormhole = getWormholeOnFreeSpace();
}

void Gameplay::paintAllGameplayObjects()
{
    field->paintGameplayObject();
    snake->paintGameplayObject();
    apple->paintGameplayObject();
    wormhole->paintGameplayObject();
    wall->paintGameplayObject();
}

void Gameplay::gameOverCapacity()
{
    gameOverCapacityNumber++;
}
