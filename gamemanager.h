#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager
{
public:
    GameManager();
    void SetCurrentlyDrawnCards(int cards);
    int GetCurrentlyDrawnCards();
    void SetTotalTurnsPassed(int turns);
    int GetTotalTurnsPassed();
    void SetPointsInCurrentTurn(int points);
    int GetPointsInCurrentTurn();

private:
    int currentlyDrawnCards;
    int totalTurnsPassed;
    int pointsInCurrentTurn;
};

#endif // GAMEMANAGER_H
