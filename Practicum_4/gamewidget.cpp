#include "gamewidget.h"
#include "gameloading.h"
#include <QMouseEvent>

GameWidget::GameWidget( QWidget *parent ) : QWidget( parent )
{
    painter = new QPainter( this );
    painter->setRenderHint( QPainter::Antialiasing, true );
    setState( new GameLoading( this ) );
}

void GameWidget::setState( class State *s )
{
    if ( current != nullptr )
        delete current;
    current = s;
}

void GameWidget::paintEvent( QPaintEvent * )
{
    current->paint();
}

void GameWidget::mouseReleaseEvent( QMouseEvent *event )
{
    current->mouseReleased( event );
}

void GameWidget::keyPressEvent( QKeyEvent *event )
{
    current->keyPressed( event );
}

void GameWidget::keyReleaseEvent( QKeyEvent *event )
{
    if ( event->isAutoRepeat() )
        event->ignore();
    else
        current->keyReleased( event );
}
