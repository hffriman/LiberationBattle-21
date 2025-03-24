#include "card.h"

Card::Card() {

    cardName = "";
    cardPoints = 0;
    cardImageSource = "";

}

void Card::SetCardName(QString name)
{
    this->cardName = name;
}

QString Card::GetCardName()
{
    return this->cardName;
}

void Card::SetCardPoints(int points)
{
    this->cardPoints = points;
}

int Card::GetCardPoints()
{
    return this->cardPoints;
}

void Card::SetCardImageSource(QString imageSource)
{
    this->cardImageSource = imageSource;
}

QString Card::GetCardImageSource()
{
    return this->cardImageSource;
}


