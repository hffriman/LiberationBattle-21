#include "player.h"

Player::Player() {

    name = "Dominique";
    healthPoints = 1000.0f;
    damagePoints = 100.0f;
    swordsTotal = 4;
    swordsLeft = 4;
    gunsTotal = 4;
    gunsLeft = 4;

}


void Player::SetName(QString finalName)
{
    this->name = finalName;
}

QString Player::GetName()
{
    return this->name;
}

int Player::GetSwordsTotal()
{
    return this->swordsTotal;
}

void Player::SetSwordsTotal(int value)
{
    this->swordsTotal = value;
}

int Player::GetSwordsLeft()
{
    return this->swordsLeft;
}

void Player::SetSwordsLeft(int value)
{
    this->swordsLeft = value;
}

int Player::GetGunsTotal()
{
    return this->gunsTotal;
}

void Player::SetGunsTotal(int value)
{
    this->gunsTotal = value;
}

int Player::GetGunsLeft()
{
    return this->gunsLeft;
}

void Player::SetGunsLeft(int value)
{
    this->gunsLeft = value;
}

void Player::SetImage(QWidget* image)
{
    this->playerImage = image;
}


void Player::DecreaseHealth(float damage)
{
    healthPoints -= damage;
}


