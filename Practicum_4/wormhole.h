#ifndef WORMHOLE_H
#define WORMHOLE_H

#include "gameplayobject.h"

class Wormhole : public GameplayObject {
public:
    Wormhole( GameWidget * );
    virtual ~Wormhole();
    void paintGameplayObject() override;
    QPoint getCoords() const;
private:
    GameWidget *gw;
    QImage wormholeImage;
    QPoint coords;
};

#endif // WORMHOLE_H
