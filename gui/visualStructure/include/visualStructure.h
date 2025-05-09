#ifndef VISUALSTRUCTURE_H
#define VISUALSTRUCTURE_H

#include "structure.h"
#include <SFML/Graphics.hpp>

class VisualStructure : public sf::Drawable {
private:
    sf::Sprite sprite_;
    std::weak_ptr<Structure> logicStructure_;
    bool isValid_;
public:
    VisualStructure(const sf::Texture& texture, std::shared_ptr<Structure> logicStructure);

    void update();

    void setValid(bool valid) { isValid_ = valid; }

    [[nodiscard]] bool isValid() const { return isValid_; }

    [[nodiscard]] std::shared_ptr<Structure> getLogicStructure() { return logicStructure_.lock(); }

    sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif