#ifndef STATEMENU
#define STATEMENU

#include "States/state.h"
#include "States/stategame.h"
#include "States/stateratings.h"
#include "States/stateoptions.h"
#include "States/stateabout.h"

#include <QCursor>
#include <QPoint>

class StateGame;

class StateMenu : public State {

private:
    enum Covered {
        Start, Options, Ratings, About, Exit,
        Start_Single, Start_Server,
        Light_Tank, Middle_Tank, Hard_Tank,
        None
    };

    QPainter* painter;
    GameWidget* widget;
    QCursor* cursor;

    Covered coveredButton;
    TankType choosen = NONE;

    bool buttonCovered = false;
    bool playMenu = false;

    int xPaintCoord;
    int yPaintCoord;
    int xDeltaCoord;
    int yDeltaCoord;

    StateMenu(GameWidget* widget) {
        this->widget = widget;
        coveredButton = None;
        cursor = new QCursor();

        xPaintCoord = this->widget->width()/2 - QPixmap(":/images/menu/start_active.png").width()/2;
        yPaintCoord = this->widget->height() / 3;
        xDeltaCoord = QPixmap(":/images/menu/start_active.png").width();
        yDeltaCoord = QPixmap(":/images/menu/start_active.png").height();
    }

    void paintPlayMenu() {

        coveredButton = getCovered();

        painter->drawPixmap(xPaintCoord, widget->height() / 3 + -1 * yDeltaCoord,
                            coveredButton == Start_Single ?
                                QPixmap(":/images/menu/start_active.png"):
                                QPixmap(":/images/menu/start_non_active.png"));
        painter->drawPixmap(xPaintCoord, widget->height() / 3 + 0.2 * yDeltaCoord,
                            coveredButton == Start_Server ?
                                QPixmap(":/images/menu/options_active.png"):
                                QPixmap(":/images/menu/options_non_active.png"));

        painter ->drawPixmap(widget->width() / 2 - 200, widget->height() / 2,
                             coveredButton == Light_Tank || choosen == TankType::LIGHT ?
                                 QPixmap(":/tanksprites/light_tank_down.png").scaled(125, 125):
                                 QPixmap(":/tanksprites/light_tank_grey.png").scaled(125, 125));
        painter ->drawPixmap(widget->width() / 2 - 50, widget->height() / 2,
                             coveredButton == Middle_Tank || choosen == TankType::MEDIUM ?
                                 QPixmap(":/tanksprites/middle_tank_down.png").scaled(125, 125):
                                 QPixmap(":/tanksprites/middle_tank_grey.png").scaled(125, 125));
        painter ->drawPixmap(widget->width() / 2 + 100, widget->height() / 2,
                             coveredButton == Hard_Tank || choosen == TankType::HARD ?
                                 QPixmap(":/tanksprites/hard_tank_down.png").scaled(125, 125):
                                 QPixmap(":/tanksprites/hard_tank_grey.png").scaled(125, 125));
    }

    void paintMainMenu() {

        coveredButton = getCovered();

        painter->drawPixmap(xPaintCoord, widget->height() / 3 + 0 * yDeltaCoord,
                            coveredButton == Start ?
                                QPixmap(":/images/menu/start_active.png"):
                                QPixmap(":/images/menu/start_non_active.png"));
        painter->drawPixmap(xPaintCoord, widget->height() / 3 + 1.2 * yDeltaCoord,
                            coveredButton == Options ?
                                QPixmap(":/images/menu/options_active.png"):
                                QPixmap(":/images/menu/options_non_active.png"));
        painter->drawPixmap(xPaintCoord, widget->height() / 3 + 2.4 * yDeltaCoord,
                            coveredButton == Ratings ?
                                QPixmap(":/images/menu/ratings_active.png"):
                                QPixmap(":/images/menu/ratings_non_active.png"));
        painter->drawPixmap(xPaintCoord, widget->height() / 3 + 3.6 * yDeltaCoord,
                            coveredButton == About ?
                                QPixmap(":/images/menu/about_active.png"):
                                QPixmap(":/images/menu/about_non_active.png"));
        painter->drawPixmap(xPaintCoord, widget->height() / 3 + 4.8 * yDeltaCoord,
                            coveredButton == Exit ?
                                QPixmap(":/images/menu/exit_active.png"):
                                QPixmap(":/images/menu/exit_non_active.png"));
    }

