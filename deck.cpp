#include "deck.h"
#include "card.h"
#include <QDebug>

/* Deck:
 * - Contains all the necessary Card objects
 */
Deck::Deck() {

}

void Deck::CreateDeck()
{
    QString cardNames[52] = {"Heart-A", "Heart-2", "Heart-3", "Heart-4", "Heart-5", "Heart-6", "Heart-7", "Heart-8", "Heart-9", "Heart-10", "Heart-J", "Heart-Q", "Heart-K", "Spade-A", "Spade-2", "Spade-3", "Spade-4", "Spade-5", "Spade-6", "Spade-7", "Spade-8", "Spade-9", "Spade-10", "Spade-J", "Spade-Q", "Spade-K", "Club-A", "Club-2", "Club-3", "Club-4", "Club-5", "Club-6", "Club-7", "Club-8", "Club-9", "Club-10", "Club-J", "Club-Q", "Club-K", "Diamond-A", "Diamond-2", "Diamond-3", "Diamond-4", "Diamond-5", "Diamond-6", "Diamond-7", "Diamond-8", "Diamond-9", "Diamond-10", "Diamond-J", "Diamond-Q", "Diamond-K"};
    int cardPoints[52] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    QString cardImageSources[52] = {":/Images/Cards/Heart-A.png", ":/Images/Cards/Heart-2.png", ":/Images/Cards/Heart-3.png", ":/Images/Cards/Heart-4.png", ":/Images/Cards/Heart-5.png", ":/Images/Cards/Heart-6.png", ":/Images/Cards/Heart-7.png", ":/Images/Cards/Heart-8.png", ":/Images/Cards/Heart-9.png", ":/Images/Cards/Heart-10.png", ":/Images/Cards/Heart-J.png", ":/Images/Cards/Heart-Q.png", ":/Images/Cards/Heart-K.png", ":/Images/Cards/Spade-A.png", ":/Images/Cards/Spade-2.png", ":/Images/Cards/Spade-3.png", ":/Images/Cards/Spade-4.png", ":/Images/Cards/Spade-5.png", ":/Images/Cards/Spade-6.png", ":/Images/Cards/Spade-7.png", ":/Images/Cards/Spade-8.png", ":/Images/Cards/Spade-9.png", ":/Images/Cards/Spade-10.png", ":/Images/Cards/Spade-J.png", ":/Images/Cards/Spade-Q.png", ":/Images/Cards/Spade-K.png", ":/Images/Cards/Club-A.png", ":/Images/Cards/Club-2.png", ":/Images/Cards/Club-3.png", ":/Images/Cards/Club-4.png", ":/Images/Cards/Club-5.png", ":/Images/Cards/Club-6.png", ":/Images/Cards/Club-7.png", ":/Images/Cards/Club-8.png", ":/Images/Cards/Club-9.png", ":/Images/Cards/Club-10.png", ":/Images/Cards/Club-J.png", ":/Images/Cards/Club-Q.png", ":/Images/Cards/Club-K.png", ":/Images/Cards/Diamond-A.png", ":/Images/Cards/Diamond-2.png", ":/Images/Cards/Diamond-3.png", ":/Images/Cards/Diamond-4.png", ":/Images/Cards/Diamond-5.png", ":/Images/Cards/Diamond-6.png", ":/Images/Cards/Diamond-7.png", ":/Images/Cards/Diamond-8.png", ":/Images/Cards/Diamond-9.png", ":/Images/Cards/Diamond-10.png", ":/Images/Cards/Diamond-J.png", ":/Images/Cards/Diamond-Q.png", ":/Images/Cards/Diamond-K.png"};

    for (int i = 0; i < 52; i++)
    {
        Card card = *new Card();
        card.SetCardName(cardNames[i]);
        card.SetCardPoints(cardPoints[i]);
        card.SetCardImageSource(cardImageSources[i]);

        cards[i] = card;
    }
}
