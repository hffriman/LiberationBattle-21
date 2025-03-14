#include "enemy.h"

Enemy::Enemy() {

    name = "Nosferatu";
    healthPoints = 1000.0f;
    damagePoints = 200.0f;
}


void Enemy::SetName(QString finalName)
{
    this->name = finalName;
}

QString Enemy::GetName()
{
    return this->name;
}

void Enemy::SetImage(QWidget* image)
{
    this->enemyImage = image;
}

void Enemy::DecreaseHealth(float damage)
{
    healthPoints -= damage;
}
