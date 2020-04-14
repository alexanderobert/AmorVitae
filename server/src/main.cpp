
#include "../include/World.h"

int main() {

    World world(player_count, round_duration, port);// В конструкторе Создаются Приватные поля(EventManager, NetServer, ObjectManager)
    world.game_start()
    return 0;

}
