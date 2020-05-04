#include <SFML/Graphics.hpp>
#include <iostream>

#include "clientConnection.h"
#include "actionServer.h"

int main() {

    clientConnection clientCon;
    actionServer action;


    bool startGameButtonPressed = false;

    //создание фона кнопки старт
    sf::RenderWindow window(sf::VideoMode(1200, 800), "AmorVitae", sf::Style::Titlebar | sf::Style::Close);
    sf::RectangleShape startGameButton(sf::Vector2f(120, 50));
    startGameButton.setPosition(560, 350);

    //подключение шрифта
    sf::Font font;
    if (!font.loadFromFile("ArialRegular.ttf"))
    {
        //нет шрифта
    }

    //создание подписи кнопки старта
    sf::Text labelStart;
    labelStart.setFont(font);
    labelStart.setString("Start game");
    labelStart.setCharacterSize(20);
    labelStart.setPosition(570, 360);
    labelStart.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                clientCon.closeConnectClient();
                window.close();
            }


            ///////////////////////////////
            if (event.type == sf::Event::MouseButtonPressed){
                if ((event.mouseButton.button == sf::Mouse::Left) &&
                ((sf::Mouse::getPosition(window).x >= 560)&&(sf::Mouse::getPosition(window).x <= 680)
                &&(sf::Mouse::getPosition(window).y >= 350)&&(sf::Mouse::getPosition(window).y <= 400)))
                {
                    startGameButtonPressed = true;
                    // запустить функцию подключения
                    bool isCon = clientCon.connectClient();
                }
            }

            if ((event.type == sf::Event::KeyPressed)&&(startGameButtonPressed)) {
                if (event.key.code == sf::Keyboard::W) {
                    //std::cout << "W was pressed" << std::endl;
                    //сигнал нажатия W
                    action.getActionKey("UP");
                }
                if (event.key.code == sf::Keyboard::A) {
                    //std::cout << "a was pressed" << std::endl;
                    //сигнал нажатия A
                    action.getActionKey("LEFT");
                }
                if (event.key.code == sf::Keyboard::D) {
                    //std::cout << "d was pressed" << std::endl;
                    //сигнал нажатия D
                    action.getActionKey("RIGHT");
                }
                if (event.key.code == sf::Keyboard::S) {
                    //std::cout << "s was pressed" << std::endl;
                    //сигнал нажатия S
                    action.getActionKey("DOWN");
                }
            }

            if ((event.type == sf::Event::MouseMoved)&&(startGameButtonPressed)){
                //std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                //std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                //посылать новые коориднаты мыши
                action.getActionMousePos(event.mouseMove.x, event.mouseMove.y );
            }

            ///получение данных от сервера
            json currentMessage = clientCon.getServer();

            //std::cout<<currentMessage;

            ///отображение графики от части графики
        }

        window.clear();

        // метка входа в игру
        if(!startGameButtonPressed) {
            window.draw(startGameButton);
            window.draw(labelStart);
        }

        window.display();
    }

    return 0;
}