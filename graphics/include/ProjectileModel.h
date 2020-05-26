#ifndef AMORVITAE_PROJECTILEMODEL_H
#define AMORVITAE_PROJECTILEMODEL_H

#include <SFML/Graphics.hpp>

class ProjectileModel : public sf::Drawable {
public:
    ProjectileModel(float startX, float startY, int width, int height);

    ~ProjectileModel();

    void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;

    void setTexutre(sf::Texture &texture);
private:
    sf::Sprite model;
    sf::Vector2f position;
    int width;
    int height;
};

#endif //AMORVITAE_PROJECTILEMODEL_H