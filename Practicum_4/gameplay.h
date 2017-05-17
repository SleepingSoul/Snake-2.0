#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <state.h>
#include <QTimer>
#include "gameplayobject.h"

class Gameplay : public State {
    Q_OBJECT
public:
    Gameplay( class GameWidget * );
    virtual ~Gameplay();
    void paint() override;
    void nextState() override;
    void mouseReleased( QMouseEvent * ) override;
    void keyPressed( QKeyEvent * ) override;
    void keyReleased( QKeyEvent * ) override;
public slots:
    void gameStep();
    void holdingKey();
private:
    void gameOver();
    void pause();
    void continueGame();
    GameWidget *gw;
    QImage button_back;
    QImage button_pause;
    QImage button_continue;
    GameplayObject *wall{ nullptr };
    GameplayObject *field{ nullptr };
    GameplayObject *snake{ nullptr };
    GameplayObject *apple{ nullptr };
    QTimer *timer;
    QTimer *timer4key;
    QTimer *speedMovingTimer;
    unsigned points;
    unsigned keyAlreadyHoldedTime;
    QRect backRect;
    QRect pauseRect;
    bool keyAlreadyPressed;
    const unsigned MAIN_INTERVAL;
    const unsigned BOOST_INTERVAL;
    const unsigned PUSHING_TIME;
    const unsigned FAST_INTERVAL;
    bool gameIsOver;
    bool gamePaused;
};

#endif // GAMEPLAY_H