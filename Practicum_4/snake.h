#ifndef SNAKE_H
#define SNAKE_H

#include "gameplayobject.h"
#include <QImage>
#include <QPoint>

enum DIRECTION{ FORWARD = 0, BACKWARD, LEFT, RIGHT };

class Snake : public GameplayObject {
public:
    Snake( GameWidget * );
    virtual ~Snake();
    void paintGameplayObject() override;
    void changeDirection( DIRECTION );
    DIRECTION getDirection();
    void move();
    QPoint getHead();
    QVector<QPoint> getSnake();
    void grow();
private:
    GameWidget *gw;
    QVector<QPoint> pathVec;
    DIRECTION dir;
    QPoint lastPointBeforeTail;
};

#endif // SNAKE_H
