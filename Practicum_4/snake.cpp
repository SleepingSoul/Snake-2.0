#include "snake.h"
#include <cassert>
#include <exception>

Snake::Snake( GameWidget *gw ) : gw( gw ), dir( FORWARD ), tailDir( FORWARD )
{
    pathVec.reserve( 1000 );
    pathParamsVec.resize( 1000 );
    pathParamsVec.fill( NOTHING );
    pathVec.append( QPoint( 32, 644 ) );
    pathVec.append( QPoint( 32, 674 ) );
    pathVec.append( QPoint( 32, 704 ) );
}

Snake::~Snake()
{

}

void Snake::paintGameplayObject()
{
    gw->painter->begin( gw );
    gw->painter->setRenderHint( QPainter::Antialiasing, true );
    gw->painter->setBrush( QBrush( Qt::yellow ) );
    gw->painter->setPen( Qt::NoPen );

    switch ( dir ) {
    case FORWARD:
        gw->painter->drawEllipse( QPoint( getHead().x() + 15, getHead().y() ), 15, 10 );
        break;
    case BACKWARD:
        gw->painter->drawEllipse( QPoint( getHead().x() + 15, getHead().y() + 30 ), 15, 10 );
        break;
    case LEFT:
        gw->painter->drawEllipse( QPoint( getHead().x(), getHead().y() + 15 ), 10, 15 );
        break;
    case RIGHT:
        gw->painter->drawEllipse( QPoint( getHead().x() + 30, getHead().y() + 15 ), 10, 15 );
        break;
    default:
        assert( false );
    }

    switch ( tailDir ) {
    case FORWARD:
        gw->painter->drawEllipse( QPoint( pathVec.last().x() + 15, pathVec.last().y() + 30 ), 15, 10 );
        break;
    case BACKWARD:
        gw->painter->drawEllipse( QPoint( pathVec.last().x() + 15, pathVec.last().y() ), 15, 10 );
        break;
    case LEFT:
        gw->painter->drawEllipse( QPoint( pathVec.last().x() + 30, pathVec.last().y() + 15 ), 10, 15 );
        break;
    case RIGHT:
        gw->painter->drawEllipse( QPoint( pathVec.last().x(), pathVec.last().y() + 15 ), 10, 15 );
        break;
    default:
        assert( false );
    }

    for ( int i = 0; i < pathVec.size(); i++ ) {
        if ( pathParamsVec[ i ] == DRAW_APPLE ) {
            //appleBrush = QBrush( QColor( 255, 255, ( 51 + colorOffset ) % 255 ) );
            gw->painter->setRenderHint( QPainter::Antialiasing, true );
            gw->painter->setPen( Qt::NoPen );
            //gw->painter->setBrush( appleBrush );
            //gw->painter->translate( x.x() + 15, x.y() + 15 );
            //gw->painter->rotate( colorOffset / 10.0 );
            gw->painter->drawImage( pathVec[ i ].x() - 30, pathVec[ i ].y() - 30,
                                    QImage( ":/images/Images/black_hole.png" ) );
            //gw->painter->drawEllipse( QPoint( 0, 0 ), 8, 8 );
        }
        if ( pathParamsVec[ i ] == DRAW_WORMHOLE ) {
            gw->painter->setBrush( QBrush( Qt::blue ) );
            gw->painter->drawEllipse( pathVec[ i ].x(), pathVec[ i ].y(), 40, 40 );
        }
    }
    foreach ( QPoint x, pathVec ) {
        gw->painter->setBrush( QBrush( Qt::yellow ) );
        gw->painter->drawRect( x.x(), x.y(), 30, 30 );
        gw->painter->setBrush( Qt::black );
        gw->painter->drawEllipse( QPoint( x.x() + 15, x.y() + 15 ), 7, 7 );
    }
    gw->painter->end();
}

void Snake::changeDirection( DIRECTION newDir )
{
    dir = newDir;
}

DIRECTION Snake::getDirection()
{
    return dir;
}

void Snake::move()
{
    switch ( dir ) {
    case FORWARD:
        pathVec.push_front( QPoint( pathVec[ 0 ].x(), pathVec[ 0 ].y() - 30 ) );
        break;
    case BACKWARD:
        pathVec.push_front( QPoint( pathVec[ 0 ].x(), pathVec[ 0 ].y() + 30 ) );
        break;
    case LEFT:
        pathVec.push_front( QPoint( pathVec[ 0 ].x() - 30, pathVec[ 0 ].y() ) );
        break;
    case RIGHT:
        pathVec.push_front( QPoint( pathVec[ 0 ].x() + 30, pathVec[ 0 ].y() ) );
        break;
    default:
        assert( false );
    }
    // setting tail direction
    if ( pathVec.last().x() - pathVec[ pathVec.size() - 2 ].x() == -30 )
        tailDir = RIGHT;
    else if ( pathVec.last().x() - pathVec[ pathVec.size() - 2 ].x() == 30 )
        tailDir = LEFT;
    if ( pathVec.last().y() - pathVec[ pathVec.size() - 2 ].y() == -30 )
        tailDir = BACKWARD;
    else if ( pathVec.last().y() - pathVec[ pathVec.size() - 2 ].y() == 30 )
        tailDir = FORWARD;

    lastPointBeforeTail = pathVec.last();
    pathVec.removeLast();
}

void Snake::move( QPoint movePoint )
{
    pathVec.push_front( movePoint );

    // setting tail direction
    if ( pathVec.last().x() - pathVec[ pathVec.size() - 2 ].x() == -30 )
        tailDir = RIGHT;
    else if ( pathVec.last().x() - pathVec[ pathVec.size() - 2 ].x() == 30 )
        tailDir = LEFT;
    if ( pathVec.last().y() - pathVec[ pathVec.size() - 2 ].y() == -30 )
        tailDir = BACKWARD;
    else if ( pathVec.last().y() - pathVec[ pathVec.size() - 2 ].y() == 30 )
        tailDir = FORWARD;

    lastPointBeforeTail = pathVec.last();
    pathVec.removeLast();
}

QPoint Snake::getHead()
{
    return pathVec[ 0 ];
}

QVector<QPoint> Snake::getSnake()
{
    return pathVec;
}

void Snake::grow()
{
    pathVec.push_back( lastPointBeforeTail );
}

void Snake::setAdditionalDrawing( QPoint x, ADDITIONAL_DRAWING ad )
{
    int i = 0;
    foreach ( QPoint sp, pathVec ) {
        if ( sp == x ) {
            pathParamsVec[ i ] = ad;
            return;
        }
    i++;
    }
}
