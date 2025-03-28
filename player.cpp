#include "player.h"

Player::Player() {

    name = "DOMINIQUE";
    healthPoints = 2000.0f;
    swordDamage = 300.0f;
    gunDamage = 400.0f;
    guardPoints = 0;
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


int Player::GetSwordDamage()
{
    return this->swordDamage;
}

void Player::SetSwordDamage(int damage)
{
    this->swordDamage = damage;
}

int Player::GetGunDamage()
{
    return this->gunDamage;
}

void Player::SetGunDamage(int damage)
{
    this->gunDamage = damage;
}

int Player::GetGuardPoints()
{
    return this->guardPoints;
}

void Player::SetGuardPoints(int points)
{
    this->guardPoints = points;
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


