#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

class Player
{
public:
    Player();
    void SetName(QString finalName);
    QString GetName();
    void DecreaseHealth(float damage);

private:
    QString name;
    float healthPoints;
    float damagePoints;
};

#endif // PLAYER_H
