#include "gamemanager.h"

/* GameManager:
 * - Handles the game-related data, such as:
 *   1) the number of cards that the player has drawn on their current turn
 *   2) the total number of turns the player has taken in the game
 *   3) the points that the player has gotten from the cards on their current turn
*/
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

void GameManager::SetCurrentAction(QString actionName)
{
    this->currentAction = actionName;
}

QString GameManager::GetCurrentAction()
{
    return this->currentAction.toUpper();
}
