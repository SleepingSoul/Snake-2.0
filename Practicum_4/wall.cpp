#include "wall.h"
#include <QPainter>

Wall::Wall( GameWidget *gw ) : gw( gw )
{
    southwestPoint = QPoint( 32, 734 );
    northwestPoint = QPoint( 32, 74 );
    northeastPoint = QPoint( 992, 74 );
    southeastPoint = QPoint( 992, 734 );
}

Wall::~Wall()
{

}

void Wall::paintGameplayObject()
{
    gw->painter->begin( gw );
    gw->painter->setPen( QPen( QColor( 255, 255, 255 ), 5 ) );
    gw->painter->drawRect( northwestPoint.x(), northwestPoint.y(), northeastPoint.x() - northwestPoint.x(),
                      southwestPoint.y() - northwestPoint.y() );
    gw->painter->end();
}

QVector<QPoint> Wall::getFronts()
{
    return QVector<QPoint>() << southwestPoint << northwestPoint << northeastPoint << southeastPoint;
}
