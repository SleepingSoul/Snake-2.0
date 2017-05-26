#ifndef SNAKE_H
#define SNAKE_H

#include "gameplayobject.h"

enum DIRECTION{ FORWARD = 0, BACKWARD, LEFT, RIGHT };
enum ADDITIONAL_DRAWING{ NOTHING = 0, DRAW_APPLE, DRAW_WORMHOLE };

class Snake : public GameplayObject {
public:
    Snake( GameWidget * );
    virtual ~Snake();
    void paintGameplayObject() override; // non-const because of call of "update drawing vec"
    void changeDirection( DIRECTION );
    DIRECTION getDirection() const;
    void move();
    void move( QPoint );
    QPoint getHead() const;
    QVector<QPoint> getSnake() const;
    void grow();
    void setAdditionalDrawing( QPoint, ADDITIONAL_DRAWING );
private:
    GameWidget *gw;
    QImage wormholeImage;
    QImage appleImage;
    QVector<QPoint> pathVec;
    QVector<ADDITIONAL_DRAWING> pathParamsVec;
    DIRECTION dir;
    DIRECTION tailDir;
    QPoint lastPointBeforeTail;
    bool isRupture( const QPoint, const QPoint ) const;
    void updateDrawingVec();
};

#endif // SNAKE_H
