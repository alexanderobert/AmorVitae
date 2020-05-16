#ifndef AMORVITAE_PROJECTILEMODEL_H
#define AMORVITAE_PROJECTILEMODEL_H

#include <SFML/Graphics.hpp>

class ProjectileModel : public sf::Drawable {
public:
    ProjectileModel(float startX, float startY, int _width, int _height);
    virtual ~ProjectileModel();

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;
private:


    sf::RectangleShape model;
    sf::Vector2f position;
    int width;
    int height;
    sf::Color color;
};

#endif //AMORVITAE_PROJECTILEMODEL_H