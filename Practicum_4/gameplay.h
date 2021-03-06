#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "state.h"
#include "gameplayobject.h"
#include "apple.h"
#include "wormhole.h"
#include "snake.h"

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
private slots:
    void gameStep();
    void holdingKey();
    void appleColorChange();
    void gameOverCapacity();
private:
    void gameOver();
    void pause();
    void continueGame();
    bool tryToMoveSnake() const;
    void updateFieldPoints();
    void createBasicGameplayObjects();
    void getAppleAndWormholeOnFreeSpace();
    void paintAllGameplayObjects();
    void paintPressEnterInGameOverState();
    Apple *getAppleOnFreeSpace();
    Wormhole *getWormholeOnFreeSpace();
    GameWidget *gw;
    QImage button_back;
    QImage button_pause;
    QImage button_continue;
    QImage game_over_image;
    GameplayObject *wall{ nullptr };
    GameplayObject *field{ nullptr };
    GameplayObject *snake{ nullptr };
    GameplayObject *apple{ nullptr };
    GameplayObject *wormhole{ nullptr };
    QTimer *timer;
    QTimer *timer4key;
    QTimer *timer4Apple;
    QTimer *timer4GameOver;
    unsigned points;
    unsigned keyAlreadyHoldedTime;
    unsigned colorAppleTime;
    unsigned gameOverCapacityNumber;
    QRect backRect;
    QRect pauseRect;
    const unsigned MAIN_INTERVAL;
    const unsigned BOOST_INTERVAL;
    const unsigned PUSHING_TIME;
    const unsigned COLOR_INTERVAL;
    bool gameIsOver;
    bool gamePaused;
    bool gameplayAlreadyStarted;
    bool keyAlreadyPressed;
    bool fieldPoints[ 32 ][ 22 ];
};

#endif // GAMEPLAY_H
