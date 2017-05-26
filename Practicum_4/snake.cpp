#include "snake.h"
#include <cassert>
#include <exception>
#include <cmath>

Snake::Snake( GameWidget *gw ) : gw( gw ), dir( FORWARD ), tailDir( FORWARD )
{
    pathVec.reserve( 1000 );
    pathParamsVec.resize( 1000 );
    pathParamsVec.fill( NOTHING );
    pathVec.append( QPoint( 32, 644 ) );
    pathVec.append( QPoint( 32, 674 ) );
    pathVec.append( QPoint( 32, 704 ) );
    wormholeImage.load( ":/images/Images/wormhole.png"  );
    appleImage.load( ":/images/Images/black_hole.png" );
}

Snake::~Snake()
{

}

void Snake::paintGameplayObject()
{
    gw->painter->begin( gw );
    gw->painter->setRenderHint( QPainter::Antialiasing, true );
    gw->painter->setPen( Qt::NoPen );

    switch ( dir ) {
    case FORWARD:
        gw->painter->setBrush( QBrush( QColor( 173, 216, 230 ) ) );
        gw->painter->drawEllipse( QPoint( getHead().x() + 15, getHead().y() ), 15, 10 );
        gw->painter->setBrush( QBrush( Qt::black ) );
        gw->painter->drawEllipse( QPoint( getHead().x() + 7, getHead().y() - 3 ), 3, 3 );
        gw->painter->drawEllipse( QPoint( getHead().x() + 23, getHead().y() - 3 ), 3, 3 );
        break;
    case BACKWARD:
        gw->painter->setBrush( QBrush( QColor( 173, 216, 230 ) ) );
        gw->painter->drawEllipse( QPoint( getHead().x() + 15, getHead().y() + 30 ), 15, 10 );
        gw->painter->setBrush( QBrush( Qt::black ) );
        gw->painter->drawEllipse( QPoint( getHead().x() + 7, getHead().y() + 33 ), 3, 3 );
        gw->painter->drawEllipse( QPoint( getHead().x() + 23, getHead().y() + 33 ), 3, 3 );
        break;
    case LEFT:
        gw->painter->setBrush( QBrush( QColor( 173, 216, 230 ) ) );
        gw->painter->drawEllipse( QPoint( getHead().x(), getHead().y() + 15 ), 10, 15 );
        gw->painter->setBrush( QBrush( Qt::black ) );
        gw->painter->drawEllipse( QPoint( getHead().x() - 3, getHead().y() + 7 ), 3, 3 );
        gw->painter->drawEllipse( QPoint( getHead().x() - 3, getHead().y() + 23 ), 3, 3 );
        break;
    case RIGHT:
        gw->painter->setBrush( QBrush( QColor( 173, 216, 230 ) ) );
        gw->painter->drawEllipse( QPoint( getHead().x() + 30, getHead().y() + 15 ), 10, 15 );
        gw->painter->setBrush( QBrush( Qt::black ) );
        gw->painter->drawEllipse( QPoint( getHead().x() + 33, getHead().y() + 7 ), 3, 3 );
        gw->painter->drawEllipse( QPoint( getHead().x() + 33, getHead().y() + 23 ), 3, 3 );
        break;
    default:
        assert( false );
    }

    gw->painter->setBrush( QBrush( QColor( 173, 216, 230 ) ) );
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

    updateDrawingVec();

    for ( int i = 0; i < pathVec.size(); i++ ) {
        if ( pathParamsVec[ i ] == DRAW_WORMHOLE )
            gw->painter->drawImage( pathVec[ i ].x() - 20, pathVec[ i ].y() - 20, wormholeImage );
        else if ( pathParamsVec[ i ] == DRAW_APPLE )
            gw->painter->drawImage( pathVec[ i ].x() - 15, pathVec[ i ].y() - 15, appleImage );
    }
    foreach ( QPoint x, pathVec ) {
        gw->painter->setBrush( QBrush( QColor( 173, 216, 230 ) ) );
        gw->painter->drawRect( x.x(), x.y(), 30, 30 );
        gw->painter->setBrush( QBrush( Qt::black ) );
        gw->painter->drawEllipse( QPoint( x.x() + 15, x.y() + 15 ), 7, 7 );
    }
    gw->painter->end();
}

void Snake::changeDirection( DIRECTION newDir )
{
    dir = newDir;
}

DIRECTION Snake::getDirection() const
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

QPoint Snake::getHead() const
{
    return pathVec[ 0 ];
}

QVector<QPoint> Snake::getSnake() const
{
    return pathVec;
}

void Snake::grow()
{
    pathVec.push_back( lastPointBeforeTail );
}

void Snake::setAdditionalDrawing( QPoint x, ADDITIONAL_DRAWING ad )
{
    if ( pathVec.contains( x ) )
        pathParamsVec[ pathVec.indexOf( x ) ] = ad;
    else
        assert( "Tried to set drawing to incorrect point (point is not exist in snake vec)" );
}

bool Snake::isRupture( const QPoint p_one, const QPoint p_two ) const
{
    if ( std::sqrt( std::pow( p_one.x() - p_two.x(), 2) + std::pow( p_one.y() - p_two.y(), 2 ) ) == 30 )
        return false;
    return true;
}

void Snake::updateDrawingVec()
{
    for ( int i = 1; i < pathVec.size(); i++ ) {
        if ( isRupture( pathVec[ i - 1 ], pathVec[ i ] ) ) {
            pathParamsVec[ i - 1 ] = DRAW_WORMHOLE;
            pathParamsVec[ i ] = DRAW_APPLE;
            i++;
        }
        else {
            pathParamsVec[ i - 1 ] = NOTHING;
            pathParamsVec[ i ] = NOTHING;
        }
    }
    if ( !isRupture( pathVec[ 0 ], pathVec[ 1 ] ) ) {
        pathParamsVec[ 0 ] = NOTHING;
        pathParamsVec[ 1 ] = NOTHING;
    }
    if ( isRupture( pathVec[ 1 ], pathVec[ 2 ] ) )
        pathParamsVec[ 1 ] = DRAW_WORMHOLE;
}
