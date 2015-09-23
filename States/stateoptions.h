#ifndef STATEOPTIONS
#define STATEOPTIONS

#include "States/state.h"

class StateOptions : public State {

private:
    GameWidget* widget;
    QPainter* painter;

    StateOptions(GameWidget* widget) {
        this->widget = widget;
    }

public:
    static State* getInstance(GameWidget* widget) {
        return new StateOptions(widget);
    }

    void paint() {
        painter = new QPainter(widget);
        painter->drawPixmap(0, 0, QPixmap(":/images/menubackground.png").scaled(widget->size()));

        painter->setPen(QColor(Qt::white));
        painter->setFont(QFont("Arial",25));
    }

    void keyPress(QKeyEvent* event) {
        if(event->key() == Qt::Key_Escape)
            widget->setState(StateType::MENU_STATE);
    }

    void mousePress(QMouseEvent* event) {

    }


};

#endif // STATEOPTIONS

