#include "lair.h"
#include "globalTime.h"
#include "structureFactory.h"
#include <stdexcept>
#include <random>
#include <fstream>
#include <filesystem>

std::priority_queue<EnemyRelease, std::vector<EnemyRelease>, std::greater<>> Lair::ReleaseQueue_;
std::unordered_map<std::string, std::vector<std::shared_ptr<EnemyStats>>> Lair::EnemiesStatsTable_;



std::string random_string(std::size_t length){
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i){
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}


std::unordered_map<std::string, std::function<std::shared_ptr<Enemy>(std::shared_ptr<EnemyStats> stats)>> Lair::createEnemyByName = {
    {"Aviation", [](std::shared_ptr<EnemyStats> stats) {
        auto aviationStats = std::static_pointer_cast<AviationStats>(stats);
        return std::make_shared<Aviation>(aviationStats); }},

    {"LightInfantry", [](std::shared_ptr<EnemyStats> stats) {
        auto lightInfantryStats = std::static_pointer_cast<LightInfantryStats>(stats);
        return std::make_shared<LightInfantry>(lightInfantryStats); }},

    {"HeavyInfantry", [](std::shared_ptr<EnemyStats> stats) {
        auto heavyInfantryStats = std::static_pointer_cast<HeavyInfantryStats>(stats);
        return std::make_shared<HeavyInfantry>(heavyInfantryStats); }},

    {"HeroAviation", [](std::shared_ptr<EnemyStats> stats) {
        auto heroAviationStats = std::static_pointer_cast<HeroStats<AviationStats>>(stats);
        return std::make_shared<Hero<Aviation, AviationStats>>(heroAviationStats); }},

    {"HeroLightInfantry", [](std::shared_ptr<EnemyStats> stats) {
        auto heroLightInfantryStats = std::static_pointer_cast<HeroStats<LightInfantryStats>>(stats);
        return std::make_shared<Hero<LightInfantry, LightInfantryStats>>(heroLightInfantryStats); }},
        
    {"HeroHeavyInfantry", [](std::shared_ptr<EnemyStats> stats) {
        auto heroHeavyInfantryStats = std::static_pointer_cast<HeroStats<HeavyInfantryStats>>(stats);
        return std::make_shared<Hero<HeavyInfantry, HeavyInfantryStats>>(heroHeavyInfantryStats); }}
};


std::unordered_map<std::string, std::function<std::shared_ptr<EnemyStats>(std::stringstream& ss)>> Lair::createEnemyStatsByName = {
    {"Aviation", [](std::stringstream& ss) {
        std::size_t maxHP, regenerationRate, speed, ammo;
        char comma;
        ss >> maxHP >> comma >> regenerationRate >> comma >> speed >> comma >> ammo;
        return std::make_shared<AviationStats>(maxHP, regenerationRate, speed, ammo); }},

    {"LightInfantry", [](std::stringstream& ss) {
        std::size_t maxHP, regenerationRate, speed, missChance;
        char comma;
        ss >> maxHP >> comma >> regenerationRate >> comma >> speed >> comma >> comma >> comma >> comma >> missChance;
        return std::make_shared<LightInfantryStats>(maxHP, regenerationRate, speed, missChance); }},

    {"HeavyInfantry", [](std::stringstream& ss) {
        std::size_t maxHP, regenerationRate, speed, damage, range;
        char comma;
        ss >> maxHP >> comma >> regenerationRate >> comma >> speed >> comma >> comma >> damage >> comma >> range;
        return std::make_shared<HeavyInfantryStats>(maxHP, regenerationRate, speed, damage, range); }},

    {"HeroAviation", [](std::stringstream& ss) {
        std::size_t maxHP, regenerationRate, speed, ammo, auraRadius;
        char comma;
        std::string maxhpAura, regenerationAura, speedAura;
        ss >> maxHP >> comma >> regenerationRate >> comma >> speed >> comma >> ammo >> comma >> comma >> comma >> comma >> auraRadius >> comma;

        std::getline(ss, maxhpAura, ',');
        std::getline(ss, regenerationAura, ',');
        std::getline(ss, speedAura, '\r');

        std::vector<std::string> aurasNames;
        aurasNames.push_back(maxhpAura);
        aurasNames.push_back(regenerationAura);
        aurasNames.push_back(speedAura);
        return std::make_shared<HeroStats<AviationStats>>(maxHP, regenerationRate, speed, ammo, auraRadius, aurasNames); }},

    {"HeroLightInfantry", [](std::stringstream& ss) {
        std::size_t maxHP, regenerationRate, speed, missChance, auraRadius;
        char comma;
        std::string maxhpAura, regenerationAura, speedAura;
        ss >> maxHP >> comma >> regenerationRate >> comma >> speed >> comma >> comma >> comma >> comma >> missChance >> comma >> auraRadius >> comma;

        std::getline(ss, maxhpAura, ',');
        std::getline(ss, regenerationAura, ',');
        std::getline(ss, speedAura, '\r');

        std::vector<std::string> aurasNames;
        aurasNames.push_back(maxhpAura);
        aurasNames.push_back(regenerationAura);
        aurasNames.push_back(speedAura);
        return std::make_shared<HeroStats<LightInfantryStats>>(maxHP, regenerationRate, speed, missChance, auraRadius, aurasNames); }},

    {"HeroHeavyInfantry", [](std::stringstream& ss) {
        std::size_t maxHP, regenerationRate, speed, damage, range, auraRadius;
        char comma;
        std::string maxhpAura, regenerationAura, speedAura;
        ss >> maxHP >> comma >> regenerationRate >> comma >> speed >> comma >> comma >> damage >> comma >> range >> comma >> comma >> auraRadius >> comma;

        std::getline(ss, maxhpAura, ',');
        std::getline(ss, regenerationAura, ',');
        std::getline(ss, speedAura, '\r');

        std::vector<std::string> aurasNames;
        aurasNames.push_back(maxhpAura);
        aurasNames.push_back(regenerationAura);
        aurasNames.push_back(speedAura);
        return std::make_shared<HeroStats<HeavyInfantryStats>>(maxHP, regenerationRate, speed, damage, range, auraRadius, aurasNames); }}
};


