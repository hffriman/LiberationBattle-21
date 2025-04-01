#include "player.h"

/* Player:
 * - Handles the player-related data, such as:
 *   1) Player character's name ("DOMINIQUE" being the default name)
 *   2) Player's current health points and full health points
 *   3) Player's damage points inflicted by SwordAttack and GunAttack
 *   4) Player's health restore and weapon repairment points (will be multiplied based on the card game results)
 *   5) Player's sword and gun resources (as well as their current maximum limits)
 */
Player::Player() {

    name = "DOMINIQUE";
    currentHealthPoints = 2000;
    fullHealthPoints = 2000;
    swordDamage = 400;
    gunDamage = 450;
    hpRestorePoints = 480;
    weaponRepairPoints = 2;
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

// Used to initialize (or reset) the player's overall resources and stats
void Player::ResetPlayer(int healthPoints, int weapons, int swordDamage, int gunDamage, int hpRestorePoints, int weaponRepairPoints)
{
    this->SetCurrentHealthPoints(healthPoints);
    this->SetFullHealthPoints(healthPoints);

    this->SetSwordsLeft(weapons);
    this->SetSwordsTotal(weapons);

    this->SetGunsLeft(weapons);
    this->SetGunsTotal(weapons);

    this->SetSwordDamage(swordDamage);
    this->SetGunDamage(gunDamage);
    this->SetHpRestorePoints(hpRestorePoints);
    this->SetWeaponRepairPoints(weaponRepairPoints);
}

void Player::SetCurrentHealthPoints(int points)
{
    this->currentHealthPoints = points;
}

int Player::GetCurrentHealthPoints()
{
    return this->currentHealthPoints;
}

void Player::SetFullHealthPoints(int points)
{
    this->fullHealthPoints = points;
}

int Player::GetFullHealthPoints()
{
    return this->fullHealthPoints;
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

int Player::GetHpRestorePoints()
{
    return this->hpRestorePoints;
}

void Player::SetHpRestorePoints(int points)
{
    this->hpRestorePoints = points;
}

int Player::GetWeaponRepairPoints()
{
    return this->weaponRepairPoints;
}

void Player::SetWeaponRepairPoints(int points)
{
    this->weaponRepairPoints = points;
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




