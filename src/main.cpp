
#include "Game.h"

int main() {
    srand(time(NULL));
    
    Game game;
    game.run();
    game.clean_up();

    return 0;
}
