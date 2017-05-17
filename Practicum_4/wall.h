#ifndef WALL_H
#define WALL_H

#include "gameplayobject.h"
#include <QPoint>

class Wall : public GameplayObject {
public:
    Wall( GameWidget * );
    virtual ~Wall();
    void paintGameplayObject() override;
    QVector<QPoint> getFronts();
private:
    GameWidget *gw;
    QPoint southwestPoint;
    QPoint northwestPoint;
    QPoint northeastPoint;
    QPoint southeastPoint;
};

#endif // WALL_H
