#include "ObstacleModel.h"

ObstacleModel::ObstacleModel(float startX, float startY, float _width, float _height) :width(_width), height(_height) {
    position.x = startX;
    position.y = startY;

    color = sf::Color::Black;

    model.setSize(sf::Vector2f(width, height));
    model.setFillColor(color);
    model.setPosition(position);
}

ObstacleModel::~ObstacleModel() = default;

void ObstacleModel::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(model);
}