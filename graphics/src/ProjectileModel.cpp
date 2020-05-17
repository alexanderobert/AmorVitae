#include <ProjectileModel.h>

ProjectileModel::ProjectileModel(float startX, float startY, int _width, int _height) :width(_width), height(_height) {
    position.x = startX;
    position.y = startY;

    color = sf::Color::Green;

    int bulletWidth = 4;
    int bulletHeight = 4;

    model.setSize(sf::Vector2f(bulletWidth, bulletHeight));
    model.setFillColor(color);
    model.setPosition(position);
}

ProjectileModel::~ProjectileModel() = default;

void ProjectileModel::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(model);
}