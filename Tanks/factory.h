#ifndef FACTORY
#define FACTORY

#include "Tanks/basetank.h"
#include "Tanks/lighttank.h"
#include "Tanks/mediumtank.h"
#include "Tanks/hardtank.h"

#include "Helpers/gameconstants.h"

class Factory {

public:
    static BaseTank* makeTank(TankType type) {
        switch(type) {
            case LIGHT:
                return new LightTank();
                break;
            case MEDIUM:
                return new MediumTank();
                break;
            case HARD:
                return new HardTank();
                break;
        }
    }
};


#endif // FACTORY

