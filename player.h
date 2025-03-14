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

    void SetSwordsLeft(int value);
    int GetSwordsLeft();

    void SetSwordsTotal(int value);
    int GetSwordsTotal();

    void SetGunsLeft(int value);
    int GetGunsLeft();

    void SetGunsTotal(int value);
    int GetGunsTotal();

    void SetImage(QWidget* image);
    void DecreaseHealth(float damage);

private:
    QString name;
    float healthPoints;
    float damagePoints;
    QWidget* playerImage;
    int swordsTotal;
    int swordsLeft;
    int gunsTotal;
    int gunsLeft;
};

#endif // PLAYER_H
