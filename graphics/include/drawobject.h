#include <SFML/Graphics.hpp>

class drawObject{
private:
    sf::Window window;
    struct Config config;
public:
    int init(struct Congfig);
    int drawMap(char *mapCode, int state);
    int drawPlayer(struct playerData);
    int drawProjectile(struct projectileData);

    void displayMainMenu(struct Config);
    void displayPauseScreen(struct Config);

}