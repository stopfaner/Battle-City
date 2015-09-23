#ifndef FIELDELEMENT
#define FIELDELEMENT

#include <QPixmap>
#include <QMovie>

#include "GameField/map.h"
#include "Helpers/gameconstants.h"
#include "Helpers/collidable.h"

class Map;

class FieldElement : public Collidable {

protected:
    QPixmap* pixmap;

    int xPoz;
    int yPoz;

    float blockWidth;
    float blockHeight;

    FieldType type;

public:
    FieldElement() {
        this->blockWidth = 80;
        this->blockHeight = 80;
    }

    void setXpoz(int xPoz) {
        this->xPoz = xPoz;
    }

    void setYpoz(int yPoz) {
        this->yPoz = yPoz;
    }

    int getXpoz() {
        return xPoz;
    }

    int getYpoz() {
        return yPoz;
    }

    int getWidth() {
        return blockWidth;
    }
    int getHeight() {
        return blockHeight;
    }

    QPixmap getPixmap() {
        switch(type) {
            case FieldType::WATER:
                pixmap = new QPixmap(":/images/field/water.jpg");
                return *pixmap;
                break;
            case FieldType::GROUND:
                pixmap = new QPixmap(":/images/grass.jpg");
                return *pixmap;
                break;
            case FieldType::BRICK:
                pixmap = new QPixmap(":/images/stone.jpg");
                return *pixmap;
                break;
        }
    }

    void setType(FieldType type) {
        this->type = type;
    }

    FieldType getType() {
        return this->type;
    }
};

#endif
