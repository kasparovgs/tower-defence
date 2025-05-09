#ifndef STRUCTURE_H
#define STRUCTURE_H

// STATUS - DONE
#include <string>
#include <memory>
#include <iostream>

class Landscape;

struct StructureStats{
    std::size_t upgradeCost_;

    StructureStats(std::size_t upgradeCost) :
                   upgradeCost_(upgradeCost) {}
    
    virtual ~StructureStats() = default;
};

class Structure {
private:
    std::weak_ptr<Landscape> landscape_;
    std::string name_;
    std::size_t level_ = 1;
    std::pair<int, int> position_;
    std::size_t upgradeCost_;
protected:
    bool is_valid_ = true;
public:
    virtual ~Structure() = default;
    Structure() = default;
    Structure(std::string name,
              std::size_t level,
              std::pair<int, int> position,
              std::size_t upgradeCost) : 
                                        name_(name),
                                        level_(level),
                                        position_(position),
                                        upgradeCost_(upgradeCost) {}

    Structure(std::size_t upgradeCost) : upgradeCost_(upgradeCost) {}
    virtual void levelUp() = 0;
    virtual void makeMove() = 0;
    [[nodiscard]] std::string getName() const { return name_; }
    [[nodiscard]] std::pair<int, int> getPosition() const { return position_; }
    [[nodiscard]] std::size_t getLevel() const { return level_; }
    [[nodiscard]] std::size_t getUpgradeCost() const { return upgradeCost_; }
    [[nodiscard]] std::shared_ptr<Landscape> getLandscape() const { return landscape_.lock(); } 
    [[nodiscard]] bool getValidity() const { return is_valid_; }
    [[nodiscard]] virtual std::shared_ptr<StructureStats> getStats() const = 0;

    void setName(const std::string& name) { name_ = name; }
    void setLevel(std::size_t level) { level_ = level; };
    void setUpgradeCost(std::size_t upgradeCost) { upgradeCost_ = upgradeCost; }
    void setLandscape(std::shared_ptr<Landscape> landscape) { landscape_ = landscape; }
    void setPosition(const std::pair<int, int>& position) { position_ = position; }
};


#endif