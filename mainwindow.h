#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString playerName;

private slots:
    void on_StartGame_clicked();

    void on_Quit_clicked();

    void on_Accept_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
