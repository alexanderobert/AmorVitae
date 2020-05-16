#ifndef PLAYERMODEL_H_INCLUDED
#define PLAYERMODEL_H_INCLUDED

#include <SFML/Graphics.hpp>

class PlayerModel : public sf::Drawable {
public:
    PlayerModel(float startX, float startY, float _width, float _height);
    virtual ~PlayerModel();

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;
private:


    sf::RectangleShape model;
    sf::Vector2f position;
    float width;
    float height;
    sf::Color color;
};

#endif