#ifndef AMORVITAE_STRUCT_CONFIG_H
#define AMORVITAE_STRUCT_CONFIG_H

#include <SFML/Window/Keyboard.hpp>

struct Config {
    int windowWidth;
    int windowHeight;

    //int radius;

    sf::Keyboard::Key UP;
    sf::Keyboard::Key DOWN;
    sf::Keyboard::Key LEFT;
    sf::Keyboard::Key RIGHT;
};

#endif //AMORVITAE_STRUCT_CONFIG_H
