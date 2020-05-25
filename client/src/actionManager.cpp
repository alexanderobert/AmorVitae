#include <actionManager.h>

void actionManager::sendMove(actionServer &action, DirectionInterface dir){
    action.sendActionMove(dir);
}
void actionManager::sendBlink(actionServer &action){
    action.sendActionBlink();
}

void actionManager::actionUser(sf::RenderWindow &window, sf::Event &event, actionServer &action) {
    sf::Vector2f mouse_world = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    action.updateSight(mouse_world);

    sf::RectangleShape mouseOnScreen(sf::Vector2f(5, 5));
    mouseOnScreen.setPosition(action.mySight.to.x, action.mySight.to.y);
    mouseOnScreen.setFillColor(sf::Color::Red);
    window.draw(mouseOnScreen);

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
    }
}

void actionManager::makeIcon(sf::RenderWindow &window){
    sf::Image icon;
    icon.loadFromFile("../client/icons/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void actionManager::defineResolution(Config &configWindow){
    Display *display;
    display = XOpenDisplay (NULL);
//    configWindow.windowWidth = DisplayWidth (display, 0);
//    configWindow.windowHeight = DisplayHeight (display, 0);
    configWindow.windowWidth = 1280;
    configWindow.windowHeight = 800;
}