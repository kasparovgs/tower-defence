/**
 * @file Enemy.h
 * @brief Объявление абстрактного класса Enemy и связанной с ним структуры.
 */


#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include <memory>
#include <atomic>


#include "IDamageable.h"
class Aura;
#include "landscape.h"

/**
 * @struct EnemyStats
 * @brief Описывает основные характеристики врага.
 */
struct EnemyStats{
    std::size_t maxHP_ = 0;            ///< Максимальное количество здоровья врага.
    std::size_t regenerationRate_ = 0; ///< Скорость регенерации здоровья.
    std::size_t speed_ = 0;            ///< Скорость перемещения врага.

    /**
     * @brief Конструктор для инициализации характеристик врага.
     * @param maxHP Максимальное количество здоровья.
     * @param regenerationRate Скорость регенерации здоровья.
     * @param speed Скорость перемещения.
     */
    EnemyStats(std::size_t maxHP,
               std::size_t regenerationRate,
               std::size_t speed) :
               maxHP_(maxHP),
               regenerationRate_(regenerationRate),
               speed_(speed) {}
    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~EnemyStats() = default;
};


/**
 * @class Enemy
 * @brief Абстрактный класс, представляющий врага в игре.
 * Наследует интерфейс IDamageable.
 */
class Enemy : public IDamageable{
private:
    std::weak_ptr<Landscape> landscape_;      ///< Указатель на карту.
    std::vector<std::pair<int, int>> path_;   ///< Путь движения врага.
    std::string name_;                        ///< Имя врага.
    std::size_t maxHP_ = 0;                   ///< Максимальное количество здоровья.
    std::atomic<std::size_t> currentHP_ = 0;  ///< Текущее количество здоровья.
    std::size_t regenerationRate_ = 0;        ///< Скорость регенерации здоровья.
    std::pair<int, int> position_;            ///< Текущая позиция врага.
    std::size_t currentStep_ = 0;             ///< Текущий шаг по пути.
    std::size_t speed_ = 0;                   ///< Скорость перемещения.
    std::size_t level_ = 1;                   ///< Уровень.
public:
    /// @name Конструкторы
    /// @{

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~Enemy() = default;

    /**
     * @brief Конструктор для создания врага с полными параметрами.
     * @param name Имя врага.
     * @param maxHP Максимальное количество здоровья.
     * @param currentHP Текущее количество здоровья.
     * @param regenerationRate Скорость регенерации здоровья.
     * @param position Текущая позиция врага.
     * @param speed Скорость перемещения.
     */
    Enemy(std::string name,
          std::size_t maxHP,
          std::size_t currentHP,
          std::size_t regenerationRate,
          std::pair<int, int> position,
          std::size_t speed) : 
          name_(name),
          maxHP_(maxHP),
          currentHP_(currentHP),
          regenerationRate_(regenerationRate),
          position_(position),
          speed_(speed) {}

    /**
     * @brief Конструктор для создания врага с базовыми параметрами.
     * @param maxHP Максимальное количество здоровья.
     * @param regenerationRate Скорость регенерации здоровья.
     * @param speed Скорость перемещения.
     */
    Enemy(std::size_t maxHP,
          std::size_t regenerationRate,
          std::size_t speed) : 
          maxHP_(maxHP),
          currentHP_(maxHP),
          regenerationRate_(regenerationRate),
          speed_(speed) {}

    /**
     * @brief Конструктор по умолчанию.
     */
    Enemy() = default;
    /// @}

    /// @name Виртуальные логические методы
    /// @{

    /**
     * @brief Чистая виртуальная функция, описывающая логику движения врага.
     */
    virtual void makeMove() = 0;

    /**
     * @brief Чистая виртуальная функция для поиска пути.
     */
    virtual void findPath() = 0;

    /**
     * @brief Наносит урон по замку.
     * @return Размер урона, нанесенного замку.
     */
    virtual std::size_t dealDamageToCastle() { return currentHP_; }
    /// @}

    /// @name Модификаторы
    /// @{

    /**
     * @brief Устанавливает имя врага.
     * @param name Новое имя врага.
     */
    void setName(const std::string& name) { name_ = name; }

