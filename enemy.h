#ifndef ENEMY_H
#define ENEMY_H
#include <Qstring>
#include <QWidget>

class Enemy
{
public:
    Enemy();
    void SetName(QString finalName);
    QString GetName();
    void ResetEnemy(int healthPoints, int damage);
    void SetCurrentHealthPoints(int points);
    int GetCurrentHealthPoints();
    void SetFullHealthPoints(int points);
    int GetFullHealthPoints();
    void SetDamagePoints(int points);
    int GetDamagePoints();
    void SetImage(QWidget* image);
    void DecreaseHealth(float damage);

private:
    QString name;
    int currentHealthPoints;
    int fullHealthPoints;
    int damagePoints;
    QWidget* enemyImage;
};

#endif // ENEMY_H
