#ifndef LIGHTTANK
#define LIGHTTANK

#include "Tanks/basetank.h"

class LightTank : public BaseTank {

private:
    void fillImages() {
        tankSpriteLeft[0] = QPixmap(":/tanksprites/light_tank_left.png");
        tankSpriteRight[0] = QPixmap(":/tanksprites/light_tank_right.png");
        tankSpriteDown[0] = QPixmap(":/tanksprites/light_tank_down.png");
        tankSpriteUp[0] = QPixmap(":/tanksprites/light_tank_up.png");
        tankSpriteLeft[1] = QPixmap(":/tanksprites/light_tank_left_1.png");
        tankSpriteRight[1] = QPixmap(":/tanksprites/light_tank_right_1.png");
        tankSpriteDown[1] = QPixmap(":/tanksprites/light_tank_down_1.png");
        tankSpriteUp[1] = QPixmap(":/tanksprites/light_tank_up_1.png");
        tankSpriteLeft[2] = QPixmap(":/tanksprites/light_tank_left_2.png");
        tankSpriteRight[2] = QPixmap(":/tanksprites/light_tank_right_2.png");
        tankSpriteDown[2] = QPixmap(":/tanksprites/light_tank_down_2.png");
        tankSpriteUp[2] = QPixmap(":/tanksprites/light_tank_up_2.png");
        tankSpriteLeft[3] = QPixmap(":/tanksprites/light_tank_left_3.png");
        tankSpriteRight[3] = QPixmap(":/tanksprites/light_tank_right_3.png");
        tankSpriteDown[3] = QPixmap(":/tanksprites/light_tank_down_3.png");
        tankSpriteUp[3] = QPixmap(":/tanksprites/light_tank_up_3.png");
    }

public:
    LightTank() {
        fillImages();
        direction = TankDirection::RIGHT;
        type = TankType::LIGHT;
        tankSprite = tankSpriteRight[0];
        speed = 50;
        currentHP =  healthPoint = 400;
        armor = 10;
        power = 50;
        coolDown = 1;
    }
};


#endif // LIGHTTANK

