#ifndef DECK_H
#define DECK_H
#include "card.h"

class Deck
{
public:
    Deck();
    void CreateDeck();
    Card cards[52];
};

#endif // DECK_H
