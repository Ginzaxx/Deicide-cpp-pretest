#pragma once
#include "Cards/CardRegistry.h"
#include <string>

class ShopSystem
{
public:
    explicit ShopSystem(CardRegistry& registry);

    void OpenShop();

private:
    CardRegistry& cardRegistry;

    static constexpr int PACK_OPTIONS = 3;

    void OpenKremnosPack();
    void OpenOkhemaPack();

    void UpgradeCardPrototype(const std::string& cardName);
    void UpgradeBond(const std::string& bondName);

    int GetValidatedInput(int min, int max);
};