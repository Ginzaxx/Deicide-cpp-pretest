#pragma once
#include <string>

// Interface kartu — Prototype pattern
class ICard {
public:
    virtual ~ICard() {}
    virtual ICard*       Clone()    const = 0;
    virtual int          GetJourney() const = 0;  // base score
    virtual int          GetCycle()   const = 0;  // multiplier
    virtual std::string  GetName()    const = 0;
    virtual void         SetJourney(int j) = 0;
    virtual void         SetCycle(int c)   = 0;
};
