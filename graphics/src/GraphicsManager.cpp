#include <GraphicsManager.h>
#include <string>

void GraphicsManager::drawMap(const std::vector<MapInterface> &map) {
    int state = map[0].layers_count;
    int radius = map[0].ring_radius;

    sf::Text ids[4];

    int circlePoints = 50;

    window->draw(background);

    for (int i = 0; i < state; ++i) {
        sf::CircleShape stage(
                float(radius * (state - i)), circlePoints);
        stage.setPosition(
                window->getSize().x / 2 - radius * (state - i),
                window->getSize().y / 2 - radius * (state - i)
        );
        stage.setFillColor(mapColors[i]);
        window->draw(stage);
    }

    for (auto x : map[0].players_pts) {
        sf::Font font;
        if (!font.loadFromFile("../graphics/fonts/arial.ttf")) {/* handle error */}

        sf::Text id;
        sf::Text pts;

        id.setFont(font);
        pts.setFont(font);

        if (x.first == 0) {
            id.setString("Me");
        } else {
            id.setString("Griyazniy_Billy");
        }

        pts.setString(std::to_string(x.second));

        id.setColor(sf::Color::White);
        pts.setColor(sf::Color::White);

        id.setCharacterSize(20);
        pts.setCharacterSize(20);

        id.setPosition(-250 + config.windowWidth * 9 / 10, config.windowHeight * 1 / 10 - 50 + 50 * x.first);
        pts.setPosition(-50 + config.windowWidth * 9 / 10 + 30, config.windowHeight * 1 / 10 - 50 + 50 * x.first);

        window->draw(id);
        window->draw(pts);
    }


}

GraphicsManager::GraphicsManager(Config config, actionManager &user) : config(config) {
    window = new sf::RenderWindow(
            sf::VideoMode(config.windowWidth, config.windowHeight),
            "AmorVitae",
            sf::Style::Titlebar | sf::Style::Close
    );
    window->setMouseCursorVisible(false);
    //menu = new Menu(config.windowWidth, config.windowHeight);
    open = true;

    user.makeIcon(*window); //создание иконки из actionManager

    if (!menu_texture.loadFromFile("../graphics/textures/menu_background.jpg")) {
        std::cout << "texture load failed" << std::endl;
    }

    if (!background_texture.loadFromFile("../graphics/textures/space_background.jpeg")) {
        std::cout << "texture load failed" << std::endl;
    }

    if (!player_texture.loadFromFile("../graphics/textures/UFO2.png")) {
        std::cout << "texture load failed" << std::endl;
    }

    if (!enemy_player_texture.loadFromFile("../graphics/textures/UFO3.png")) {
        std::cout << "texture load failed" << std::endl;
    }

    if (!bullet_texture.loadFromFile("../graphics/textures/bullet.png")) {
        std::cout << "texture load failed" << std::endl;
    }

    if (!win.loadFromFile("../graphics/textures/you_win.png")) {
        std::cout << "texture load failed" << std::endl;
    }

    if (!lose.loadFromFile("../graphics/textures/you_lose.png")) {
        std::cout << "texture load failed" << std::endl;
    }

    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setTexture(&background_texture);

    menu.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    menu.setTexture(&menu_texture);

    mapColors.emplace_back(sf::Color::White);
    mapColors.emplace_back(sf::Color(204, 227, 249));
    mapColors.emplace_back(sf::Color(153, 200, 244));
    mapColors.emplace_back(sf::Color(102, 172, 239));
    mapColors.emplace_back(sf::Color(0, 118, 229));

}

bool GraphicsManager::isOpen() const {
    return open;
}

void GraphicsManager::close() {
    window->close();
    open = false;
    delete window;
}

void GraphicsManager::handleEvent(actionManager &user, actionServer &action) {
    sf::Event event;
    user.actionUser(*window, event, action);
}

void GraphicsManager::clear() {
    window->clear();
}

void GraphicsManager::drawPlayer(const std::vector<PlayerInterface> &playerData) {
    std::vector<PlayerModel> buff;


    for (PlayerInterface player : playerData) {
//        std::cout<<player.sight.to.x<<std::endl;
//        std::cout<<player.sight.to.y<<std::endl;
//        std::cout<<player.sight.to.x<<std::endl;
//        std::cout<<player.sight.to.y<<std::endl;

        PlayerModel playerModel(
                player.position.x - player.model.width / 2,
                player.position.y - player.model.height / 2,
                player.model.width,
                player.model.height,
                player.sight.to.x,
                player.sight.to.y
        );
        buff.push_back(playerModel);
    }

    buff[0].setTexture(player_texture);

    if (buff.size() > 1)
        buff[1].setTexture(enemy_player_texture);

    sf::RenderStates renderStates;
    for (auto &it : buff) {
//        if(it.getID() == myID){
////
////        } else {
////            it.setTexture(enemy_player_texture);
////            }
//        it.
//        if(it.getID() == myID){
//
//        }

        it.draw(*window, renderStates);
    }

}


