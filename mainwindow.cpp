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
        ResetCardBoard();
        player->SetSwordsLeft(player->GetSwordsLeft() - 1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->Action->setText("SWORD ATTACK");
        ResetCardBoard();
        DrawCard();
    }
}

void MainWindow::on_GunAttack_clicked()
{
    if (player->GetGunsLeft() > 0)
    {
        ResetCardBoard();
        player->SetGunsLeft(player->GetGunsLeft() - 1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->Action->setText("GUN ATTACK");
        DrawCard();
    }
}

void MainWindow::UpdatePlayerStatus()
{
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
    ui->ActionPerfectText->setVisible(false);
    ui->ActionFailedText->setVisible(false);
    ui->AceNoticeText->setVisible(false);
    ui->Ace1->setVisible(false);
    ui->Ace1->setEnabled(false);
    ui->Ace10->setVisible(false);
    ui->Ace10->setEnabled(false);
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
    if (gameManager->GetPointsInCurrentTurn() > 21)
    {
        ui->DrawMore->setVisible(false);
        ui->DrawMore->setEnabled(false);
        ui->ActionFailedText->setVisible(true);
    }

    if (gameManager->GetPointsInCurrentTurn() == 21)
    {
        ui->DrawMore->setVisible(false);
        ui->DrawMore->setEnabled(false);
        ui->ActionPerfectText->setVisible(true);
    }

    qDebug() << gameManager->GetPointsInCurrentTurn();
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

void MainWindow::on_DrawMore_clicked()
{
    DrawCard();
}
