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
private:
    GameWidget *gw;
    QPoint coords;
    QBrush appleBrush;
    static unsigned count;
};

#endif // APPLE_H
