#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H


#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

#include "Helpers/gameconstants.h"
#include "States/state.h"

class StateFactory {
public:
    static State* makeState(GameWidget* widget, StateType stateType, TankType tankType);
};

class GameWidget : public QWidget {
    Q_OBJECT
private:
    int counter = 0;
    QTimer* timer;
    State* state;
public:
    GameWidget(QWidget *parent = 0);

    //Paining methods to paint loading and menu screens
    void paintEvent(QPaintEvent* paintEvent);
    //Handle callbacks
    void keyPressEvent(QKeyEvent* event);
    //void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);

    void setState(StateType type) {
        setState(type, NONE);
    }
    void setState(StateType type, TankType tank) {
        state = StateFactory::makeState(this, type, tank);
    }
};

#endif // GAMEWIDGET_H
