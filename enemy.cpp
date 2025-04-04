#include "enemy.h"

/* Enemy:
 * - Represents the player's opponent
 * - Has some similarities with the Player class (but is much more simpler)
 */
Enemy::Enemy() {

    name = "NOSFERATU";
    currentHealthPoints = 3000;
    fullHealthPoints = 3000;
    damagePoints = 500;
}


void Enemy::SetName(QString finalName)
{
    this->name = finalName;
}

QString Enemy::GetName()
{
    return this->name;
}

void Enemy::ResetEnemy(int healthPoints, int damage)
{
    this->SetCurrentHealthPoints(healthPoints);
    this->SetFullHealthPoints(healthPoints);
    this->SetDamagePoints(damage);
}

void Enemy::SetImage(QWidget* image)
{
    this->enemyImage = image;
}

void Enemy::SetCurrentHealthPoints(int points)
{
    this->currentHealthPoints = points;
}

int Enemy::GetCurrentHealthPoints()
{
    return this->currentHealthPoints;
}

void Enemy::SetFullHealthPoints(int points)
{
    this->fullHealthPoints = points;
}

int Enemy::GetFullHealthPoints()
{
    return this->fullHealthPoints;
}

void Enemy::SetDamagePoints(int points)
{
    this->damagePoints = points;
}

int Enemy::GetDamagePoints()
{
    return this->damagePoints;
}

void Enemy::DecreaseHealth(float damage)
{
    currentHealthPoints -= damage;
}
