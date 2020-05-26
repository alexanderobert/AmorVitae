#include "PlayerModel.h"

PlayerModel::PlayerModel(float startX, float startY, float width, float height) :width(width), height(height) {
    position.x = startX;
    position.y = startY;

    model.setPosition(position);
}
// 9 - 23, 42 - 64
PlayerModel::~PlayerModel() = default;

void PlayerModel::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) {

    renderTarget.draw(model);
}

void PlayerModel::setTexture(const sf::Texture &texture) {
    model.setTexture(texture);
}

void PlayerModel::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

PlayerModel::PlayerModel() = default;
