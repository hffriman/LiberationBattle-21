#ifndef ENEMY_H
#define ENEMY_H
#include <Qstring>

class Enemy
{
public:
    Enemy();
    void SetName(QString finalName);
    QString GetName();
    void DecreaseHealth(float damage);

private:
    QString name;
    float healthPoints;
    float damagePoints;
};

#endif // ENEMY_H
