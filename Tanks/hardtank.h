#ifndef HARDTANK
#define HARDTANK

#include "basetank.h"
#include <QPixmap>

class BaseTank;

class HardTank : public BaseTank {

private:
    void fillImages() {
        tankSpriteLeft[0] = QPixmap(":/tanksprites/hard_tank_left.png");
        tankSpriteRight[0] = QPixmap(":/tanksprites/hard_tank_right.png");
        tankSpriteDown[0] = QPixmap(":/tanksprites/hard_tank_down.png");
        tankSpriteUp[0] = QPixmap(":/tanksprites/hard_tank_up.png");
        tankSpriteLeft[1] = QPixmap(":/tanksprites/hard_tank_left_1.png");
        tankSpriteRight[1] = QPixmap(":/tanksprites/hard_tank_right_1.png");
        tankSpriteDown[1] = QPixmap(":/tanksprites/hard_tank_down_1.png");
        tankSpriteUp[1] = QPixmap(":/tanksprites/hard_tank_up_1.png");
        tankSpriteLeft[2] = QPixmap(":/tanksprites/hard_tank_left_2.png");
        tankSpriteRight[2] = QPixmap(":/tanksprites/hard_tank_right_2.png");
        tankSpriteDown[2] = QPixmap(":/tanksprites/hard_tank_down_2.png");
        tankSpriteUp[2] = QPixmap(":/tanksprites/hard_tank_up_2.png");
        tankSpriteLeft[3] = QPixmap(":/tanksprites/hard_tank_left_3.png");
        tankSpriteRight[3] = QPixmap(":/tanksprites/hard_tank_right_3.png");
        tankSpriteDown[3] = QPixmap(":/tanksprites/hard_tank_down_3.png");
        tankSpriteUp[3] = QPixmap(":/tanksprites/hard_tank_up_3.png");

    }
public:
    HardTank() {
        fillImages();
        direction = TankDirection::RIGHT;
        type = TankType::HARD;
        tankSprite = tankSpriteRight[0];
        speed = 30;
        currentHP =  healthPoint = 600;
        armor = 20;
        power = 60;
        coolDown = 3;
    }
};

#endif // HARDTANK

