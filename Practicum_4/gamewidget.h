#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QtWidgets>
#include "state.h"

class State;

class GameWidget : public QWidget {
public:
    GameWidget( QWidget * = 0 );
    void setState( State * );
    QPainter *painter;
protected:
    void paintEvent( QPaintEvent * ) override;
    void mouseReleaseEvent( QMouseEvent * ) override;
    void keyPressEvent( QKeyEvent * ) override;
    void keyReleaseEvent( QKeyEvent * ) override;
private:
    State *current{ nullptr };
};

#endif // GAMEWIDGET_H
