#ifndef OBSTACLEMODEL_H_INCLUDED
#define OBSTACLEMODEL_H_INCLUDED

#include <SFML/Graphics.hpp>

class ObstacleModel : public sf::Drawable {
public:
    ObstacleModel(float startX, float startY, float _width, float _height);
    virtual ~ObstacleModel();

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;
private:


    sf::RectangleShape model;
    sf::Vector2f position;
    float width;
    float height;
    sf::Color color;
};

#endif