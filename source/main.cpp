#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "gameRenderer.h"
#include "upgradeManager.h"
#include "GameOverException.h"


int main() {
    Game game{};
    game.initGame("/home/gkasp/oop2024/3/tests/configs/");

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tower Defense");

    GameRenderer renderer(window, game);

    bool mousePressed = false;
    bool isBlocked = false;
    sf::Clock clock;

    renderer.render();    

    std::shared_ptr<VisualStructure> selectedStructure = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (isBlocked && clock.getElapsedTime().asSeconds() >= 5.0f) {
            window.close();
            return 0;
        }

        if (!isBlocked && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!mousePressed) {
                mousePressed = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (renderer.handleMouseClickMakeMove(mousePos)) {
                    try {
                        game.makeMove();
                        renderer.render();
                    }
                    catch (const GameOverException& ex) {
                        renderer.renderGameOverLost();
                        isBlocked = true;
                        clock.restart();
                    }
                }
                if (renderer.handleMouseClickCollectGold(mousePos)) {
                    GlobalGold::collectAccumulatedGold();
                    renderer.render();
                }
                if (auto visualEnemy = renderer.handleMouseClickEnemy(mousePos)) {
                    renderer.render();
                    renderer.renderEnemyStats(visualEnemy);
                }
                if (auto visualStructure = renderer.handleMouseClickStructure(mousePos)) {
                    selectedStructure = visualStructure;
                    renderer.render();
                    renderer.renderStructureStats(visualStructure);
                }
                if (renderer.handleMouseClickLevelUp(mousePos)) {
                    try {
                        UpgradeManager::levelUp(selectedStructure->getLogicStructure());
                        renderer.render();
                        renderer.renderStructureUpgradeSuccess();
                        renderer.renderStructureStats(selectedStructure); //
                    }
                    catch(const std::logic_error& e) {
                        std::string errorMsg = e.what();
                        if (errorMsg == "Insufficient funds") {
                            renderer.renderNoMoneyAlert();
                        }
                        else if (errorMsg == "The structure has already reached its maximum level.") {
                            renderer.renderStructureAlreadyMaxed();
                        }
                    }
                }
            }
        } else mousePressed = false;
    }

    return 0;
}