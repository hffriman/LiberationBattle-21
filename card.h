#ifndef CARD_H
#define CARD_H
#include <QString>

class Card
{
public:
    Card();

    void SetCardName(QString name);
    QString GetCardName();

    void SetCardPoints(int points);
    int GetCardPoints();

    void SetCardImageSource(QString imageSource);
    QString GetCardImageSource();

private:
    QString cardName;
    int cardPoints;
    QString cardImageSource;

};

#endif // CARD_H
