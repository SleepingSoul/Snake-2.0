#include "snake.h"
#include <cassert>

Snake::Snake( GameWidget *gw ) : gw( gw )
{
    pathVec.reserve( 1000 );
    pathVec.append( QPoint( 32, 644 ) );
    pathVec.append( QPoint( 32, 674 ) );
    pathVec.append( QPoint( 32, 704 ) );
    dir = FORWARD;
}

Snake::~Snake()
{

}

void Snake::paintGameplayObject()
{
    gw->painter->begin( gw );
    gw->painter->setBrush( QBrush( Qt::yellow ) );
    foreach ( QPoint x, pathVec ) {
        gw->painter->drawRect( x.x(), x.y(), 30, 30 );
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
{/*
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
    lastPointBeforeTail = pathVec.last();
    pathVec.removeLast();*/
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
