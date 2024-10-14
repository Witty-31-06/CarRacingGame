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


void MainWindow::on_startButton_clicked() {
    drawGameScene();
}

void MainWindow::drawGameScene() {
    int width = ui->gameWindow->viewport()->width();
    int height = ui->gameWindow->viewport()->height();
    ui->gameWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gameScene *scene = new gameScene(width, height);
    ui->gameWindow->setScene(scene);

    // Draw the scene components
    scene->drawGreeneries();
    scene->drawRoadBoundaries();
    scene->drawRoadStrips();
    base = scene;
}
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    drawGameScene();
}

