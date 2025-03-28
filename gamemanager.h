#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QString>

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
    void SetCurrentAction(QString action);
    QString GetCurrentAction();

private:
    int currentlyDrawnCards;
    int totalTurnsPassed;
    int pointsInCurrentTurn;
    QString currentAction;
};

#endif // GAMEMANAGER_H
