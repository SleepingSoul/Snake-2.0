#ifndef SNAKE_H
#define SNAKE_H

#include "gameplayobject.h"
#include <QImage>
#include <QPoint>

enum DIRECTION{ FORWARD = 0, BACKWARD, LEFT, RIGHT };
enum ADDITIONAL_DRAWING{ NOTHING = 0, DRAW_APPLE, DRAW_WORMHOLE };

class Snake : public GameplayObject {
public:
    Snake( GameWidget * );
    virtual ~Snake();
    void paintGameplayObject() override;
    void changeDirection( DIRECTION );
    DIRECTION getDirection();
    void move();
    void move( QPoint );
    QPoint getHead();
    QVector<QPoint> getSnake();
    void grow();
    void setAdditionalDrawing( QPoint, ADDITIONAL_DRAWING );
private:
    GameWidget *gw;
    QVector<QPoint> pathVec;
    QVector<ADDITIONAL_DRAWING> pathParamsVec;
    DIRECTION dir;
    DIRECTION tailDir;
    QPoint lastPointBeforeTail;
    bool isRupture( QPoint, QPoint ) const;
    void updateDrawingVec();
};

#endif // SNAKE_H
