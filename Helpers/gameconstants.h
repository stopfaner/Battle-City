#ifndef GAMECONSTANTS
#define GAMECONSTANTS

//Server connection parametrs
#define SERVER_HOST "188.166.30.164"
#define SERVER_PORT 8189

//Screen size constants
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//Game key constants
#define UP_KEY "up"
#define DOWN_KEY "down"
#define LEFT_KEY "left"
#define RIGHT_KEY "right"
#define SPACE_KEY "space"

#include <QPixmap>

enum TankDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum TankType {
    LIGHT = 1,
    MEDIUM = 2,
    HARD = 3,
    NONE = 4
};

enum FieldType {
    GROUND,
    BRICK,
    WATER
};

enum Collission {
    TOP_COLLISION,
    BOTTOM_COLLISION,
    LEFT_COLLISION,
    RIGHT_COLLISION,
    NO_COLLIDE
};

enum StateType {
    GAME_STATE,
    LOADING_STATE,
    MENU_STATE,
    OPTIONS_STATE,
    ABOUT_STATE,
    RATINGS_STATE
};

#endif // GAMECONSTANTS

