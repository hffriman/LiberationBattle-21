#include "gamemanager.h"

GameManager::GameManager() {
    currentlyDrawnCards = 0;
    totalTurnsPassed = 0;
    pointsInCurrentTurn = 0;
}


void GameManager::SetCurrentlyDrawnCards(int cards)
{
    this->currentlyDrawnCards = cards;
}

int GameManager::GetCurrentlyDrawnCards()
{
    return this->currentlyDrawnCards;
}

void GameManager::SetTotalTurnsPassed(int turns)
{
    this->totalTurnsPassed = turns;
}

int GameManager::GetTotalTurnsPassed()
{
    return this->totalTurnsPassed;
}

void GameManager::SetPointsInCurrentTurn(int points)
{
    this->pointsInCurrentTurn = points;
}

int GameManager::GetPointsInCurrentTurn()
{
    return this->pointsInCurrentTurn;
}