    /**
     * @brief Устанавливает максимальное количество здоровья.
     * @param maxHP Новое максимальное здоровье.
     */
    void setMaxHP(std::size_t maxHP) { maxHP_ = maxHP; }

    /**
     * @brief Устанавливает текущее количество здоровья.
     * @param currentHP Новое текущее здоровье.
     */
    void setCurrentHP(std::size_t currentHP) { currentHP_ = currentHP; }

    /**
     * @brief Устанавливает скорость регенерации здоровья.
     * @param regenerationRate Новая скорость регенерации.
     */
    void setRegenerationRate(std::size_t regenerationRate) { regenerationRate_ = regenerationRate; }

    /**
     * @brief Устанавливает текущую позицию врага.
     * @param position Новая позиция (x, y).
     */
    void setPosition(const std::pair<int, int>& position) { position_ = position; }

    /**
     * @brief Устанавливает текущий шаг врага по пути.
     * @param currentStep Новый текущий шаг.
     */
    void setCurrentStep(std::size_t currentStep) { currentStep_ = currentStep; }

    /**
     * @brief Устанавливает скорость перемещения врага.
     * @param speed Новая скорость.
     */
    void setSpeed(std::size_t speed) { speed_ = speed; }

    /**
     * @brief Устанавливает уровень врага.
     * @param level Новый уровень.
     */
    void setLevel(std::size_t level) { level_ = level; }

    /**
     * @brief Устанавливает путь движения врага.
     * @param path Новый путь в виде последовательности координат.
     */
    void setPath(std::vector<std::pair<int, int>>& path) { path_ = path; }

    /**
     * @brief Устанавливает карту, в котором находится враг.
     * @param landscape Умный указатель shared_ptr на карту.
     */
    void setLandscape(std::shared_ptr<Landscape> landscape) { landscape_ = landscape; }
    /// @}

    /// @name Геттеры
    /// @{

    /**
     * @brief Возвращает имя врага.
     * @return Имя врага.
     */
    [[nodiscard]] std::string getName() const { return name_; }

    /**
     * @brief Возвращает максимальное количество здоровья врага.
     * @return Максимальное здоровье.
     */
    [[nodiscard]] std::size_t getMaxHP() const { return maxHP_; }

    /**
     * @brief Возвращает текущее количество здоровья врага.
     * @return Текущее здоровье.
     */
    [[nodiscard]] std::atomic<std::size_t>& getCurrentHP() { return currentHP_; }

    /**
     * @brief Возвращает скорость регенерации здоровья врага.
     * @return Скорость регенерации.
     */
    [[nodiscard]] std::size_t getRegenerationRate() const { return regenerationRate_; }

    /**
     * @brief Возвращает текущую позицию врага.
     * @return Координаты позиции (x, y).
     */
    [[nodiscard]] std::pair<int, int> getPosition() const { return position_; }

    /**
     * @brief Возвращает текущий шаг врага по пути.
     * @return Номер текущего шага.
     */
    [[nodiscard]] std::size_t getCurrentStep() const { return currentStep_; }

    /**
     * @brief Возвращает скорость перемещения врага.
     * @return Скорость.
     */
    [[nodiscard]] std::size_t getSpeed() const { return speed_; }

    /**
     * @brief Возвращает уровень врага.
     * @return Уровень.
     */
    [[nodiscard]] std::size_t getLevel() const { return level_; }

    /**
     * @brief Возвращает указатель на карту, которую хранит враг.
     * @return Умный указатель shared_ptr, полученный из weak_ptr на карту.
     */
    [[nodiscard]] std::shared_ptr<Landscape> getLandscape() const { return landscape_.lock(); }

    /**
     * @brief Возвращает путь движения врага.
     * @return Ссылка на вектор координат пути.
     */
    [[nodiscard]] std::vector<std::pair<int, int>>& getPath() { return path_; }

    /**
     * @brief Возвращает указатель на структуру со статистикой врага.
     * @return Указатель на структуру с характеристикой.
     */
    [[nodiscard]] virtual std::shared_ptr<EnemyStats> getStats() const = 0;
    /// @}
};


#endif