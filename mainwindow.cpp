#include "mainwindow.h"
#include "soundeffectplayer.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "enemy.h"
#include "deck.h"

/* Main Window:
 * - Handles all the scenes (pages of StackedWidgets)
 * - Handles most of the gameplay and interaction
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LiberationBattle21)
{
    soundEffectPlayer = new SoundEffectPlayer();
    musicPlayer = new MusicPlayer();
    musicPlayer->PlayMusic(0);

    deck = new Deck();
    deck->CreateDeck();

    player = new Player();
    enemy = new Enemy();

    gameManager = new GameManager();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    QApplication::quit();
}

void MainWindow::on_StartGame_clicked()
{
    soundEffectPlayer->PlaySound(0);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Quit_clicked()
{
    soundEffectPlayer->PlaySound(1);
    QApplication::quit();
}


/* When the actual gameplay begins:
 * 1. the values of Player and Enemy objects
 * 2. the values are updated in the UI screen
 * 3. the number of total game turns is resetted to 0
*/
void MainWindow::on_AcceptGameStart_clicked()
{
    soundEffectPlayer->PlaySound(0);

    player->ResetPlayer(2000, 4, 400, 450, 480, 2);
    enemy->ResetEnemy(3000, 500);

    ui->stackedWidget->setCurrentIndex(2);
    UpdatePlayerStatus();
    UpdateEnemyStatus();
    gameManager->SetTotalTurnsPassed(0);
}

