#include "field.h"

Field::Field( GameWidget *gw ) : gw( gw )
{
    southwestPoint = QPoint( 32, 734 );
    northwestPoint = QPoint( 32, 74 );
    northeastPoint = QPoint( 992, 74 );
    southeastPoint = QPoint( 992, 734 );
    fieldImage.load( ":/images/Images/field.png" );
}

Field::~Field()
{

}

void Field::paintGameplayObject()
{
    gw->painter->begin( gw );
    gw->painter->drawImage( northwestPoint, fieldImage );
    gw->painter->end();
}