void GraphicsManager::drawObstacle(const std::vector<ObstructionInterface> &obstacleData) {
    std::vector<sf::RectangleShape> obs;

    for (ObstructionInterface obstacle : obstacleData) {
        sf::RectangleShape obsModel(sf::Vector2f(obstacle.model.width, obstacle.model.height));
        obsModel.setPosition(sf::Vector2f(obstacle.position.x, obstacle.position.y));
        obsModel.setFillColor(sf::Color::Red);

        obs.push_back(obsModel);
    }

    for (const sf::RectangleShape &model : obs) {
        window->draw(model);
    }
}

void GraphicsManager::drawProjectile(const std::vector<BulletInterface> &projectileData) {
    std::vector<ProjectileModel> bulletBuff;

    for (BulletInterface bullet : projectileData) {
        ProjectileModel projectileModel(
                bullet.position.x,
                bullet.position.y,
                bullet.model.width,
                bullet.model.height
        );

        bulletBuff.push_back(projectileModel);
    }

    sf::RenderStates renderStates;
    for (auto &it : bulletBuff) {
        it.setTexutre(bullet_texture);
        it.draw(*window, renderStates);
    }
}

void GraphicsManager::object(const std::vector<std::shared_ptr<ObjectInterface>> &objects) {
    std::map<ObjectInterface::Type, std::vector<std::shared_ptr<ObjectInterface>>> group;

    for (const std::shared_ptr<ObjectInterface> &obj : objects) {
        group[obj->type].push_back(obj);
    }

    std::vector<PlayerInterface> playersData;
    std::vector<MapInterface> mapData;
    std::vector<BulletInterface> bulletsData;
    std::vector<ObstructionInterface> obstructionData;

    for (std::shared_ptr<ObjectInterface> &obj : group[ObjectInterface::Type::PLAYER_OBJECT]) {
        playersData.emplace_back(*std::static_pointer_cast<PlayerInterface>(obj));
    }

    for (std::shared_ptr<ObjectInterface> &obj : group[ObjectInterface::Type::MAP_OBJECT]) {
        mapData.emplace_back(*std::static_pointer_cast<MapInterface>(obj));
    }

    for (std::shared_ptr<ObjectInterface> &obj : group[ObjectInterface::Type::BULLET_OBJECT]) {
        bulletsData.emplace_back(*std::static_pointer_cast<BulletInterface>(obj));
    }

    for (std::shared_ptr<ObjectInterface> &obj : group[ObjectInterface::Type::STATIC_OBJECT]) {
        obstructionData.emplace_back(*std::static_pointer_cast<ObstructionInterface>(obj));
    }

    drawMap(mapData);
    drawObstacle(obstructionData);
    drawPlayer(playersData);
    drawProjectile(bulletsData);

}

void GraphicsManager::displayMainMenu() {
//    sf::Font font;
//    if (!font.loadFromFile("../graphics/fonts/arial.ttf")) {/* handle error */}
//
//    sf::Text menu;
//    menu.setFont(font);
//    menu.setColor(sf::Color::Red);
//    menu.setString("Play");
//    menu.setCharacterSize(50);
//    menu.setPosition(sf::Vector2f(config.windowWidth / 2 - 50, config.windowHeight / 2 - 50));

    window->draw(menu);
}

void GraphicsManager::displayWin() {
//    sf::Font font;
//    if (!font.loadFromFile("../graphics/fonts/arial.ttf")) {/* handle error */}

    sf::RectangleShape winMessage(sf::Vector2f(500, 500));
    //sf::Text winMessage;
    winMessage.setTexture(&win);
//    winMessage.setFont(font);
//    winMessage.setColor(sf::Color::Red);
//    winMessage.setString("Win");
//    winMessage.setCharacterSize(50);
    winMessage.setPosition(sf::Vector2f(config.windowWidth / 2 - 250, config.windowHeight / 2 - 250));

    window->draw(winMessage);
}

void GraphicsManager::displayLose() {
//    sf::Font font;
//    if (!font.loadFromFile("../graphics/fonts/arial.ttf")) {/* handle error */}

    //sf::Text lossMessage;
    sf::RectangleShape lossMessage(sf::Vector2f(700, 700));
    //lossMessage.setTexture(&lose);
//        lossMessage.setFont(font);
//    lossMessage.setColor(sf::Color::Red);
//    lossMessage.setString("Lose");
//    lossMessage.setCharacterSize(50);
    lossMessage.setPosition(sf::Vector2f(config.windowWidth / 2 - 350, config.windowHeight / 2 - 350));

    window->draw(lossMessage);
}