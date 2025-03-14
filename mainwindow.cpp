#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "enemy.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LiberationBattle21)
{
    ui->setupUi(this);
    player = new Player();
    enemy = new Enemy();
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

    player->SetGunsLeft(player->GetGunsLeft() / 2);
    qDebug() << player->GetGunsLeft();

}

