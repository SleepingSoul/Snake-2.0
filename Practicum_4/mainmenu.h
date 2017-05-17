#ifndef MAINMENU_H
#define MAINMENU_H

#include "state.h"
#include <QTimer>
#include <QString>
#include <QRect>

class MainMenu : public State {
    Q_OBJECT
public:
    MainMenu( class GameWidget * );
    virtual ~MainMenu();
    void paint() override;
    void nextState() override;
    void mouseReleased( QMouseEvent * ) override;
    void keyPressed( QKeyEvent * ) override {}
    void keyReleased( QKeyEvent * ) override {}
public slots:
    void btnloading();
private:
    GameWidget *gw;
    QImage button_newgame;
    QImage button_results;
    QImage button_exit;
    QRect rect_newgame;
    QRect rect_results;
    QRect rect_exit;
    QTimer *timer;
    unsigned load;
    unsigned oscillationCount_newgame;
    unsigned oscillationCount_results;
    unsigned oscillationCount_exit;
    unsigned coeff_newgame;
    unsigned coeff_results;
    unsigned coeff_exit;
};

#endif // MAINMENU_H
