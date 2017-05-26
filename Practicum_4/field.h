#ifndef FIELD_H
#define FIELD_H
#define FIELD_WIDTH 32
#define FIELD_HEIGHT 22

#include "gameplayobject.h"

class Field : public GameplayObject {
public:
    Field( GameWidget * );
    virtual ~Field();
    void paintGameplayObject() override;
private:
    GameWidget *gw;
    QImage fieldImage;
    QPoint southwestPoint;
    QPoint northwestPoint;
    QPoint northeastPoint;
    QPoint southeastPoint;
    unsigned height{ FIELD_HEIGHT };
    unsigned width{ FIELD_WIDTH };
};

#endif // FIELD_H
