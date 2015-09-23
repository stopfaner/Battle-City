#ifndef BASETANK_H
#define BASETANK_H

#include "Helpers/gameconstants.h"
#include "Helpers/movable.h"
#include "Helpers/collidable.h"
#include "Tanks/bullet.h"

#include <vector>
#include <time.h>

using namespace std;

class BaseTank : public Collidable, public Movable {

protected:
    int serverId;

    //Tank coordinates
    int xPoz;
    int yPoz;
    //Picture parametrs
    int width;
    int height;
    //Tank images
    QPixmap tankSprite;
    QPixmap* tankSpriteLeft;
    QPixmap* tankSpriteRight;
    QPixmap* tankSpriteUp;
    QPixmap* tankSpriteDown;

    //Tank condition
    TankDirection direction;
    TankType type;
    int speed;
    int healthPoint;
    int currentHP;
    float armor;
    float power;

    float coolDown;
    bool isShot = false;
    clock_t shot;

    vector<Bullet> bullets;

public:

    BaseTank() {
        tankSpriteLeft = new QPixmap[4];
        tankSpriteRight = new QPixmap[4];
        tankSpriteUp = new QPixmap[4];
        tankSpriteDown = new QPixmap[4];
        serverId = 4;
        width = height = 80;
        xPoz = 160;
        yPoz = 160;
    }
    ~BaseTank() {}

    void setHealthPoint(float healthPoint) {
        this->healthPoint = healthPoint;
    }

    int getSpeed() { return speed; }
    int getHealthPoint() { return healthPoint; }
    int getMaxHealth() { return currentHP; }
    float getArmor() { return armor; }
    float getPower() { return power; }
    float getCoolDown() {
        clock_t reuse = clock() - shot;
        float persent = coolDown / 100;
        return reuse > 0 ? ((float)reuse)/CLOCKS_PER_SEC / persent : 101;
    }
    bool isCoolDown() {
        if(!isShot) return true;
        return getCoolDown() > 100 && getCoolDown() != 101;
    }
    int getXpoz() { return xPoz; }
    int getYpoz() { return yPoz; }
    int getWidth() { return width; }
    int getHeight() { return height; }

    TankDirection getDirection() {
        return direction;
    }

    QPixmap getSprite() {
        switch(direction) {
            case TankDirection::LEFT:
                if(this->currentHP - this->healthPoint == 0)
                    tankSprite = tankSpriteLeft[0];
                if(this->currentHP - this->healthPoint > 100)
                    tankSprite = tankSpriteLeft[1];
                if(this->currentHP - this->healthPoint > 300)
                    tankSprite = tankSpriteLeft[2];
                if(this->currentHP - this->healthPoint >= this->currentHP)
                    tankSprite = tankSpriteLeft[3];
                break;
            case TankDirection::RIGHT:
                if(this->currentHP - this->healthPoint == 0)
                    tankSprite = tankSpriteRight[0];
                if(this->currentHP - this->healthPoint > 100)
                    tankSprite = tankSpriteRight[1];
                if(this->currentHP - this->healthPoint > 300)
                    tankSprite = tankSpriteRight[2];
                if(this->currentHP - this->healthPoint >= this->currentHP)
                    tankSprite = tankSpriteRight[3];
                break;
            case TankDirection::UP:
                if(this->currentHP - this->healthPoint == 0)
                    tankSprite = tankSpriteUp[0];
                if(this->currentHP - this->healthPoint > 100)
                    tankSprite = tankSpriteUp[1];
                if(this->currentHP - this->healthPoint > 300)
                    tankSprite = tankSpriteUp[2];
                if(this->currentHP - this->healthPoint >= this->currentHP)
                    tankSprite = tankSpriteUp[3];
                break;
            case TankDirection::DOWN:
                if(this->currentHP - this->healthPoint == 0)
                    tankSprite = tankSpriteDown[0];
                if(this->currentHP - this->healthPoint > 100)
                    tankSprite = tankSpriteDown[1];
                if(this->currentHP - this->healthPoint > 300)
                    tankSprite = tankSpriteDown[2];
                if(this->currentHP - this->healthPoint >= this->currentHP)
                    tankSprite = tankSpriteDown[3];
                break;
        }
        return tankSprite;
    }

    void setXpoz(int xPoz) {
        this->xPoz = xPoz;
    }
    void setYpoz(int yPoz) {
        this->yPoz = yPoz;
    }
    void setSprite(QString path) {
        tankSprite = QPixmap(path);
    }
    void setPixmap(QPixmap pixmap) {
        tankSprite = pixmap;
    }
    void setDirection(TankDirection direction) {
        this->direction = direction;
    }

    vector<Bullet> getBullets() {
        return bullets;
    }

    void setCoolDown(float coolDown) {
        this->coolDown = coolDown;
    }

    float getHpPersent() {
        return ((float) healthPoint / (float) currentHP) * 100;
    }

    QPixmap getDownPixmap() {
        return *tankSpriteDown;
    }

    TankType getType() {
        return this->type;
    }

    //Key Handlers
    void leftPressed(bool collide) {
        if(direction == TankDirection::LEFT) {
            if(!collide)
                this->setXpoz(xPoz - speed / 10);
        }
        else {
            direction = TankDirection::LEFT;
        }
    }
    void rightPressed(bool collide) {
        if(direction == TankDirection::RIGHT) {
            if(!collide)
                this->setXpoz(xPoz + speed / 10);
        }
        else {
            direction = TankDirection::RIGHT;
        }
    }
    void upPressed(bool collide) {
        if(direction == TankDirection::UP) {
            if(!collide)
                this->setYpoz(yPoz - speed / 10);
        }
        else {
            direction = TankDirection::UP;
        }
    }
    void downPressed(bool collide) {
        if(direction == TankDirection::DOWN) {
            if(!collide)
                this->setYpoz(yPoz + speed / 10);
        }
        else {
            direction = TankDirection::DOWN;
        }
    }
    Bullet spacePressed() {
            isShot = true;
            shot = clock();
            int xPoz;
            int yPoz;
            switch(direction) {
                case LEFT:
                    xPoz = this->xPoz - 16;
                    yPoz = this->yPoz + (this->height - 16) / 2;
                    break;
                case RIGHT:
                    xPoz = this->xPoz + this->height;
                    yPoz = this->yPoz + (this->height - 16) / 2;
                    break;
                case UP:
                    xPoz = this->xPoz + this->width / 2 - 8;
                    yPoz = this->yPoz - 16;
                    break;
                case DOWN:
                    xPoz = this->xPoz + this->width / 2 - 8;
                    yPoz = this->yPoz + this->height;
                break;
            }
            return Bullet(this->power, direction, xPoz, yPoz);
    }
};

#endif // BASETANK_H
