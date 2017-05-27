#ifndef RESULTS_H
#define RESULTS_H

#include "state.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

using std::ios;
using std::endl;
using std::ofstream;
using std::ifstream;

class Results : public State {
public:
    Results( class GameWidget * );
    Results( class GameWidget *, unsigned );
    virtual ~Results();
    void paint() override;
    void mouseReleased( QMouseEvent * ) override;
    void keyPressed( QKeyEvent * ) override;
    void setPoints( unsigned );

    // useless in this class:
    void nextState() override {}
    void keyReleased( QKeyEvent * ) override {}
private:
    GameWidget *gw;
    QImage button_back;
    QImage name_field_image;
    QString nickname;
    ofstream outResultsFile;
    ifstream inResultsFile;
    unsigned points;
    unsigned offset;
    bool nicknameEntered;
};

#endif // RESULTS_H
