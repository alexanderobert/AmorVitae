#include <actionManager.h>


void actionManager::sendMove(actionServer &action, DirectionInterface dir){
    action.sendActionMove(dir);
}
void actionManager::sendBlink(actionServer &action){
    action.sendActionBlink();
}

void actionManager::actionUser(sf::RenderWindow &window, sf::Event &event, actionServer &action) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
            action.sendActionMove(up);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
            action.sendActionMove(left);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
            action.sendActionMove(right);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
            action.sendActionMove(down);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
            action.sendActionBlink();
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
            action.sendActionShot();
        }
        if (event.type == sf::Event::MouseMoved) {
            action.updateSight(event.mouseMove.x, event.mouseMove.y);
        }
    }
}