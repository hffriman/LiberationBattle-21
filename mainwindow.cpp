#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "enemy.h"
#include "deck.h"
#include <QFile>
#include <QJsonParseError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LiberationBattle21)
{
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
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Quit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_AcceptGameStart_clicked()
{
    player->ResetPlayer(2000, 4, 400, 450, 480, 2);
    enemy->ResetEnemy(3000, 500);

    player->SetName(ui->givePlayerNameBox->toPlainText().toUpper());

    ui->stackedWidget->setCurrentIndex(2);

    UpdatePlayerStatus();
    UpdateEnemyStatus();

    gameManager->SetTotalTurnsPassed(1);
}

void MainWindow::on_SwordAttack_clicked()
{
    if (player->GetSwordsLeft() > 0)
    {
        gameManager->SetCurrentAction("SWORD ATTACK");
        player->SetSwordsLeft(player->GetSwordsLeft() - 1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->Action->setText(gameManager->GetCurrentAction());
        gameManager->SetCurrentAction(gameManager->GetCurrentAction());
        DrawCard();
    }
}

void MainWindow::on_GunAttack_clicked()
{
    if (player->GetGunsLeft() > 0)
    {
        gameManager->SetCurrentAction("GUN ATTACK");
        player->SetGunsLeft(player->GetGunsLeft() - 1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->Action->setText(gameManager->GetCurrentAction());
        ui->Player_Phase2->setPixmap(QPixmap(":/Images/Characters/dominique-gun-prepare.png"));
        DrawCard();
    }
}

void MainWindow::on_LifeRestoration_clicked()
{
    gameManager->SetCurrentAction("LIFE RESTORATION");
    ui->stackedWidget->setCurrentIndex(3);
    ui->Action->setText(gameManager->GetCurrentAction());
    ui->Player_Phase2->setPixmap(QPixmap(":/Images/Characters/dominique-health-prepare.png"));
    DrawCard();
}

void MainWindow::on_WeaponRepairment_clicked()
{
    gameManager->SetCurrentAction("WEAPON REPAIRMENT");
    ui->stackedWidget->setCurrentIndex(3);
    ui->Action->setText(gameManager->GetCurrentAction());
    DrawCard();
}

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

void MainWindow::UpdateEnemyStatus()
{
    ui->EnemyName->setText(enemy->GetName());
    ui->EnemyHP->setText(QString::number(enemy->GetCurrentHealthPoints()) + " / " + QString::number(enemy->GetFullHealthPoints()));
    ui->EnemyHP->setText(QString::number(enemy->GetCurrentHealthPoints()) + " / " + QString::number(enemy->GetFullHealthPoints()));
}

void MainWindow::ResetCardBoard()
{
    AdjustDrawButtons(true);
    AdjustDrawStatusMessages(false);
    AdjustAceSelection(false);
    AdjustActionMessages(false);
}

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

        if (drawnCard.GetCardPoints() == 0)
        {
            AceCardSelection();
            return;
        }
    }
    CheckCurrentCardPoints();
}


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

void MainWindow::AdjustDrawButtons(bool status)
{
    ui->DrawMore->setVisible(status);
    ui->DrawMore->setEnabled(status);
    ui->Stop->setVisible(status);
    ui->Stop->setEnabled(status);
}

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

void MainWindow::AdjustDrawStatusMessages(bool status)
{
    ui->ActionPerfectText->setVisible(status);
    ui->ActionFailedText->setVisible(status);
    ui->AceNoticeText->setVisible(status);
}

void MainWindow::AdjustActionMessages(bool status)
{
    ui->ActionMessage->setVisible(status);
    ui->ActionResultMessage->setVisible(status);
}

void MainWindow::AdjustAceSelection(bool status)
{
    ui->Ace1->setEnabled(status);
    ui->Ace1->setVisible(status);
    ui->Ace10->setEnabled(status);
    ui->Ace10->setVisible(status);
    ui->AceNoticeText->setVisible(status);
}

void MainWindow::CheckCurrentCardPoints()
{
    if (gameManager->GetPointsInCurrentTurn() < 21)
    {
        ResetCardBoard();
    }
    else if (gameManager->GetPointsInCurrentTurn() > 21)
    {
        PreventDrawing(0);
    }
    else
    {
        PreventDrawing(1);
    }
}

// If statusCode is 0, the ui will inform the player of a failed action
// If statusCode is 1, the ui will inform the player of the perfect action
void MainWindow::PreventDrawing(int statusCode)
{
    ui->DrawMore->setVisible(false);
    ui->DrawMore->setEnabled(false);

    ui->Stop->setVisible(true);
    ui->Stop->setEnabled(true);

    ui->ActionPerfectText->setVisible(false);
    ui->AceNoticeText->setVisible(false);

    if (statusCode == 0)
    {
        ui->ActionFailedText->setVisible(true);
    }
    if (statusCode == 1)
    {
        ui->ActionPerfectText->setVisible(true);
    }
}

void MainWindow::on_DrawMore_clicked()
{
    DrawCard();
}

void MainWindow::on_Ace1_clicked()
{
    gameManager->SetPointsInCurrentTurn(gameManager->GetPointsInCurrentTurn() + 1);
    ui->TotalPointsValue->setText(QString::number(gameManager->GetPointsInCurrentTurn()));
    AdjustAceSelection(false);
    CheckCurrentCardPoints();
}

void MainWindow::on_Ace10_clicked()
{
    gameManager->SetPointsInCurrentTurn(gameManager->GetPointsInCurrentTurn() + 10);
    ui->TotalPointsValue->setText(QString::number(gameManager->GetPointsInCurrentTurn()));
    AdjustAceSelection(false);
    CheckCurrentCardPoints();
}

void MainWindow::on_Stop_clicked()
{
    ResetCardBoard();
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
        int inflictedDamage = player->GetSwordDamage() * actionCounter;
        enemy->DecreaseHealth(inflictedDamage);
        ui->ActionResultMessage->setText(QString::number(inflictedDamage) + " damage inflicted to " + enemy->GetName());
    }

    if (gameManager->GetCurrentAction() == "GUN ATTACK")
    {
        int inflictedDamage = player->GetGunDamage() * actionCounter;
        enemy->DecreaseHealth(inflictedDamage);
        ui->Player_Phase3->setPixmap(QPixmap(":/Images/Characters/dominique-gun-shoot"));
        ui->ActionResultMessage->setText(QString::number(inflictedDamage) + " damage inflicted to " + enemy->GetName());
    }

    if (gameManager->GetCurrentAction() == "LIFE RESTORATION")
    {
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
        ui->ActionResultMessage->setText(message);
    }

    if (gameManager->GetCurrentAction() == "WEAPON REPAIRMENT")
    {
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
        else if (gameManager->GetPointsInCurrentTurn() > 21)
        {
            ui->ActionResultMessage->setText("Weapon repairment failed");
        }
    }
    AdjustActionMessages(true);
    UpdatePlayerStatus();
}

void MainWindow::on_EnemyTurnButton_clicked()
{
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

void MainWindow::on_EndGameTurnButton_clicked()
{
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
        ui->stackedWidget->setCurrentIndex(6);
        ui->GameOverHeader->setText("CONGRATULATIONS");
        ui->GameOverExplanation->setText(player->GetName() + " has defeated " + enemy->GetName());
    }
    else if (player->GetCurrentHealthPoints() <= 0 && enemy->GetCurrentHealthPoints() > 0)
    {
        ui->stackedWidget->setCurrentIndex(6);
        ui->GameOverHeader->setText("GAME OVER");
        ui->GameOverExplanation->setText(player->GetName() + " has lost to " + enemy->GetName());
    }
}

void MainWindow::on_PlayAgain_clicked()
{
    on_AcceptGameStart_clicked();
}

void MainWindow::on_ExitToMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_BackToMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_GiveUp_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

