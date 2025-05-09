#ifndef VISUALENEMY_H
#define VISUALENEMY_H

#include "enemy.h"
#include <SFML/Graphics.hpp>

class VisualEnemy : public sf::Drawable {
private:
    sf::Sprite sprite_;
    std::weak_ptr<Enemy> logicEnemy_;
    bool isAlive_;
public:
    VisualEnemy(const sf::Texture& texture, std::shared_ptr<Enemy> logicEnemy);

    void update();

    void setAlive(bool alive) { isAlive_ = alive; }

    [[nodiscard]] bool isAlive() const { return isAlive_; }

    [[nodiscard]] std::shared_ptr<Enemy> getLogicEnemy() { return logicEnemy_.lock(); }

    sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif