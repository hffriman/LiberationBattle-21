#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include "enemy.h"
#include "deck.h"
#include "gamemanager.h"
#include <QPushButton>
#include "soundeffectplayer.h"
#include "musicplayer.h"

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
    SoundEffectPlayer* soundEffectPlayer;
    MusicPlayer* musicPlayer;

private slots:
    void on_StartGame_clicked();

    void on_Quit_clicked();

    void on_AcceptGameStart_clicked();

    void on_SwordAttack_clicked();

    void on_GunAttack_clicked();

    void UpdatePlayerStatus();

    void UpdateEnemyStatus();

    void ResetCardBoard();

    void DrawCard();

    void AdjustWeaponButtons(QPushButton* button, int numberValue);

    void AdjustDrawButtons(bool status);

    void AdjustDrawStatusMessages(bool status);

    void AdjustActionMessages(bool status);

    void CheckCurrentCardPoints();

    void PreventDrawing(int statusCode);

    void AceCardSelection();

    void AdjustAceSelection(bool status);

    void on_DrawMore_clicked();

    void on_Ace1_clicked();

    void on_Ace10_clicked();

    void on_Stop_clicked();

    void on_LifeRestoration_clicked();

    void on_WeaponRepairment_clicked();

    void on_EnemyTurnButton_clicked();

    void on_EndGameTurnButton_clicked();

    void on_PlayAgain_clicked();

    void on_ExitToMenu_clicked();

    void on_BackToMenu_clicked();

    void on_GiveUp_clicked();

    void on_GameOverTryAgain_clicked();

    void on_GameOverGiveUp_clicked();

    void on_SaveNameButton_clicked();

    void on_ReturnFromCredits_clicked();

    void on_CreditsButton_clicked();

private:
    Ui::LiberationBattle21 *ui;
};
#endif // MAINWINDOW_H
