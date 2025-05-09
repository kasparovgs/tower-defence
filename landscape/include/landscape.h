#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <memory>
#include <vector>
#include "structure.h"
#include "mymatrix.h"

class Enemy;

enum class fieldType{
    Water,
    Mountain,
    Plain
};

class Field{
private:
    fieldType field_ = fieldType::Plain;
    std::shared_ptr<Structure> structure_ = nullptr;
    std::shared_ptr<Enemy> enemy_ = nullptr;
public:
    Field() = default;
    Field(fieldType field, std::shared_ptr<Structure> structure) : field_(field), structure_(structure){}

    [[nodiscard]] std::shared_ptr<Structure> getStructure() const { return structure_; }
    [[nodiscard]] std::shared_ptr<Enemy> getEnemy() const { return enemy_; }
    [[nodiscard]] fieldType getFieldType() const { return field_; }

    void setStructure(const std::shared_ptr<Structure> structure) { structure_ = structure; }
    void setEnemy(const std::shared_ptr<Enemy>& enemy) { enemy_ = enemy; }
    void setFieldType(fieldType field) { field_ = field; }
};


using Matrix = MyMatrix<Field>;
class Landscape{
private:
    std::weak_ptr<Landscape> self_;
    std::vector<std::shared_ptr<Enemy>> enemies_;
    std::size_t mapSize_ = 0;
    std::vector<std::shared_ptr<Structure>> structures_;

    Matrix fieldGrid_;

    std::pair<int, int> lairPos_;
    std::pair<int, int> castlePos_;
public:
    Landscape() = default;
    explicit Landscape(const std::string& directory);

    void makeMove();

    void changeLandscapeFromCSV(const std::string& directory);
    void changeFieldFromCSV(const std::string& directory);
    void changeEnemiesFromCSV(const std::string& directory);
    void changeStructuresFromCSV(const std::string& directory);

    void setSelf(std::shared_ptr<Landscape> ptr) { self_ = ptr; }

    [[nodiscard]] const std::vector<std::shared_ptr<Enemy>>& getEnemies() { return enemies_; }

    [[nodiscard]] const std::vector<std::shared_ptr<Structure>>& getStructures() { return structures_; }

    [[nodiscard]] std::shared_ptr<Landscape> getSelf() { return self_.lock(); }

    [[nodiscard]] Matrix& getFieldGrid() { return fieldGrid_; }

    [[nodiscard]] Field& getFieldByPosition(const std::pair<int, int>& position) const;

    [[nodiscard]] std::pair<int, int> getCastlePosition() const { return castlePos_; }

    [[nodiscard]] std::pair<int, int> getLairPosition() const { return lairPos_; }

    [[nodiscard]] std::shared_ptr<Structure> getStructureByPosition(const std::pair<int, int>& position) const;

    [[nodiscard]] std::shared_ptr<Enemy> getEnemyByPosition(const std::pair<int, int>& position) const;

    [[nodiscard]] std::size_t getMapSize() const { return mapSize_; }

    void setCastlePosition(const std::pair<int, int>& position);

    void setLairPosition(const std::pair<int, int>& position);

    void setStructureByPosition(const std::pair<int, int>& position, const std::shared_ptr<Structure> structure);

    void setEnemyByPosition(const std::pair<int, int>& position, const std::shared_ptr<Enemy> enemy);

    void addEnemy(std::shared_ptr<Enemy> enemy);

    void setMapSize(std::size_t size) { mapSize_ = size; }

    // итератор для enemyGrid_
    using EnemyIterator = std::vector<std::shared_ptr<Enemy>>::iterator;

    EnemyIterator beginEnemies() { return enemies_.begin(); }
    EnemyIterator endEnemies() { return enemies_.end(); }

    // итератор для structuresGrid_
    using StructuresIterator = std::vector<std::shared_ptr<Structure>>::iterator;

    StructuresIterator beginStructures() { return structures_.begin(); }
    StructuresIterator endStructures() { return structures_.end(); }
};


#endif