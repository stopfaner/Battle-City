#ifndef STATEGAME
#define STATEGAME

#include "States/state.h"

#include "Tanks/factory.h"
#include "Tanks/bullet.h"
#include "Tanks/botlogic.h"

#include "Helpers/collidable.h"
#include "Helpers/movable.h"

#include "GameField/map.h"
#include "GameField/fieldelement.h"

#include <QLineEdit>

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <random>

using namespace std;

class StateMenu;


class PaintBar {
private:
    int xPos;
    int yPos;

    GameWidget* widget;
    QRect* hpBar;
    QRect* coolDownBar;

    int counter = 0;

    BaseTank* tank;
    int tankHp;

    void paintInfo(QPainter* painter, int score) {
        painter->setPen(QColor(Qt::white));
        painter->setFont(QFont("Arial",25));

        std::string scoreBox= "Score: ";
        scoreBox += to_string(score * 100);

        painter->drawText(xPos + 35, 50, QString(scoreBox.c_str()));

        std::string hp = "HP: ";
        hp += to_string(tank->getHealthPoint());
        hp += "/";
        hp += to_string(tank->getMaxHealth());
        painter->drawText(xPos + 35, 480, QString(hp.c_str()));

        std::string power = "Power: ";
        power += to_string(((int)tank->getPower()));
        painter->drawText(xPos + 35, 530, QString(power.c_str()));

        std::string armor = "Armor: ";
        armor += to_string(((int)tank->getArmor()));
        painter->drawText(xPos + 35, 580, QString(armor.c_str()));

        std::string speed = "Speed: ";
        speed += to_string(((int)tank->getSpeed()));
        painter->drawText(xPos + 35, 630, QString(speed.c_str()));
    }
public:
    PaintBar(GameWidget* widget, BaseTank* tank) {
        this->widget = widget;
        this->tank = tank;
        this->xPos = widget->size().width()  - 320;
        this->tankHp = tank->getHpPersent();

        hpBar = new QRect(QPoint(xPos + 35, 370), QSize(250, 20));
        coolDownBar = new QRect(QPoint(xPos + 35, 410), QSize(0, 20));
    }

    void paint(QPainter* painter, int score) {
        counter++;
        tankHp = tank->getHpPersent();
        painter->drawPixmap(xPos + 35, 100, tank->getDownPixmap());
        coolDownBar->setWidth(tank->getCoolDown() > 100 ? 250 : 2.5 * tank->getCoolDown());
        hpBar->setWidth(tank->getHpPersent() >= 0 ? tank->getHpPersent() * 2.5 : 0);
        QBrush hpBrush(Qt::red);
        QBrush coolBrush(QColor(247, 206, 42));
        painter->fillRect(*hpBar, hpBrush);
        painter->fillRect(*coolDownBar, coolBrush);

        paintInfo(painter, score);
    }
};

class StateGame : public State {

private:
    QPainter* painter;
    GameWidget* widget;

    int enemiesSpawn;
    int deadCount = 0;
    int score = 0;
    bool covered = false;

    PaintBar* paintBar;

    Map* map;
    FieldElement** elements;
    int** elMatrix;

    BaseTank* myTank;
    TankType myType;

    vector<Bullet> bullets;

    vector<BaseTank*> enemies;
    vector<BotLogic*> logic;

    QLineEdit* edit;
    bool pauseMode = false;

    StateGame(GameWidget* widget, TankType type) {
        this->widget = widget;
        myType = type;
        srand(time(0));
        enemiesSpawn = rand() % 3;

        myTank = Factory::makeTank(myType);

        map = new Map();
        elMatrix = map->getMatrix();

        paintBar = new PaintBar(widget, myTank);

        edit = new QLineEdit("", widget);
        edit->setStyleSheet("QLineEdit { background: rgb(0, 255, 255); selection-background-color: rgb(233, 99, 0); }");
        edit->move(widget->size().width()/2 - 80, 500);

        spawnEnemies();
    }

    ~StateGame() {
        delete edit;
    }

    void setMenuState();

public:

    static State* getInstance(GameWidget* widget, TankType type) {
        return new StateGame(widget, type);
    }

