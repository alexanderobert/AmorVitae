#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/clientConnection.h"
#include "include/actionManager.h"
#include <displayManager.h>
#include <actionServer.h>

int main() {

    clientConnectionInterface clientCon;
    actionServerInterface action;
    actionManagerInterface launch;

    bool startGameButtonPressed = false;

    //создание окна, Дожна быть часть от Глеба
    sf::RenderWindow window(sf::VideoMode(1200, 800), "AmorVitae", sf::Style::Titlebar | sf::Style::Close);

    launch.pollEvent(window, clientCon, action, startGameButtonPressed);

    //создание фона кнопки старт
//    sf::RectangleShape startGameButton(sf::Vector2f(120, 50));
//    startGameButton.setPosactionManagerition(560, 350);
//
//    //подключение шрифта
//    sf::Font font;
//    if (!font.loadFromFile("ArialRegular.ttf"))
//    {
//        //нет шрифта
//    }
//
//    //создание подписи кнопки старта
//    sf::Text labelStart;
//    labelStart.setFont(font);
//    labelStart.setString("Start game");
//    labelStart.setCharacterSize(20);
//    labelStart.setPosition(570, 360);
//    labelStart.setFillColor(sf::Color::Red);



    return 0;
}