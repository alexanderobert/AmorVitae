#ifndef PLAYERMODEL_H_INCLUDED
#define PLAYERMODEL_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <iostream>

class PlayerModel : public sf::Drawable {
public:
    PlayerModel(float startX, float startY, float _width, float _height);

    virtual ~PlayerModel();

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;

private:


    sf::Sprite model;
    sf::Texture texture;

    sf::Vector2f position;
    float width;
    float height;
    sf::Color color;
};

#endif