#pragma once
#include <vector>
#include <memory>
#include "ICard.h"

// Interface untuk modifier/bond — bagian MUTABLE dari sistem
// Bond baru bisa ditambah tanpa menyentuh GameSession
class IBondRule {
public:
    virtual void Apply(std::vector<std::unique_ptr<ICard>>& cards) = 0;
    virtual ~IBondRule() = default;
};
