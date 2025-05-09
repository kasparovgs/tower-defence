#include "visualEnemy.h"


VisualEnemy::VisualEnemy(const sf::Texture& texture, std::shared_ptr<Enemy> logicEnemy) : logicEnemy_(logicEnemy), isAlive_(true) {
    sprite_.setTexture(texture);
    sprite_.setScale(0.3f, 0.3f);
    auto [posX, posY] = logicEnemy->getPosition();

    float xPos = 400 + (posX * 108);
    float yPos = 990 - (posY * 108);
    sprite_.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));
}


void VisualEnemy::update() {
    if (isAlive_) {
        auto [posX, posY] = logicEnemy_.lock()->getPosition();
        sprite_.setPosition(static_cast<float>(posX), static_cast<float>(posY));
    }
}


void VisualEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isAlive_) {
        target.draw(sprite_, states);
    }
}