void Lair::clearReleaseQueue(){
    while (!ReleaseQueue_.empty()){
        ReleaseQueue_.pop();
    }
}


std::shared_ptr<Enemy> Lair::releaseEnemy(const std::string& name, std::size_t level){
    auto it = EnemiesStatsTable_.find(name);
    if (it != EnemiesStatsTable_.end()){
        auto statsVec = it->second;

        if (level > statsVec.size()){
            throw std::out_of_range("There is no such level.");
        }

        auto stats = statsVec[level-1];
        auto enemy = createEnemyByName[name](stats);

        enemy->setName(random_string(6));
        enemy->setLevel(level);

        return enemy;
    }
    else{
        throw std::invalid_argument("Enemy not found.");
    }
}


std::shared_ptr<Enemy> Lair::releaseEnemyOnTime(std::size_t time){
    if (!ReleaseQueue_.empty() && ReleaseQueue_.top().time == time){
        EnemyRelease release = ReleaseQueue_.top();
        ReleaseQueue_.pop();

        std::shared_ptr<Enemy> enemy = releaseEnemy(release.type, release.level);

        release.time = release.interval + time;
        ReleaseQueue_.push(release);

        return enemy;
    }
    return nullptr;
}


void Lair::loadStatsFromConfig(const std::string& filePath){
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filePath);
    }

    std::string line;

    std::getline(file, line);
    EnemiesStatsTable_.clear();
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string enemyType;
        std::getline(ss, enemyType, ',');
        
        if (createEnemyStatsByName.find(enemyType) != createEnemyStatsByName.end()){
            auto enemyStats = createEnemyStatsByName[enemyType](ss);
            EnemiesStatsTable_[enemyType].emplace_back(enemyStats);
        }
        else{
            throw std::invalid_argument("Unknown type of enemy.");
        }
    }
}


void Lair::loadReleaseQueueFromConfig(const std::string& filePath){
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filePath);
    }
    clearReleaseQueue();
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::size_t time, interval, level;
        std::string enemyType, strTime, strInterval, strLevel;

        std::getline(ss, enemyType, ',');
        std::getline(ss, strTime, ',');
        std::getline(ss, strInterval, ',');
        std::getline(ss, strLevel, ',');

        time = std::stoul(strTime);
        level = std::stoul(strLevel);
        interval = std::stoul(strInterval);

        if (EnemiesStatsTable_.find(enemyType) != EnemiesStatsTable_.end()){
            EnemyRelease enemyRelease = {enemyType, time, interval, level};
            ReleaseQueue_.push(enemyRelease);
        }
        else{
            throw std::invalid_argument("Unknown type of enemy.");
        }
    }
}


void Lair::levelUp(){
    if (StructureFactory::StructuresStatsTable_["Lair"].size() < getLevel() + 1){
        throw std::logic_error("The structure has already reached its maximum level.");
    }
    setLevel(getLevel() + 1);
}


void Lair::makeMove() {
    std::size_t time = GlobalTime::getTime();
    auto enemy = releaseEnemyOnTime(time);
    auto prEnemy = releaseEnemyOnTime(time);
    while (prEnemy != nullptr) {
        prEnemy = releaseEnemyOnTime(time);
    }
    if (enemy != nullptr) {
        auto landscape =  getLandscape();
        landscape->addEnemy(enemy);
    }
}


std::shared_ptr<StructureStats> Lair::getStats() const {
    return std::make_shared<LairStats>(getUpgradeCost());
}