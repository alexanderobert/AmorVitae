#include <World.h>
int main() {

    World world(1, 1, 8001, 5, 60);// количество игроков, длительность игры, порт, колво слоев, радиус слоя
    world.game_start();
    return 0;

}