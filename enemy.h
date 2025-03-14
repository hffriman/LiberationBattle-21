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
    void SetImage(QWidget* image);
    void DecreaseHealth(float damage);

private:
    QString name;
    float healthPoints;
    float damagePoints;
    QWidget* enemyImage;
};

#endif // ENEMY_H