// Occurs when the Player has chosen SWORD ATTACK as their action
void MainWindow::on_SwordAttack_clicked()
{
    if (player->GetSwordsLeft() > 0)
    {
        soundEffectPlayer->PlaySound(3);
        gameManager->SetCurrentAction("SWORD ATTACK");
        player->SetSwordsLeft(player->GetSwordsLeft() - 1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->Action->setText(gameManager->GetCurrentAction());
        gameManager->SetCurrentAction(gameManager->GetCurrentAction());
        ui->Player_Phase2->setPixmap(QPixmap(":/Images/Characters/dominique-sword-prepare.png"));
        DrawCard();
    }
}

// Occurs when the Player has chosen GUN ATTACK as their action
void MainWindow::on_GunAttack_clicked()
{
    if (player->GetGunsLeft() > 0)
    {
        soundEffectPlayer->PlaySound(5);
        gameManager->SetCurrentAction("GUN ATTACK");
        player->SetGunsLeft(player->GetGunsLeft() - 1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->Action->setText(gameManager->GetCurrentAction());
        ui->Player_Phase2->setPixmap(QPixmap(":/Images/Characters/dominique-gun-prepare.png"));
        DrawCard();
    }
}

// Occurs when the Player has chosen LIFE RESTORATION as their action
void MainWindow::on_LifeRestoration_clicked()
{
    soundEffectPlayer->PlaySound(7);
    gameManager->SetCurrentAction("LIFE RESTORATION");
    ui->stackedWidget->setCurrentIndex(3);
    ui->Action->setText(gameManager->GetCurrentAction());
    ui->Player_Phase2->setPixmap(QPixmap(":/Images/Characters/dominique-health-prepare.png"));
    DrawCard();
}

// Occurs when the Player has chosen WEAPON REPAIRMENT as their action
void MainWindow::on_WeaponRepairment_clicked()
{
    soundEffectPlayer->PlaySound(9);
    gameManager->SetCurrentAction("WEAPON REPAIRMENT");
    ui->stackedWidget->setCurrentIndex(3);
    ui->Action->setText(gameManager->GetCurrentAction());
    ui->Player_Phase2->setPixmap(QPixmap(":/Images/Characters/dominique-repair-prepare.png"));
    DrawCard();
}

// Updates the attributes of the Player object, as well as all the related UI elements
// (additionally, SWORD ATTACK and GUN ATTACK buttons become hidden if the player has used all of them)
void MainWindow::UpdatePlayerStatus()
{
    player->SetSwordsLeft(player->GetSwordsLeft());
    player->SetGunsLeft(player->GetGunsLeft());

    ui->PlayerNameText->setText(player->GetName());
    ui->PlayerHP->setText((QString::number(player->GetCurrentHealthPoints()) + " / " + QString::number(player->GetFullHealthPoints())));
    ui->GunStatus->setText(QString::number(player->GetGunsLeft()) + " / " + QString::number(player->GetGunsTotal()));
    ui->SwordStatus->setText(QString::number(player->GetSwordsLeft()) + " / " + QString::number(player->GetGunsTotal()));

    AdjustWeaponButtons(ui->SwordAttack, player->GetSwordsLeft());
    AdjustWeaponButtons(ui->GunAttack, player->GetGunsLeft());
}

// Updates the UI values related to the Enemy object
void MainWindow::UpdateEnemyStatus()
{
    ui->EnemyName->setText(enemy->GetName());
    ui->EnemyHP->setText(QString::number(enemy->GetCurrentHealthPoints()) + " / " + QString::number(enemy->GetFullHealthPoints()));
    ui->EnemyHP->setText(QString::number(enemy->GetCurrentHealthPoints()) + " / " + QString::number(enemy->GetFullHealthPoints()));
}

// Resets the buttons and labels of the cardboard to its original state
void MainWindow::ResetCardBoard()
{
    AdjustDrawButtons(true);
    AdjustDrawStatusMessages(false);
    AdjustAceSelection(false);
    AdjustActionMessages(false);
}

// Represents the card-drawing action in the 21 card game section
void MainWindow::DrawCard()
{
    ResetCardBoard();
    if (gameManager->GetPointsInCurrentTurn() < 21)
    {
        int randomizedNumber = rand() % 52;
        Card drawnCard = *new Card(deck->cards[randomizedNumber]);
        QPixmap image (QString(drawnCard.GetCardImageSource()));
        gameManager->SetPointsInCurrentTurn(gameManager->GetPointsInCurrentTurn() + drawnCard.GetCardPoints());
        gameManager->SetCurrentlyDrawnCards(gameManager->GetCurrentlyDrawnCards() + 1);
        ui->TotalPointsValue->setText(QString::number(gameManager->GetPointsInCurrentTurn()));
        ui->DrawnCardNumber->setText(QString::number(gameManager->GetCurrentlyDrawnCards()));
        ui->Card->setPixmap(image);

        // Note: Ace card is worth 0 points at default (the Player must decide whether it will be 1 or 10)
        if (drawnCard.GetCardPoints() == 0)
        {
            AceCardSelection();
            return;
        }
    }
    CheckCurrentCardPoints();
}

// Shows OR Hides the SWORD ATTACK or GUN ATTACK buttons based on the Player's resources
void MainWindow::AdjustWeaponButtons(QPushButton* button, int valueNumber)
{
    if (valueNumber <= 0)
    {
        button->setEnabled(false);
    }
    else
    {
        button->setEnabled(true);
    }
}

// Shows OR Hides the Draw buttons on the Cardboard based on the boolean value
void MainWindow::AdjustDrawButtons(bool status)
{
    ui->DrawMore->setVisible(status);
    ui->DrawMore->setEnabled(status);
    ui->Stop->setVisible(status);
    ui->Stop->setEnabled(status);
}

// When the player draws an Ace, the buttons and labels for "Ace value selection"
// are activated (and the regular Draw/Stop buttons are hidden)
void MainWindow::AceCardSelection()
{
    ui->DrawMore->setEnabled(false);
    ui->DrawMore->setVisible(false);
    ui->Stop->setEnabled(false);
    ui->Stop->setVisible(false);

    ui->ActionPerfectText->setVisible(false);
    ui->ActionFailedText->setVisible(false);

    ui->AceNoticeText->setVisible(true);
    ui->Ace1->setEnabled(true);
    ui->Ace1->setVisible(true);
    ui->Ace10->setEnabled(true);
    ui->Ace10->setVisible(true);
}

// Shows OR Hides all the info labels that report the Player's card score
// (Over 21 / Equal to 21 / or when an Ace card is drawn)
void MainWindow::AdjustDrawStatusMessages(bool status)
{
    ui->ActionPerfectText->setVisible(status);
    ui->ActionFailedText->setVisible(status);
    ui->AceNoticeText->setVisible(status);
}

// Shows OR Hides the report labels regarding the Player's used action and its success
// - Happens when the card game section is over (on StackedWidget no. 4)
// - Example: "Player has used GUN ATTACK. 400 damage points inflicted to ENEMY"
void MainWindow::AdjustActionMessages(bool status)
{
    ui->ActionMessage->setVisible(status);
    ui->ActionResultMessage->setVisible(status);
}

// Shows OR Hides the buttons and labels from "the Ace value selection"
void MainWindow::AdjustAceSelection(bool status)
{
    ui->Ace1->setEnabled(status);
    ui->Ace1->setVisible(status);
    ui->Ace10->setEnabled(status);
    ui->Ace10->setVisible(status);
    ui->AceNoticeText->setVisible(status);
}

// This is used to check the Player's current score in the card game section
// - If the Player has gotten a score of 21 (or over 21), they are prevented from drawing more cards
// - Otherwise, the card game can continue normally (but the board's UI elements are resetted to default just for precautions)
void MainWindow::CheckCurrentCardPoints()
{
    if (gameManager->GetPointsInCurrentTurn() < 21)
    {
        ResetCardBoard();
    }
    else if (gameManager->GetPointsInCurrentTurn() > 21)
    {
        musicPlayer->PlayMusic(1);
        PreventDrawing(0);
    }
    else
    {
        musicPlayer->PlayMusic(2);
        PreventDrawing(1);
    }
}

// This is used to prevent the player from drawing cards, but the outcome depends on the status code:
// - If the status code is 0, the UI will inform the player of a failed action (the score is over 21)
// - If the status code is 1, the UI will inform the player of the perfect action (the score is exactly 21)
void MainWindow::PreventDrawing(int statusCode)
{
    ui->DrawMore->setVisible(false);
    ui->DrawMore->setEnabled(false);

    ui->Stop->setVisible(true);
    ui->Stop->setEnabled(true);

    ui->ActionPerfectText->setVisible(false);
    ui->AceNoticeText->setVisible(false);

    if (statusCode == 0) { ui->ActionFailedText->setVisible(true);}
    if (statusCode == 1) { ui->ActionPerfectText->setVisible(true);}
}

// This occurs when the Player has pressed "Draw More" button
void MainWindow::on_DrawMore_clicked()
{
    soundEffectPlayer->PlaySound(0);
    DrawCard();
}


// This occurs when the Player has selected the Ace card's value to be 1
void MainWindow::on_Ace1_clicked()
{
    soundEffectPlayer->PlaySound(0);
    gameManager->SetPointsInCurrentTurn(gameManager->GetPointsInCurrentTurn() + 1);
    ui->TotalPointsValue->setText(QString::number(gameManager->GetPointsInCurrentTurn()));
    AdjustAceSelection(false);
    CheckCurrentCardPoints();
}

// This occurs when the Player has selected the Ace card's value to be 10
void MainWindow::on_Ace10_clicked()
{
    soundEffectPlayer->PlaySound(0);
    gameManager->SetPointsInCurrentTurn(gameManager->GetPointsInCurrentTurn() + 10);
    ui->TotalPointsValue->setText(QString::number(gameManager->GetPointsInCurrentTurn()));
    AdjustAceSelection(false);
    CheckCurrentCardPoints();
}

// This occurs when the Player has stopped drawing any more cards on their turn
// - This activates the Stacked Widget no. 4, which:
//   1) Reports the player's chosen action
//   2) Shows the effect calculations of this action (based on the results of 21 card game section)
//   3) Activates the correct sound effect and
//   4) Inserts the correct Player / Enemy images
 void MainWindow::on_Stop_clicked()
{
    soundEffectPlayer->PlaySound(0);
    ResetCardBoard();
    if (gameManager->GetPointsInCurrentTurn() > 21)
    {
        on_EnemyTurnButton_clicked();
        return;
    }

    ui->stackedWidget->setCurrentIndex(4);
    ui->ActionMessage->setVisible(true);
    ui->ActionMessage->setText(player->GetName() + " used " + gameManager->GetCurrentAction());

    float actionCounter = 0;

    if (gameManager->GetPointsInCurrentTurn() < 21)
    {
        actionCounter = ((float)gameManager->GetPointsInCurrentTurn() / 10.0f);
    }
    else if (gameManager->GetPointsInCurrentTurn() == 21)
    {
        actionCounter = 3.0f;
    }

    ui->ActionResultMessage->setVisible(true);

    if (gameManager->GetCurrentAction() == "SWORD ATTACK")
    {
        soundEffectPlayer->PlaySound(4);
        int inflictedDamage = player->GetSwordDamage() * actionCounter;
        enemy->DecreaseHealth(inflictedDamage);
        ui->Player_Phase3->setPixmap(QPixmap(":/Images/Characters/dominique-sword-slash.png"));
        ui->Enemy_Phase3->setPixmap(QPixmap(":/Images/Characters/nosferatu_damage.png"));
        ui->ActionResultMessage->setText(QString::number(inflictedDamage) + " damage inflicted to " + enemy->GetName());
    }

    if (gameManager->GetCurrentAction() == "GUN ATTACK")
    {
        soundEffectPlayer->PlaySound(6);
        int inflictedDamage = player->GetGunDamage() * actionCounter;
        enemy->DecreaseHealth(inflictedDamage);
        ui->Player_Phase3->setPixmap(QPixmap(":/Images/Characters/dominique-gun-shoot"));
        ui->Enemy_Phase3->setPixmap(QPixmap(":/Images/Characters/nosferatu_damage.png"));
        ui->ActionResultMessage->setText(QString::number(inflictedDamage) + " damage inflicted to " + enemy->GetName());
    }

    if (gameManager->GetCurrentAction() == "LIFE RESTORATION")
    {
        soundEffectPlayer->PlaySound(8);
        QString message = *new QString();
        int increasedHealth = player->GetHpRestorePoints() * actionCounter;

        if ((gameManager->GetPointsInCurrentTurn() < 21))
        {
            if ((player->GetCurrentHealthPoints() + increasedHealth) >= (player->GetFullHealthPoints()))
            {
                player->SetCurrentHealthPoints(player->GetFullHealthPoints());
            }
            else
            {
                player->SetCurrentHealthPoints(player->GetCurrentHealthPoints() + increasedHealth);
            }
            message = *new QString("Health increased by " + QString::number(increasedHealth) + " POINTS");
        }
        else if (gameManager->GetPointsInCurrentTurn() == 21)
        {
            player->SetFullHealthPoints(player->GetFullHealthPoints() * 2);
            player->SetCurrentHealthPoints(player->GetFullHealthPoints());
            message = *new QString("Health fully restored and multiplied");
        }
        ui->Player_Phase3->setPixmap(QPixmap(":/Images/Characters/dominique-health-drink.png"));
        ui->Enemy_Phase3->setPixmap(QPixmap(":/Images/Characters/nosferatu_idle.png"));
        ui->ActionResultMessage->setText(message);
    }

    if (gameManager->GetCurrentAction() == "WEAPON REPAIRMENT")
    {
        soundEffectPlayer->PlaySound(10);
        int increasedWeapons = player->GetWeaponRepairPoints() * actionCounter;
        if (gameManager->GetPointsInCurrentTurn() < 21)
        {
            if ((player->GetGunsLeft() + increasedWeapons) >= (player->GetGunsTotal()))
            {
                player->SetGunsLeft(player->GetGunsTotal());
            }
            if ((player->GetSwordsLeft() + increasedWeapons) >= (player->GetSwordsTotal()))
            {
                player->SetSwordsLeft(player->GetSwordsTotal());
            }

            if ((player->GetGunsLeft() + increasedWeapons) < (player->GetGunsTotal()))
            {
                player->SetGunsLeft(player->GetGunsLeft() + increasedWeapons);
            }
            if ((player->GetSwordsLeft() + increasedWeapons) < (player->GetSwordsTotal()))
            {
                player->SetSwordsLeft(player->GetSwordsLeft() + increasedWeapons);
            }
            ui->ActionResultMessage->setText("Capacity of weapons increased by " + QString::number(increasedWeapons) + " UNITS");
        }
        else if (gameManager->GetPointsInCurrentTurn() == 21)
        {
            player->SetGunsTotal(player->GetGunsTotal() * 2);
            player->SetGunsLeft(player->GetGunsTotal());
            player->SetSwordsTotal(player->GetSwordsTotal() * 2);
            player->SetSwordsLeft(player->GetSwordsTotal());
            ui->ActionResultMessage->setText("Weapons repaired and leveled up successfully");
        }
        ui->Player_Phase3->setPixmap(QPixmap(":/Images/Characters/dominique-repair-complete.png"));
        ui->Enemy_Phase3->setPixmap(QPixmap(":/Images/Characters/nosferatu_idle.png"));
    }
    AdjustActionMessages(true);
    UpdatePlayerStatus();
}


// This represents the Enemy's turn
// - The Enemy's action and damage points are reported
// - The Images of the Enemy and Player are also updated
void MainWindow::on_EnemyTurnButton_clicked()
{
    soundEffectPlayer->PlaySound(11);
    if (enemy->GetCurrentHealthPoints() > 0) {
        ui->stackedWidget->setCurrentIndex(5);
        ui->EnemyActionMessage->setText(enemy->GetName() + " used DESTRUCTION RAY");
        player->SetCurrentHealthPoints((player->GetCurrentHealthPoints()) - (enemy->GetDamagePoints()));
        ui->EnemyActionResultMessage->setText(QString::number(enemy->GetDamagePoints()) + " damage inflicted to " + player->GetName());
    }
    else if (enemy->GetCurrentHealthPoints() <= 0)
    {
        on_EndGameTurnButton_clicked();
    }
    AdjustActionMessages(true);
    UpdatePlayerStatus();
}

// This occurs when the Enemy's turn has ended
// - If the Player or Enemy's health points are 0:
//   --> the game will switch to either "Game Over" or "Congratulations" sections
// - If both are still alive, the new turn will begin (returning to the "Action Selection" phase):
//   --> the Game Manager will reset the card scores and update the number of total turns
//   --> Additionally, the Card Board is resetted, and the Player / Enemy Ui elements are updated
void MainWindow::on_EndGameTurnButton_clicked()
{
    soundEffectPlayer->PlaySound(0);
    gameManager->SetCurrentlyDrawnCards(0);
    gameManager->SetPointsInCurrentTurn(0);
    gameManager->SetTotalTurnsPassed(gameManager->GetTotalTurnsPassed() + 1);

    if (player->GetCurrentHealthPoints() > 0 && enemy->GetCurrentHealthPoints() > 0)
    {
        ui->stackedWidget->setCurrentIndex(2);
        ResetCardBoard();
        UpdatePlayerStatus();
        UpdateEnemyStatus();
    }
    else if (player->GetCurrentHealthPoints() > 0 && enemy->GetCurrentHealthPoints() <= 0)
    {
        musicPlayer->PlayMusic(4);
        ui->stackedWidget->setCurrentIndex(6);
        ui->Player_Name_FinalPhase->setText(player->GetName());
        ui->ClearedInTurns->setText("IN " + QString::number(gameManager->GetTotalTurnsPassed()) + " TURNS");
    }
    else if (player->GetCurrentHealthPoints() <= 0 && enemy->GetCurrentHealthPoints() > 0)
    {
        musicPlayer->PlayMusic(3);
        ui->stackedWidget->setCurrentIndex(7);
    }
}

// This occurs when "Play Again" button is clicked
void MainWindow::on_PlayAgain_clicked()
{
    soundEffectPlayer->PlaySound(0);
    on_AcceptGameStart_clicked();
}

// This occurs when "Exit to Menu" button is clicked
void MainWindow::on_ExitToMenu_clicked()
{
    soundEffectPlayer->PlaySound(1);
    ui->stackedWidget->setCurrentIndex(0);
}

// This occurs when Player return back to Menu from certain sections
void MainWindow::on_BackToMenu_clicked()
{
    soundEffectPlayer->PlaySound(1);
    ui->stackedWidget->setCurrentIndex(0);
}

// This occurs when the Player has pressed "Give Up" button
void MainWindow::on_GiveUp_clicked()
{
    soundEffectPlayer->PlaySound(1);
    ui->stackedWidget->setCurrentIndex(0);
}

// This occurs when the Player wants to try again after Game Over
void MainWindow::on_GameOverTryAgain_clicked()
{
    soundEffectPlayer->PlaySound(0);
    on_AcceptGameStart_clicked();
}

// This occurs when the Player has pressed "Give Up" button when the Game is Over
void MainWindow::on_GameOverGiveUp_clicked()
{
    soundEffectPlayer->PlaySound(1);
    ui->stackedWidget->setCurrentIndex(0);
}

// This occurs when the Player has given a new name to their character
// and pressed a separate "SAVE" button
void MainWindow::on_SaveNameButton_clicked()
{
    if (ui->givePlayerNameBox->text().trimmed() != "")
    {
        player->SetName(ui->givePlayerNameBox->text().trimmed().toUpper());
        soundEffectPlayer->PlaySound(2);
    }
}

// This occurs when the Player returns from the separate "Credits" section
void MainWindow::on_ReturnFromCredits_clicked()
{
    soundEffectPlayer->PlaySound(1);
    ui->stackedWidget->setCurrentIndex(0);
}


// This occurs when the Player presses "Credits" button in the Main Menu
void MainWindow::on_CreditsButton_clicked()
{
    soundEffectPlayer->PlaySound(0);
    ui->stackedWidget->setCurrentIndex(8);
}

