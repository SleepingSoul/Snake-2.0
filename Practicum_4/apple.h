#ifndef APPLE_H
#define APPLE_H

#include "gameplayobject.h"

class Apple : public GameplayObject {
public:
    Apple( GameWidget * );
    virtual ~Apple();
    void paintGameplayObject() override;
    QPoint getCoords() const;
    void setCoords( QPoint );
    void setColorOffset( unsigned );
private:
    GameWidget *gw;
    QPoint coords;
    QBrush appleBrush;
    QImage blackHole;
    unsigned colorOffset;
    unsigned startColorValue;
};

#endif // APPLE_H
