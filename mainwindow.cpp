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
        gameManager->SetCurrentlyDrawnCards(1);
        player->SetSwordsLeft(player->GetSwordsLeft() - 1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->Action->setText("SWORD ATTACK");
        DrawCard();
    }
}

void MainWindow::on_GunAttack_clicked()
{
    gameManager->SetCurrentlyDrawnCards(1);
    player->SetGunsLeft(player->GetGunsLeft() - 1);
    ui->stackedWidget->setCurrentIndex(3);
    ui->Action->setText("GUN ATTACK");
    DrawCard();
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

void MainWindow::DrawCard()
{
    int randomizedNumber = rand() % 53;
    Card drawnCard = deck->cards[randomizedNumber];
    QPixmap image (QString(drawnCard.GetCardImageSource()));
    gameManager->SetPointsInCurrentTurn(gameManager->GetPointsInCurrentTurn() + drawnCard.GetCardPoints());
    ui->TotalPointsValue->setText(QString::number(gameManager->GetPointsInCurrentTurn()));
    ui->Card->setPixmap(image);
}
