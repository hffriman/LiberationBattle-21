#include "player.h"

Player::Player() {

    name = "Dominique";
    healthPoints = 1000.0f;
    damagePoints = 100.0f;
}


void Player::SetName(QString finalName) {
    this->name = finalName;
}

QString Player::GetName()
{
    return this->name;
}

void Player::DecreaseHealth(float damage)
{
    healthPoints -= damage;
}
