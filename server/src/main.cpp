#include <World.h>
int main() {

    World world(1, 60, 8001);// В конструкторе Создаются Приватные поля(EventManager, NetServer, ObjectManager)
    world.game_start();
    return 0;

}