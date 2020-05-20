#include "PlayerModel.h"

PlayerModel::PlayerModel(float startX, float startY, float _width, float _height) :width(_width), height(_height) {
    position.x = startX;
    position.y = startY;

    if (!texture.loadFromFile("../graphics/textures/characters.jpg")) {
        std::cout << "texture load failed" << std::endl;
    }

    sf::IntRect rectSourceSprite(9, 42, 14, 22);

    model.setTexture(texture);
    model.setTextureRect(rectSourceSprite);

    //model.setFillColor(color);

    model.setPosition(position);
}
// 9 - 23, 42 - 64
PlayerModel::~PlayerModel() = default;

void PlayerModel::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(model);
}