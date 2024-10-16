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
    base->addImage(":/images/assets/main_car.png", 100,100);
    ui->gameWindow->setScene(base);
}

void MainWindow::drawGameScene() {
    // Get the width and height of the QGraphicsView's viewport
    int width = ui->gameWindow->viewport()->width();
    int height = ui->gameWindow->viewport()->height();

    // Set scroll bars policy to always off
    ui->gameWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create a new gameScene instance and set its dimensions
    gameScene *scene = new gameScene(width, height);
    ui->gameWindow->setScene(scene);

    // Set the scene rect to match the viewport size
    scene->setSceneRect(0, 0, width, height);

    // Draw the scene components
    scene->drawGreeneries();
    scene->drawRoadBoundaries();
    scene->drawRoadStrips();

    // Optionally store the scene if you need to access it later
    base = scene; // Ensure base is a member variable in MainWindow
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    drawGameScene();
}

