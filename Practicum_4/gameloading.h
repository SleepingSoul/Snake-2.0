#ifndef GAMELOADING_H
#define GAMELOADING_H

#include <state.h>
#include <QTimer>

class GameLoading : public State {
    Q_OBJECT
public:
    GameLoading( class GameWidget * );
    virtual ~GameLoading();
    void paint() override;
    void nextState() override;
    void mouseReleased( QMouseEvent * ) override {}
    void keyPressed( QKeyEvent * ) override {};
    void keyReleased( QKeyEvent * ) override {}
public slots:
    void loading();
private:
    GameWidget *gw;
    unsigned load;
    QTimer *timer;
};

#endif // GAMELOADING_H