    void keyPress(QKeyEvent* event) {
        //TODO:work here with server
        bool collideIs = false;
        switch(event->key()) {
            case Qt::Key_Left :
                if(!pauseMode) {
                    collideIs = getCollision(TankDirection::LEFT, *myTank);
                    if(!collideIs)
                        collideIs = getTankCollision(TankDirection::LEFT, *myTank);

                    myTank->leftPressed(collideIs);
                }
                break;
            case Qt::Key_Right :
                if(!pauseMode){
                    collideIs = getCollision(TankDirection::RIGHT, *myTank);
                    if(!collideIs)
                        collideIs = getTankCollision(TankDirection::RIGHT, *myTank);
                    myTank->rightPressed(collideIs);
                }
                break;
            case Qt::Key_Up :
                if(!pauseMode) {
                    collideIs = getCollision(TankDirection::UP, *myTank);
                    if(!collideIs)
                        collideIs = getTankCollision(TankDirection::UP, *myTank);
                    myTank->upPressed(collideIs);
                }
                break;
            case Qt::Key_Down :
                if(!pauseMode) {
                    collideIs = getCollision(TankDirection::DOWN, *myTank);
                    if(!collideIs)
                        collideIs = getTankCollision(TankDirection::DOWN, *myTank);
                    myTank->downPressed(collideIs);
                }
                break;
            case Qt::Key_Space :
                if(!pauseMode) {
                    if(myTank->isCoolDown())
                        bullets.push_back(myTank->spacePressed());
                }
                break;
            case Qt::Key_Escape:
                pauseMode = true;
            break;
        case Qt::Key_Return:
                pauseMode = false;
            break;
        }

    }
    void mousePress(QMouseEvent* event) {
        if(event->button() == Qt::LeftButton && covered) {
            if(edit->text().toStdString() != "") {
                writeResult(edit->text().toStdString(), deadCount * 100);
                widget->setState(StateType::RATINGS_STATE);
                delete edit;
            }
        }
    }

    void paint() {
        painter = new QPainter(widget);
        widget->setStyleSheet("background-color:black;");

        painter->setPen(QColor(Qt::white));
        painter->setFont(QFont("Arial",25));
        painter->drawText(widget->size().width() - 285,
                          widget->size().height() - 100,
                          pauseMode ? "Pause mode" : "Play mode");

        renderMap();
        renderMine();
        renderBullets();
        paintBarSide();
        renderEnemies();

    }

    void renderMine() {
        if(myTank->getHealthPoint() <= 0)
            paintLoose();
        painter->drawPixmap(myTank->getXpoz(), myTank->getYpoz(), myTank->getWidth(), myTank->getHeight(), myTank->getSprite());
    }

    void renderMap() {
        elements = map->getField();
        for(int i = 0; i < map->getRowCount(); i++) {
            for(int j = 0; j < map->getColCount(); j++) {
                painter->drawPixmap(elements[i][j].getXpoz(),
                                    elements[i][j].getYpoz(),
                                    elements[i][j].getPixmap().scaled(80, 80));
            }
        }
    }

    void renderBullets() {
        if(bullets.size() != 0)
            for(int i = 0; i < bullets.size(); i++) {
                if(bullets[i].isDeleted()){
                    bullets.erase(bullets.begin() + i);
                    continue;
                }
                int size = bullets[i].getWidth();
                painter->drawPixmap(bullets[i].getXpoz(), bullets[i].getYpoz(),
                                    bullets[i].getBullet().scaled(size, size));
                bool collide = false;
                collide = getBulletCollision(*myTank, bullets[i]);
                if(!collide) {
                    for(int j = 0; j < enemies.size(); j++) {
                        if(collide = getBulletCollision(*enemies[j], bullets[i]))
                            break;
                    }
                }
                if(!collide)
                    collide = getCollision(bullets[i].getTankDirection(), bullets[i]);
                if(!pauseMode)
                    bullets[i].updatePosition(collide);
            }
    }

    void renderEnemies() {
        bool allDead = true;
        int dead = 0;
        for(int i = 0; i < logic.size(); i++) {
            if(!logic[i]->getIsDestroyed()) {
                allDead = false;
                break;
            }
        }
        if(enemies.size() != 0) {
            for(int i = 0; i < enemies.size(); i++) {
                BaseTank* tank = enemies[i];

                painter->drawPixmap(tank->getXpoz(), tank->getYpoz(), tank->getSprite().scaled(80, 80));

                BotLogic* current = logic[i];
                if(!current->getIsDestroyed()) {
                    bool collide = getCollision(tank->getDirection(), *tank);
                    if(!collide)
                        collide = getEnemiesCollision(i);


                    if(!collide)
                        switch(tank->getDirection()) {
                            case TankDirection::LEFT:
                                collide = checkLeftCollision(*tank, *myTank);
                                break;
                            case TankDirection::RIGHT:
                                collide = checkRightCollision(*tank, *myTank);
                                break;
                            case TankDirection::UP:
                                collide = checkUpCollision(*tank, *myTank);
                                break;
                            case TankDirection::DOWN:
                                collide = checkDownCollision(*tank, *myTank);
                                break;
                        }
                    if(!pauseMode)
                        current->updateCondition(collide, bullets);
                } else
                    dead++;
            }
            deadCount = dead;
        }
        if(allDead)
            paintVictory();
    }

