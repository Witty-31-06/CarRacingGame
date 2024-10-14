#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamescene.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MainPlayer player;

    ui->setupUi(this);
    ui->livesLabel->setText(QString("Lives: ") + QString("❤️ ").repeated(player.lives));
    ui->scoreLabel->setText(QString("Score: ") + QString::number(player.score));
    gameScene *scene = new gameScene(1586,842);

    // Draw the scene components
    scene->drawGreeneries();
    scene->drawRoadBoundaries();
    scene->drawRoadStrips();
    ui->gameWindow->setScene(scene);
    QGraphicsScene *gs = new QGraphicsScene();
    qDebug()<<ui->gameWindow->height()<<ui->gameWindow->width();
    ui->gameWindow->setScene(scene);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {


    }
    else if (event->key() == Qt::Key_Right) {

    }
    qDebug()<<event;
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resetButton_clicked()
{

}

