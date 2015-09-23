#ifndef GAME
#define GAME

#include "gamewidget.h"

class Game {

private:
    //Defining of private fields of class
    GameWidget* gameWidget;

    Game() {
        gameWidget = new GameWidget();
    }
    Game(const Game& game);
    Game& operator=(const Game& game);

public:
    static const Game& getInstance() {
        static Game* game = new Game();
        return *game;
    }

    void run() const{
        gameWidget->show();
    }
};

#endif // GAME

