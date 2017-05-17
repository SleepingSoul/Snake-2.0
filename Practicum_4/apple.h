#ifndef APPLE_H
#define APPLE_H

#include "gameplayobject.h"
#include <QPoint>
#include <QImage>

class Apple : public GameplayObject {
public:
    Apple( GameWidget * );
    virtual ~Apple();
    void paintGameplayObject() override;
    QPoint getCoords();
    void setColorOffset( unsigned );
private:
    GameWidget *gw;
    QPoint coords;
    QBrush appleBrush;
    QImage blackHole;
    static unsigned count;
    unsigned colorOffset;
    unsigned startColorValue;
};

#endif // APPLE_H
