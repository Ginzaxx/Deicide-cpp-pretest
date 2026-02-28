#include "BaseCard.h"

BaseCard::BaseCard(std::string name, int journey, int cycle)
    : name(name), journey(journey), cycle(cycle) {}

ICard* BaseCard::Clone() const
{
    return new BaseCard(*this); // Prototype magic
}

int BaseCard::GetJourney() const { return journey; }
int BaseCard::GetCycle() const { return cycle; }
std::string BaseCard::GetName() const { return name; }