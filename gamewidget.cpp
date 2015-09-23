#include "gamewidget.h"
#include "States/stateloading.h"
#include "States/statemenu.h"
#include "States/stategame.h"
#include "States/stateabout.h"
#include "States/stateoptions.h"
#include "States/stateratings.h"
#include "Helpers/gameconstants.h"

#include "Helpers/log.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {

    this->resize(1920, 1080);

    state = StateFactory::makeState(this, MENU_STATE, NONE);//StateMenu::getInstance(this);
    timer = new QTimer(this);
    connect(GameWidget::timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(17);
}

void GameWidget::paintEvent(QPaintEvent* paintEvent) {
        state->paint();
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
        state->keyPress(event);
}

void GameWidget::mousePressEvent(QMouseEvent* event) {
        state->mousePress(event);
}

State* StateFactory::makeState(GameWidget* widget, StateType tateType, TankType tankType) {

    switch(tateType) {
        case StateType::GAME_STATE :
            return StateGame::getInstance(widget, tankType);
            break;
        case StateType::LOADING_STATE :
            return StateLoading::getInstance(widget);
            break;
        case StateType::MENU_STATE :
            return StateMenu::getInstance(widget);
            break;
        case StateType::RATINGS_STATE :
            return StateRatings::getInstance(widget);
            break;
        case StateType::OPTIONS_STATE :
            return StateOptions::getInstance(widget);
            break;
        case StateType::ABOUT_STATE :
            return StateAbout::getInstance(widget);
            break;
    }
}
