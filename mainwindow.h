#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include "enemy.h"
#include "deck.h"
#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LiberationBattle21;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Player* player;
    Enemy* enemy;
    Deck* deck;
    GameManager* gameManager;

private slots:
    void on_StartGame_clicked();

    void on_Quit_clicked();

    void on_Accept_clicked();

    void on_SwordAttack_clicked();

    void on_GunAttack_clicked();

    void UpdatePlayerStatus();

    void ResetCardBoard();

    void DrawCard();

    void AceCardSelection();

    void on_DrawMore_clicked();

private:
    Ui::LiberationBattle21 *ui;
};
#endif // MAINWINDOW_H
