#include "../include/actionManager.h"
#include "../include/clientConnection.h"

void actionManagerInterface::pollEvent(sf::RenderWindow &window, clientConnectionInterface &clientCon, actionServerInterface &action, bool &startGameButtonPressed){

    startGameButtonPressed = true;

    while (window.isOpen()){

        sf::Event event;

        while (window.pollEvent(event)){
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
                    clientCon.myId = clientCon.connectClient();
                }
            }

            if ((event.type == sf::Event::KeyPressed)&&(startGameButtonPressed)) {
                if (event.key.code == sf::Keyboard::W) {
                    //std::cout << "W was pressed" << std::endl;
                    //сигнал нажатия W
                    action.sendActionMove(UP);
                }
                if (event.key.code == sf::Keyboard::A) {
                    //std::cout << "a was pressed" << std::endl;
                    //сигнал нажатия A
                    action.sendActionMove(LEFT);
                }
                if (event.key.code == sf::Keyboard::D) {
                    //std::cout << "d was pressed" << std::endl;
                    //сигнал нажатия D
                    action.sendActionMove(RIGHT);

                }
                if (event.key.code == sf::Keyboard::S) {
                    //std::cout << "s was pressed" << std::endl;
                    //сигнал нажатия S
                    action.sendActionMove(DOWN);
                }
                if (event.key.code == sf::Keyboard::Space) {
                    //std::cout << "space was pressed" << std::endl;
                    //сигнал нажатия Пробел
                    action.sendActionBlink();
                }
            }

            if ((event.type == sf::Event::MouseMoved)&&(startGameButtonPressed)){
                //std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                //std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                //посылать новые коориднаты мыши
                action.updateSight(event.mouseMove.x, event.mouseMove.y);
            }

            ///получение данных от сервера
            std::shared_ptr<ObjectInterface> currentMessage = action.getMessage();

            //std::cout<<currentMessage.type;

            ///отображение графики от части графики
        }

        window.clear();

        // метка входа в игру
//        if(!startGameButtonPressed) {
//            window.draw(startGameButton);
//            window.draw(labelStart);
//        }

        window.display();
    }
}