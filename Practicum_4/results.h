#ifndef RESULTS_H
#define RESULTS_H

#include "state.h"

class Results : public State {
public:
    Results( class GameWidget * );
    virtual ~Results();
    void paint() override;
    void mouseReleased( QMouseEvent * ) override;

    // useless in this class:
    void nextState() override {}
    void keyPressed( QKeyEvent * ) override {}
    void keyReleased( QKeyEvent * ) override {}
private:
    GameWidget *gw;
    QImage button_back;
};

#endif // RESULTS_H
