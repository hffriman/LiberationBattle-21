#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include <QWidget>

class Player
{
public:
    Player();

    void SetName(QString finalName);
    QString GetName();

    void ResetPlayer(int healthPoints, int weapons, int swordDamage, int gunDamage);

    void SetSwordsLeft(int value);
    int GetSwordsLeft();

    void SetSwordsTotal(int value);
    int GetSwordsTotal();

    void SetGunsLeft(int value);
    int GetGunsLeft();

    void SetGunsTotal(int value);
    int GetGunsTotal();

    void SetImage(QWidget* image);

    void SetCurrentHealthPoints(int points);
    int GetCurrentHealthPoints();

    void SetFullHealthPoints(int points);
    int GetFullHealthPoints();

    void SetSwordDamage(int damage);
    int GetSwordDamage();

    void SetGunDamage(int damage);
    int GetGunDamage();

    void SetGuardPoints(int points);
    int GetGuardPoints();

private:
    QString name;
    int currentHealthPoints;
    int fullHealthPoints;
    int swordDamage;
    int gunDamage;
    int guardPoints;
    QWidget* playerImage;
    int swordsTotal;
    int swordsLeft;
    int gunsTotal;
    int gunsLeft;
};

#endif // PLAYER_H
