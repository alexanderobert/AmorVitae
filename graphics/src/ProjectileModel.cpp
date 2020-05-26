#include <ProjectileModel.h>

ProjectileModel::ProjectileModel(float startX, float startY, int width, int height) :width(width), height(height) {
    position.x = startX;
    position.y = startY;

    model.setPosition(position);
}

ProjectileModel::~ProjectileModel() = default;

void ProjectileModel::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(model);
}

void ProjectileModel::setTexutre(sf::Texture &texture) {
    model.setTexture(texture);
}
