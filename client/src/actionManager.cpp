#include <actionManager.h>
#include <clientConnection.h>

#include <X11/Xlib.h>

void actionManager::sendMove(actionServer &action, Direction dir){
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

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W) {
                action.sendActionMove(UP);
            }
            if (event.key.code == sf::Keyboard::A) {
                action.sendActionMove(LEFT);
            }
            if (event.key.code == sf::Keyboard::D) {
                action.sendActionMove(RIGHT);

            }
            if (event.key.code == sf::Keyboard::S) {
                action.sendActionMove(DOWN);
            }
            if (event.key.code == sf::Keyboard::Space) {
                action.sendActionBlink();
            }
        }
    }
}