    bool getBulletCollision(BaseTank& tank, Bullet& bullet) {
        TankDirection type = bullet.getTankDirection();
        switch(type) {
            case TankDirection::LEFT:
                if(checkLeftCollision(bullet, tank)) {
                    tank.setHealthPoint(tank.getHealthPoint() - bullet.getBulletPower() + tank.getArmor());
                    return true;
                }
                break;
            case TankDirection::RIGHT:
                if(checkRightCollision(bullet, tank)){
                    tank.setHealthPoint(tank.getHealthPoint() - bullet.getBulletPower() + tank.getArmor());
                    return true;
                }
                break;
            case TankDirection::UP:
                if(checkUpCollision(bullet, tank)){
                    tank.setHealthPoint(tank.getHealthPoint() - bullet.getBulletPower() + tank.getArmor());
                    return true;
                }
                break;
            case TankDirection::DOWN:
                if(checkDownCollision(bullet, tank)){
                    tank.setHealthPoint(tank.getHealthPoint() - bullet.getBulletPower() + tank.getArmor());
                    return true;
                }
                break;
        }

        return false;
    }

    bool getEnemiesCollision(int j) {
        for(int i = 0; i < enemies.size(); i++) {
            if(i != j) {
                switch(enemies[j]->getDirection()) {
                    case TankDirection::LEFT:
                        if(checkLeftCollision(*enemies[j], *enemies[i])) {
                            return true;
                        }
                        break;
                    case TankDirection::RIGHT:
                        if(checkRightCollision(*enemies[j], *enemies[i]))
                            return true;
                        break;
                    case TankDirection::UP:
                        if(checkUpCollision(*enemies[j], *enemies[i]))
                            return true;
                        break;
                    case TankDirection::DOWN:
                        if(checkDownCollision(*enemies[j], *enemies[i]))
                            return true;
                        break;
                }
            }
        }
        return false;
    }

    bool getTankCollision(TankDirection type, Movable& movable) {
        for(int i = 0; i < enemies.size(); i++) {
            switch(type) {
                case TankDirection::LEFT:
                    if(checkLeftCollision(movable, *enemies[i])) {
                        return true;
                    }
                    break;
                case TankDirection::RIGHT:
                    if(checkRightCollision(movable, *enemies[i]))
                        return true;
                    break;
                case TankDirection::UP:
                    if(checkUpCollision(movable, *enemies[i]))
                        return true;
                    break;
                case TankDirection::DOWN:
                    if(checkDownCollision(movable, *enemies[i]))
                        return true;
                    break;
            }
        }
        return false;
    }

    bool getCollision(TankDirection type, Movable& movable) {
        for(int i = 0; i < map->getRowCount(); i++) {
            for(int j = 0; j < map->getColCount(); j++) {
                if(elements[i][j].getType() != FieldType::GROUND) {
                    switch(type) {
                        case TankDirection::LEFT:
                            if(checkLeftCollision(movable, elements[i][j]))
                                return true;
                            break;
                        case TankDirection::RIGHT:
                            if(checkRightCollision(movable, elements[i][j]))
                                return true;
                            break;
                        case TankDirection::UP:
                            if(checkUpCollision(movable, elements[i][j]))
                                return true;
                            break;
                        case TankDirection::DOWN:
                            if(checkDownCollision(movable, elements[i][j]))
                                return true;
                            break;
                    }
                }
            }
        }
        return false;
    }

    bool checkLeftCollision(Movable& tank, Collidable& element) {
        int movableXpoz = tank.getXpoz();
        int movableYpoz = tank.getYpoz();
        int movableSize = tank.getHeight();

        int elementXpoz = element.getXpoz();
        int elementYpoz = element.getYpoz();
        int elementSize;
        elementSize = element.getHeight();

        if(movableYpoz + 1> elementYpoz + elementSize)
            return false;
        if(movableYpoz + movableSize - 1< elementYpoz)
            return false;
        if(movableXpoz + movableSize < elementXpoz)
            return false;
        if(movableXpoz <= elementXpoz + elementSize &&
                movableXpoz + movableSize - elementXpoz > 0) {
            return true;
        }
        return false;
    }

    bool checkRightCollision(Movable& tank, Collidable& element) {
        int movableXpoz = tank.getXpoz();
        int movableYpoz = tank.getYpoz();
        int movableSize = tank.getHeight();

        int elementXpoz = element.getXpoz();
        int elementYpoz = element.getYpoz();
        int elementSize;
        elementSize = element.getHeight();

        if(movableYpoz + 1> elementYpoz + elementSize)
            return false;
        if(movableYpoz + movableSize - 1 < elementYpoz)
            return false;
        if(movableXpoz > elementXpoz + elementSize)
            return false;
        if(movableXpoz + movableSize >= elementXpoz &&
                elementXpoz - movableXpoz + movableSize > 0)
            return true;

        return false;
    }

