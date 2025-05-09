#ifndef UPGRADE_MANAGER
#define UPGRADE_MANAGER

#include <unordered_map>
#include <memory>
class Structure;


class UpgradeManager {
public:
    UpgradeManager() = delete;
    static void levelUp(std::shared_ptr<Structure> structure);
};


#endif