#pragma once
#include <string>

class ICard//prototype
{
public:
    virtual ~ICard() {}

    virtual ICard* Clone() const = 0;

    virtual int GetJourney() const = 0;   // base score
    virtual int GetCycle() const = 0;     // multiplier
    virtual std::string GetName() const = 0;
};