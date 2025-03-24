#include "deck.h"
#include "card.h"
#include <QDebug>

Deck::Deck() {

}

void Deck::CreateDeck()
{
    QString cardNames[52] = {"Heart-A", "Heart-2", "Heart-3", "Heart-4", "Heart-5", "Heart-6", "Heart-7", "Heart-8", "Heart-9", "Heart-10", "Heart-J", "Heart-Q", "Heart-K", "Spade-A", "Spade-2", "Spade-3", "Spade-4", "Spade-5", "Spade-6", "Spade-7", "Spade-8", "Spade-9", "Spade-10", "Spade-J", "Spade-Q", "Spade-K", "Club-A", "Club-2", "Club-3", "Club-4", "Club-5", "Club-6", "Club-7", "Club-8", "Club-9", "Club-10", "Club-J", "Club-Q", "Club-K", "Diamond-A", "Diamond-2", "Diamond-3", "Diamond-4", "Diamond-5", "Diamond-6", "Diamond-7", "Diamond-8", "Diamond-9", "Diamond-10", "Diamond-J", "Diamond-Q", "Diamond-K"};
    int cardPoints[52] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    QString cardImageSources[52] = {"/images/cards/Heart-A.png", "/images/cards/Heart-2.png", "/images/cards/Heart-3.png", "/images/cards/Heart-4.png", "/images/cards/Heart-5.png", "/images/cards/Heart-6.png", "/images/cards/Heart-7.png", "/images/cards/Heart-8.png", "/images/cards/Heart-9.png", "/images/cards/Heart-10.png", "/images/cards/Heart-J.png", "/images/cards/Heart-Q.png", "/images/cards/Heart-K.png", "/images/cards/Spade-A.png", "/images/cards/Spade-2.png", "/images/cards/Spade-3.png", "/images/cards/Spade-4.png", "/images/cards/Spade-5.png", "/images/cards/Spade-6.png", "/images/cards/Spade-7.png", "/images/cards/Spade-8.png", "/images/cards/Spade-9.png", "/images/cards/Spade-10.png", "/images/cards/Spade-J.png", "/images/cards/Spade-Q.png", "/images/cards/Spade-K.png", "/images/cards/Club-A.png", "/images/cards/Club-2.png", "/images/cards/Club-3.png", "/images/cards/Club-4.png", "/images/cards/Club-5.png", "/images/cards/Club-6.png", "/images/cards/Club-7.png", "/images/cards/Club-8.png", "/images/cards/Club-9.png", "/images/cards/Club-10.png", "/images/cards/Club-J.png", "/images/cards/Club-Q.png", "/images/cards/Club-K.png", "/images/cards/Diamond-A.png", "/images/cards/Diamond-2.png", "/images/cards/Diamond-3.png", "/images/cards/Diamond-4.png", "/images/cards/Diamond-5.png", "/images/cards/Diamond-6.png", "/images/cards/Diamond-7.png", "/images/cards/Diamond-8.png", "/images/cards/Diamond-9.png", "/images/cards/Diamond-10.png", "/images/cards/Diamond-J.png", "/images/cards/Diamond-Q.png", "/images/cards/Diamond-K.png"};

    for (int i = 0; i < 52; i++)
    {
        Card card = *new Card();
        card.SetCardName(cardNames[i]);
        card.SetCardPoints(cardPoints[i]);
        card.SetCardImageSource(cardImageSources[i]);

        cards[i] = card;
        qDebug() << cards[i].GetCardName();
        qDebug() << cards[i].GetCardPoints();
        qDebug() << cards[i].GetCardImageSource();
    }
}