    Covered getCovered() {
        QPoint point = widget->mapFromGlobal(cursor->pos());
        if(!playMenu) {
            if(point.rx() > xPaintCoord && point.rx() < xPaintCoord + xDeltaCoord) {
                if(point.ry() > yPaintCoord && point.ry() < yPaintCoord + yDeltaCoord)
                    return Start;
                if(point.ry() > yPaintCoord + 1.2 * yDeltaCoord &&
                        point.ry() < yPaintCoord + 2.2 * yDeltaCoord)
                    return Options;
                if(point.ry() > yPaintCoord + 2.4 * yDeltaCoord &&
                        point.ry() < yPaintCoord + 3.4 * yDeltaCoord)
                    return Ratings;
                if(point.ry() > yPaintCoord + 3.6 * yDeltaCoord &&
                        point.ry() < yPaintCoord + 4.6 * yDeltaCoord)
                    return About;
                if(point.ry() > yPaintCoord + 4.8 * yDeltaCoord &&
                        point.ry() < yPaintCoord + 5.8 * yDeltaCoord)
                    return Exit;
            }
        } else {
            if(point.rx() > xPaintCoord && point.rx() < xPaintCoord + xDeltaCoord) {
                if(point.ry() > yPaintCoord - yDeltaCoord
                        && point.ry() < yPaintCoord)
                    return Start_Single;
                if(point.ry() > yPaintCoord + 0.2 * yDeltaCoord
                        && point.ry() < yPaintCoord + 1.2 * yDeltaCoord)
                    return Start_Server;
            }
            if(point.ry() > widget->height() / 2 && point.ry() < widget->height() / 2 + 125) {
                if(point.rx() > widget->width() / 2 - 200 && point.rx() < widget->width() / 2 - 75)
                    return Light_Tank;
                if(point.rx() > widget->width() / 2 - 50 && point.rx() < widget->width() / 2 + 75)
                    return Middle_Tank;
                if(point.rx() > widget->width() / 2 + 100 && point.rx() < widget->width() / 2 + 225)
                    return Hard_Tank;
            }
        }
        return None;
    }

public:

    static State* getInstance(GameWidget* widget) {
        return new StateMenu(widget);
    }

    void keyPress(QKeyEvent* event) {
        if(event->key() == Qt::Key_Escape && !playMenu) {
                finishGame();
        }
        if(event->key() == Qt::Key_Escape && playMenu) {
            widget->setState(StateType::MENU_STATE);
        }
    }
    void mousePress(QMouseEvent* event) {
        if(event->button() == Qt::LeftButton) {
            switch (coveredButton) {
                case Start:
                    playMenu = true;
                    break;
                case Options:
                    setOptionsState();
                    break;
                case Ratings:
                    setRatingsState();
                    break;
                case About:
                    setAboutState();
                    break;
                case Exit:
                    delete widget;
                //Play Meny=u
                case Start_Single:
                    setGameState();
                    break;
                case Start_Server:
                    break;
                case Light_Tank:
                    choosen = TankType::LIGHT;
                    break;
                case Middle_Tank:
                    choosen = TankType::MEDIUM;
                    break;
                case Hard_Tank:
                    choosen = TankType::HARD;
                    break;
            }
        }
    }

    void paint() {
        painter = new QPainter(widget);
        widget->setStyleSheet("background-color:black;");
        painter->drawPixmap(0, 0, QPixmap(":/images/menubackground.png").scaled(widget->size()));

        playMenu ? paintPlayMenu() : paintMainMenu();
    }

    void setGameState() {
        if(choosen != NONE) {
            widget->setState(StateType::GAME_STATE, choosen);
        }
    }

    void setRatingsState() {
        widget->setState(StateType::RATINGS_STATE);
    }

    void setOptionsState() {
        widget->setState(StateType::OPTIONS_STATE);
    }

    void setAboutState() {
        widget->setState(StateType::ABOUT_STATE);
    }

    void finishGame() {
        delete widget;
    }
};


#endif // STATEMENU

