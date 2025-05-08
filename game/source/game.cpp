#include "game.h"

#include <stdexcept>
#include <fstream>
#include <filesystem>


Game::Game() : landscape_(std::make_shared<Landscape>()) {
    landscape_->setSelf(landscape_);
}


void Game::initGame(const std::string& directory){
    std::string filename = "game_config.csv";
    std::string fullPath = directory;
    fullPath += filename;

    std::ifstream file(fullPath);
    std::string line;
    
    std::getline(file, line);

    if (std::getline(file, line)){
        std::istringstream lineStream(line);
        std::string level, gold, time;

        std::getline(lineStream, level, ',');
        std::getline(lineStream, gold, ',');
        std::getline(lineStream, time, ',');

        level_ = std::stoul(level);
        GlobalGold::setGold(std::stoul(gold));
        GlobalTime::setTime(std::stoul(time));
    }
    else{
        throw std::runtime_error("Incorrect data. Check the config file.");
    }
    landscape_->changeLandscapeFromCSV(directory);
}


void Game::makeMove() {
    GlobalTime::updateTime();
    landscape_->makeMove();
}