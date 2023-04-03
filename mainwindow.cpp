#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game_timer = new QTimer;
    game_timer->setSingleShot(true);

    connect(game_timer,SIGNAL(timeout()),
    this,SLOT(game_over()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_start_btn_clicked()
{
    qDebug()<< "game started!";
    game();
}

void MainWindow::game()
{
    reaction_time = 2000;
    delay = 1000;
    this->score = 0;
    ui->statusBar->showMessage("Game Started");
    QTimer::singleShot(2000, this,SLOT(next_btn()));

}

void MainWindow::game_over()
{
    ui->lcdNumber->display(int(score));
    qDebug()<<"game over!";
    reset_buttons();
    ui->statusBar->showMessage("Game Over!");
}

void MainWindow::next_btn()
{
    reset_buttons();
    game_timer->setInterval(reaction_time);
    game_timer->start();

    int rand = QRandomGenerator::global()->bounded(1, 5);

    QList btn_list (ui->frame->children());   // create button list
    QPushButton *rand_btn = qobject_cast<QPushButton*>(btn_list.at(rand));

    rand_btn->setDefault(true);
    qDebug()<<rand_btn->objectName();
    connect(rand_btn,SIGNAL(clicked()),
    this,SLOT(point_gained())
    );

}

void MainWindow::point_gained()
{
    game_timer->stop();
    reset_buttons();
    this->score++;
    ui->lcdNumber->display(int(score));
    if(delay >100){delay -= 10;}

    if(score%10==0){
        qDebug()<<"score trigger";
        if(reaction_time >500){reaction_time -= 100;}
        ui->statusBar->showMessage("Difficulty increased!",5000);
    }
    QTimer::singleShot(delay, this,SLOT(next_btn()));

}

void MainWindow::reset_buttons()
{
    QListIterator button_list (ui->frame->children());   // create button listIterator
    // iteration loop to connect every button from button frame
    while (button_list.hasNext())  // run while there is buttons left inside of frame.
    {
        //Get next button object from list and connect it to button handler slot.
        QPushButton *btn = qobject_cast<QPushButton*>(button_list.next());
        if (btn){
            btn->setDefault(false);
            disconnect(btn,SIGNAL(clicked()),
                       this,SLOT(point_gained())
                       );
        }
    }
}

