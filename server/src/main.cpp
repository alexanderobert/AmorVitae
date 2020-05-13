
#include <World.h>
int main() {

    World world(0, 60, 808);// В конструкторе Создаются Приватные поля(EventManager, NetServer, ObjectManager)
    world.game_start();
    return 0;

}
