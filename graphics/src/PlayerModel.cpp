#include "PlayerModel.h"

PlayerModel::PlayerModel(float startX, float startY, float _width, float _height) :width(_width), height(_height) {
    position.x = startX;
    position.y = startY;

    color = sf::Color::Red;

    model.setSize(sf::Vector2f(width, height));
    model.setFillColor(color);
    model.setPosition(position);
}

PlayerModel::~PlayerModel() = default;

void PlayerModel::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(model);
}