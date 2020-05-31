#ifndef PLAYERMODEL_H_INCLUDED
#define PLAYERMODEL_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <iostream>

class PlayerModel {
public:
    PlayerModel();

    PlayerModel(float startX, float startY, float width, float height, float sightToX, float sightToY);

    virtual ~PlayerModel();

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates);

    void setTexture(const sf::Texture &texture);

    void setPosition(float x, float y);

    int getID() { return id; }

private:
    int id;
    sf::Sprite model;
    sf::Vector2f position;
    float width;
    float height;
    float sightToX;
    float sightToY;
};

#endif