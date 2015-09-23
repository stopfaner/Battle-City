 #ifndef BULLET
#define BULLET

#include <QPixmap>

#include "Helpers/gameconstants.h"
#include "Helpers/movable.h"
#include "Helpers/collidable.h"
#include "Tanks/basetank.h"

class BaseTank;

class Bullet : public Collidable, public Movable {

private:
    //Posiotion
    int xPoz;
    int yPoz;
    //Some conditions
    int width;
    int height;
    int speed;

    QPixmap* bulletRight;
    QPixmap* bulletLeft;
    QPixmap* bulletUp;
    QPixmap* bulletDown;

    TankDirection bulletDirection;
    TankType type;

    int lifeCounter = 0;
    bool deleted = false;
    int bulletPower = 0;

public:
    Bullet(int bulletPower, TankDirection tankDirection, int xPoz, int yPoz) {
        this->bulletPower = bulletPower;
        this->bulletDirection = tankDirection;
        this->xPoz = xPoz;
        this->yPoz = yPoz;

        this->width = 16;
        this->height = 16;

        speed = 5;

        bulletRight = new QPixmap(":/tanksprites/bullet_right.png");
        bulletLeft = new QPixmap(":/tanksprites/bullet_left.png");
        bulletUp = new QPixmap(":/tanksprites/bullet_up.png");
        bulletDown = new QPixmap(":/tanksprites/bullet_down.png");
    }

    int getXpoz() {
        return xPoz;
    }

    int getYpoz() {
        return yPoz;
    }

    void setXpoz(int xPoz) {
        this->xPoz = xPoz;
    }

    void setYpoz(int yPoz) {
        this->yPoz = yPoz;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    int getSpeed() {
        return speed;
    }

    bool isDeleted() {
        return deleted;
    }

    int getBulletPower() {
        return bulletPower;
    }

    TankDirection getTankDirection() {
        return this->bulletDirection;
    }

    TankType getType() {
        return this->type;
    }

    void updatePosition(bool collide) {
        if(lifeCounter == 5) {
            deleted = true;
        }
        if(!collide)
            switch(bulletDirection) {
                case TankDirection::LEFT:
                    setXpoz(this->xPoz - speed);
                    break;
                case TankDirection::RIGHT:
                    setXpoz(this->xPoz + speed);
                    break;
                case TankDirection::UP:
                    setYpoz(this->yPoz - speed);
                    break;
                case TankDirection::DOWN:
                    setYpoz(this->yPoz + speed);
                    break;
            }
        else {
            lifeCounter++;
            std::string prefix = ":/tanksprites/exp";
            switch(lifeCounter) {
                case 1:
                    prefix += std::to_string(1);
                    break;
                case 2:
                    prefix += std::to_string(2);
                    break;
                case 3:
                    prefix += std::to_string(3);
                    break;
                case 4:
                    prefix += std::to_string(4);
                    break;
                case 5:
                    prefix += std::to_string(5);
                    break;
            }
            prefix += ".png";

            bulletRight = bulletLeft = bulletUp = bulletDown = new QPixmap(QString(prefix.c_str()));
        }
    }

    QPixmap getBullet() {
        switch(bulletDirection) {
            case TankDirection::LEFT:
                return *bulletLeft;
                break;
            case TankDirection::RIGHT:
                return *bulletRight;
                break;
            case TankDirection::UP:
                return *bulletUp;
                break;
            case TankDirection::DOWN:
                return *bulletDown;
                break;
        }
    }
};

#endif // BULLET