    bool checkUpCollision(Movable& movable, Collidable& element) {
        int movableXpoz = movable.getXpoz();
        int movableYpoz = movable.getYpoz();
        int movableSize = movable.getHeight();

        int elementXpoz = element.getXpoz();
        int elementYpoz = element.getYpoz();
        int elementSize;
        elementSize = element.getHeight();

        if(movableXpoz + 1> elementXpoz + elementSize)
            return false;
        if(movableXpoz + movableSize - 1 < elementXpoz)
            return false;
        if(movableYpoz + movableSize < elementYpoz)
            return false;
        if(movableYpoz <= elementYpoz + elementSize &&
                movableYpoz + movableSize - elementYpoz > 0)
            return true;

        return false;
    }

    bool checkDownCollision(Movable& tank, Collidable& element) {
        int movableXpoz = tank.getXpoz();
        int movableYpoz = tank.getYpoz();
        int movableSize = tank.getHeight();

        int elementXpoz = element.getXpoz();
        int elementYpoz = element.getYpoz();
        int elementSize;
        elementSize = element.getHeight();

        if(movableXpoz + 1 > elementXpoz + elementSize)
            return false;
        if(movableXpoz + movableSize - 1 < elementXpoz)
            return false;
        if(movableYpoz > elementYpoz + elementSize)
            return false;
        if(movableYpoz + movableSize >= elementYpoz &&
                elementYpoz - movableYpoz + movableSize > 0)
            return true;
        return false;
    }

    void paintBarSide() {
        paintBar->paint(painter, deadCount);
    }
    void spawnEnemies() {
        for(int i = 0; i < 2 ; i++) {
            BaseTank* tank = spawn();
            enemies.push_back(tank);
            logic.push_back(new BotLogic(tank));
        }
    }

    BaseTank* spawn() {
        int xPoz = rand() % map->getColCount();
        int yPoz = rand() % map->getRowCount();
        int type = rand() % 4;
        TankType tankType;

        if(elMatrix[yPoz][xPoz] != 0)
            return spawn();

        switch(type) {
            case 1:
                tankType = TankType::LIGHT;
                break;
            case 2:
                tankType = TankType::MEDIUM;
                break;
            case 3:
                tankType = TankType::HARD;
                break;
            default:
                return spawn();
        }

        BaseTank* tank;
        tank = Factory::makeTank(tankType);
        tank->setXpoz(xPoz * Map::BLOCK_SIZE);
        tank->setYpoz(yPoz * Map::BLOCK_SIZE);

        for(int i = 0; i < enemies.size(); i++) {
            if(enemies[i]->getXpoz() == tank->getXpoz() &&
                    enemies[i]->getYpoz() == tank->getYpoz())
                return spawn();
        }
        return tank;
    }

    void writeResult(std::string playerName, int score) {
        ofstream of("C:\\Users\\Denys\\Documents\\Tanks\\rating.dat", ios::app);
        of<<playerName<<" "<<score<<endl;
        of.close();
    }

    void paintLoose() {
        painter->drawPixmap(0, 0, QPixmap(":/images/looser.png").scaled(widget->size()));
        QPixmap save(":/images/save.png");
        QPixmap save_c(":/images/save_c.png");
        QCursor* cursor;
        QPoint point = widget->mapFromGlobal(cursor->pos());
        if(point.rx() >= widget->size().width()/2 - save.size().width()/2 &&
                point.rx() <= widget->size().width()/2 + save.size().width()/2 &&
                    point.ry() >= 550 && point.ry() <= 550 + save.size().height())
            covered = true;

        painter->drawPixmap(widget->size().width()/2 - save.size().width()/2, 550, covered ? save_c : save);

        if(!pauseMode){
            edit->show();
            pauseMode = true;
        }
    }

    void paintVictory() {
        QRect* whiteScr = new QRect(QPoint(0, 0), QSize(1920, 1080));
        QBrush brush(Qt::white);
        painter->fillRect(*whiteScr, brush);
        QPixmap victory(":/images/victory.jpg");
        painter->drawPixmap(widget->size().width()/2 - victory.size().width()/2, 200, victory);

        QPixmap save(":/images/save.png");
        QPixmap save_c(":/images/save_c.png");
        QCursor* cursor;
        QPoint point = widget->mapFromGlobal(cursor->pos());
        if(point.rx() >= widget->size().width()/2 - save.size().width()/2 &&
                point.rx() <= widget->size().width()/2 + save.size().width()/2 &&
                    point.ry() >= 550 && point.ry() <= 550 + save.size().height())
            covered = true;

        painter->drawPixmap(widget->size().width()/2 - save.size().width()/2, 550, covered ? save_c : save);

        if(!pauseMode){
            edit->show();
            pauseMode = true;
        }
    }
};


#endif // STATEGAME

