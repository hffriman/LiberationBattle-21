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
    ui->setupUi(this);

    deck = new Deck();
    deck->CreateDeck();

    player = new Player();
    enemy = new Enemy();
    gameManager = new GameManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartGame_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Quit_clicked()
{
    delete ui;
    this->close();
}

void MainWindow::on_Accept_clicked()
{
    player->SetName(ui->playerName->toPlainText());
    ui->stackedWidget->setCurrentIndex(2);

    ui->PlayerNameText->setText(player->GetName());

    player->SetImage(ui->Player);
    enemy->SetImage(ui->Enemy);

    player->SetGunsLeft(player->GetGunsLeft());
    gameManager->SetTotalTurnsPassed(1);
    UpdatePlayerStatus();
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
        DrawCard();
    }
}


void MainWindow::on_LifeRestoration_clicked()
{
    gameManager->SetCurrentAction("LIFE RESTORATION");
    ui->stackedWidget->setCurrentIndex(3);
    ui->Action->setText(gameManager->GetCurrentAction());
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
    gameManager->SetCurrentlyDrawnCards(0);
    gameManager->SetPointsInCurrentTurn(0);
    gameManager->SetTotalTurnsPassed(gameManager->GetTotalTurnsPassed() + 1);

    QString updatedSwordStatusText = *new QString();
    updatedSwordStatusText.append(QString::number(player->GetSwordsLeft()));
    updatedSwordStatusText.append(" / ");
    updatedSwordStatusText.append(QString::number(player->GetSwordsTotal()));
    ui->SwordStatus->setText(updatedSwordStatusText);

    QString updatedGunStatusText = *new QString();
    updatedGunStatusText.append(QString::number(player->GetGunsLeft()));
    updatedGunStatusText.append(" / ");
    updatedGunStatusText.append((QString::number(player->GetGunsTotal())));
    ui->GunStatus->setText(updatedGunStatusText);
}

void MainWindow::ResetCardBoard()
{
    ui->DrawMore->setVisible(true);
    ui->DrawMore->setEnabled(true);

    ui->Stop->setVisible(true);
    ui->Stop->setEnabled(true);

    ui->ActionPerfectText->setVisible(false);
    ui->ActionFailedText->setVisible(false);

    ui->AceNoticeText->setVisible(false);
    ui->Ace1->setVisible(false);
    ui->Ace1->setEnabled(false);
    ui->Ace10->setVisible(false);
    ui->Ace10->setEnabled(false);

    ui->ActionMessage->setVisible(false);
    ui->ActionResultMessage->setVisible(false);
}

void MainWindow::DrawCard()
{
    if (gameManager->GetPointsInCurrentTurn() < 21)
    {
        int randomizedNumber = rand() % 53;
        Card drawnCard = deck->cards[randomizedNumber];
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

void MainWindow::AceCardSelection()
{
    ui->DrawMore->setEnabled(false);
    ui->DrawMore->setVisible(false);
    ui->Stop->setEnabled(false);
    ui->Stop->setVisible(false);

    ui->AceNoticeText->setVisible(true);

    ui->Ace1->setEnabled(true);
    ui->Ace1->setVisible(true);
    ui->Ace10->setEnabled(true);
    ui->Ace10->setVisible(true);
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
    if (statusCode == 0)
    {
        ui->DrawMore->setVisible(false);
        ui->DrawMore->setEnabled(false);
        ui->ActionFailedText->setVisible(true);
    }
    if (statusCode == 1)
    {
        ui->DrawMore->setVisible(false);
        ui->DrawMore->setEnabled(false);
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
    CheckCurrentCardPoints();
}

void MainWindow::on_Ace10_clicked()
{
    gameManager->SetPointsInCurrentTurn(gameManager->GetPointsInCurrentTurn() + 10);
    ui->TotalPointsValue->setText(QString::number(gameManager->GetPointsInCurrentTurn()));
    CheckCurrentCardPoints();
}

void MainWindow::on_Stop_clicked()
{
    ResetCardBoard();
    ui->stackedWidget->setCurrentIndex(4);
    ui->ActionMessage->setText("YOU USED " + gameManager->GetCurrentAction());

    float actionCounter = 0;

    if (gameManager->GetPointsInCurrentTurn() <= 21)
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
        qDebug() << gameManager->GetPointsInCurrentTurn() << " + " << inflictedDamage << " and " << actionCounter;
        enemy->DecreaseHealth(inflictedDamage);
        ui->ActionResultMessage->setText(QString::number(inflictedDamage) + " DAMAGE INFLICTED TO " + enemy->GetName());
    }

    if (gameManager->GetCurrentAction() == "GUN ATTACK")
    {
        int inflictedDamage = player->GetGunDamage() * actionCounter;
        enemy->DecreaseHealth(inflictedDamage);
        ui->ActionResultMessage->setText(QString::number(inflictedDamage) + " DAMAGE INFLICTED TO " + enemy->GetName());
    }
}
