#include "visualStructure.h"

VisualStructure::VisualStructure(const sf::Texture& texture, std::shared_ptr<Structure> logicStructure) 
        : logicStructure_(logicStructure), isValid_(true) {
    sprite_.setTexture(texture);
    sprite_.setScale(0.5f, 0.5f);
    auto [posX, posY] = logicStructure->getPosition();

    float xPos = 400 + (posX * 108);
    float yPos = 990 - (posY * 108);
    sprite_.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));
}


void VisualStructure::update() {
    if (isValid_) {
        auto [posX, posY] = logicStructure_.lock()->getPosition();
        sprite_.setPosition(static_cast<float>(posX), static_cast<float>(posY));
    }
}


void VisualStructure::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isValid_) {
        target.draw(sprite_, states);
    }
}