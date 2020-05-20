#include <World.h>
int main() {

    World world(1, 60, 8001, 6, 60);// количество игроков, длительность игры, порт, колво слоев, радиус слоя
    world.game_start();
    return 0;

}