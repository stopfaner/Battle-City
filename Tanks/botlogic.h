#ifndef BOTLOGIC
#define BOTLOGIC

#include "Tanks/basetank.h"
#include "Helpers/log.h"

#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

class BotLogic {

private:
    BaseTank* enemy;

    int xPoz;
    int yPoz;

    bool isDestroyed;

public:
    BotLogic() {

    }

    BotLogic(BaseTank* enemy) {
        this->enemy = enemy;

        isDestroyed = false;

        xPoz = enemy->getXpoz();
        yPoz = enemy->getYpoz();
    }

    void setEnemy(BaseTank* enemy) {
        this->enemy = enemy;
    }

    bool getIsDestroyed() {
        return isDestroyed;
    }

    void updateCondition(bool collide, vector<Bullet>& bullets) {
        if(enemy->getHealthPoint() <= 0 && !isDestroyed) {
            isDestroyed = true;
        }
        switch(enemy->getDirection()) {
            case TankDirection::LEFT :
                if(enemy->getHealthPoint() > 0) {
                    if(!collide) {
                        enemy->setXpoz(enemy->getXpoz() - enemy->getSpeed() / 30);
                    }
                    else {
                        xPoz = enemy->getYpoz();
                        yPoz = enemy->getYpoz();
                        changeDirection(enemy->getDirection());
                    }
                }
                break;
            case TankDirection::RIGHT :
                if(enemy->getHealthPoint() > 0) {
                    if(!collide) {
                        enemy->setXpoz(enemy->getXpoz() + enemy->getSpeed() / 30);
                    }
                    else {
                        xPoz = enemy->getYpoz();
                        yPoz = enemy->getYpoz();
                        changeDirection(enemy->getDirection());
                    }
                }
                break;
            case TankDirection::UP :
                if(enemy->getHealthPoint() > 0) {
                    if(!collide) {
                        enemy->setYpoz(enemy->getYpoz() - enemy->getSpeed() / 30);
                    }
                    else {
                        xPoz = enemy->getYpoz();
                        yPoz = enemy->getYpoz();
                        changeDirection(enemy->getDirection());
                    }
                }
                break;
            case TankDirection::DOWN :
                if(enemy->getHealthPoint() > 0) {
                    if(!collide) {
                        enemy->setYpoz(enemy->getYpoz() + enemy->getSpeed() / 30);
                    }
                    else {
                        xPoz = enemy->getYpoz();
                        yPoz = enemy->getYpoz();
                        changeDirection(enemy->getDirection());
                    }
                }
                break;
        }
        if(enemy->isCoolDown() && enemy->getHealthPoint() > 0)
            bullets.push_back(enemy->spacePressed());

    }

    void changeDirection(TankDirection current) {
        int direction = rand() % 5;
        switch(direction) {
            case 1:
                enemy->setDirection(TankDirection::LEFT);
                break;
            case 2:
                enemy->setDirection(TankDirection::RIGHT);
                break;
            case 3:
                enemy->setDirection(TankDirection::UP);
                break;
            case 4:
                enemy->setDirection(TankDirection::DOWN);
                break;
            default:
                changeDirection(current);
        }
    }

};


#endif // BOTLOGIC

