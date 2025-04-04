#include "card.h"

/* Card
 * - Contains details of a single card, such as:
 *   1. The name of the card
 *   2. The points granted by the card
 *   3. The image source of the card
 */
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


