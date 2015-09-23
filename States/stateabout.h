#ifndef STATEABOUT
#define STATEABOUT

#include "States/state.h"
#include "States/statemenu.h"

class StateAbout : public State {

private:

    GameWidget* widget;
    QPainter* painter;

    StateAbout(GameWidget* widget) {
        this->widget = widget;
    }

public:
    static State* getInstance(GameWidget* widget) {
        return new StateAbout(widget);
    }

    void paint() {
        painter = new QPainter(widget);
        painter->drawPixmap(0, 0, QPixmap(":/images/menubackground.png").scaled(widget->size()));

        painter->setPen(QColor(Qt::white));
        painter->setFont(QFont("Arial",25));

        painter->drawText(widget->size().width()/2 - 50, 200, "About");
        painter->drawText(widget->size().width()/2 - 250, 250, "The best tanks ever v.0.0.3");
        painter->drawText(widget->size().width()/2 - 220, 300, "Coding: Lytvinyuk Denys");
        painter->drawText(widget->size().width()/2 - 190, 350, "Design: Google.com");
        painter->drawText(widget->size().width()/2 - 300, 400, "System: 1024MB RAM, 2 core CPU");
        painter->drawText(widget->size().width()/2 - 250, 450, "512MB Video with Directx 11.0");

    }
    void keyPress(QKeyEvent* event) {
        if(event->key() == Qt::Key_Escape)
            widget->setState(StateType::MENU_STATE);
    }

    void mousePress(QMouseEvent* event) {

    }

    void setMenuState() {
    }


};

#endif // STATEABOUT

