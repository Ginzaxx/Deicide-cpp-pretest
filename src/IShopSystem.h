#pragma once
#include "CardRegistry.h"

// Interface untuk shop — MUTABLE
// GameSession hanya tahu interface ini, tidak tahu TitanShopSystem
class IShopSystem {
public:
    virtual void OpenShop(CardRegistry& registry) = 0;
    // ShowRegistry dipanggil GameSession saat player pilih "View" (free action)
    // Implementasinya ada di TitanShopSystem — GameSession tidak perlu tahu ModifierFactory
    virtual void ShowRegistry() = 0;
    virtual ~IShopSystem() = default;
};
