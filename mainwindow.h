#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_btn_clicked();
    void game();
    void game_over();
    void next_btn();
    void point_gained();
    void reset_buttons();

private:
    Ui::MainWindow *ui;
    QTimer *game_timer;
    uint score;
    int interval;
    uint reaction_time;
    uint delay;
};
#endif // MAINWINDOW_H
