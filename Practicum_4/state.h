#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QMouseEvent>
#include <QImage>
#include "gamewidget.h"

class State : public QObject {
public:
    virtual void nextState() = 0;
    virtual void paint() = 0;
    virtual void mouseReleased( QMouseEvent * ) = 0;
    virtual void keyPressed( QKeyEvent * ) = 0;
    virtual void keyReleased( QKeyEvent * ) = 0;
};

#endif
