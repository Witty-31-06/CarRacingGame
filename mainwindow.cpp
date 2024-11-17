#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamescene.h"
#include <QMessageBox>

#define fps 120
MainWindow::MainWindow(QWidget *parent)
    :player(":/car_game/main_car.png"),
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**resources**/
    // entities.append(Entity());
    entities.push_back(QPixmap(":/car_game/pink_car.png"));
    entities.push_back(QPixmap(":/car_game/red_car.png"));
    entities.push_back(QPixmap(":/car_game/white_car.png"));
    entities.push_back(QPixmap(":/car_game/yellow_car.png"));

    int scalePercentage = 80; // Replace 'x' with the desired percentage (e.g., 50 for 50%)

    greeneries.push_back(QPixmap(":/car_game/tree_1.png").scaled(
        QPixmap(":/car_game/tree_1.png").width() * scalePercentage / 100,
        QPixmap(":/car_game/tree_1.png").height() * scalePercentage / 100,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));

    greeneries.push_back(QPixmap(":/car_game/tree_2.png").scaled(
        QPixmap(":/car_game/tree_2.png").width() * scalePercentage / 100,
        QPixmap(":/car_game/tree_2.png").height() * scalePercentage / 100,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));

    greeneries.push_back(QPixmap(":/car_game/tree_3.png").scaled(
        QPixmap(":/car_game/tree_3.png").width() * scalePercentage / 100,
        QPixmap(":/car_game/tree_3.png").height() * scalePercentage / 100,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));

    greeneries.push_back(QPixmap(":/car_game/tree_4.png").scaled(
        QPixmap(":/car_game/tree_4.png").width() * scalePercentage / 100,
        QPixmap(":/car_game/tree_4.png").height() * scalePercentage / 100,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));

    base=nullptr;
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{

    QRectF roadBoundary = base->getRoadBoundary();
    QPointF playerPos = player.coords;


    if (event->key() == Qt::Key_A) {
        if (playerPos.x() - 20 >= roadBoundary.left()) {
            player.moveHorizontally(-20);
        }
    }
    else if (event->key() == Qt::Key_D) {  // Move right
        if (playerPos.x() + 30 <= roadBoundary.right() - player.xlen ) { //getting issue in width
            player.moveHorizontally(+20);
        }
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked() {
    drawGameScene();
    timer = new QTimer(this);
    spawnTimer = new QTimer(this);
    treeTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::game_loop);
    connect(spawnTimer, &QTimer::timeout, base, &gameScene::spawnObstacle);
    connect(treeTimer, &QTimer::timeout, base, &gameScene::spawnTrees);
    timer->start(1000/fps);
    spawnTimer->start(1500);
    treeTimer->start(1000);
    ui->gameWindow->setScene(base);
}

void MainWindow::drawGameScene() {
    // Get the width and height of the QGraphicsView's viewport
    int width = ui->gameWindow->viewport()->width();
    int height = ui->gameWindow->viewport()->height();

    ui->gameWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create a new gameScene instance and set its dimensions
    gameScene *scene = new gameScene(width, height, fps,entities, greeneries);
    ui->gameWindow->setScene(scene);

    // Set the scene rect to match the viewport size
    scene->setSceneRect(0, 0, width, height);

    scene->drawGreeneries();
    scene->drawRoadBoundaries();
    scene->drawRoadStrips();

    base = scene;

    connect(base, &gameScene::gameOver, this, &MainWindow::gameOver);
    connect(base, &gameScene::updateLife, this, &MainWindow::notify_life_lost);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    drawGameScene();
}
void MainWindow::game_loop() {

    base->renderMainCar(player);
    base->renderObstacles(player);
    base->updateRoadStrips();
    base->renderGreeneries();


    ui->gameWindow->setScene(base);
}


void MainWindow::on_pauseButton_clicked()
{
    if(timer->isActive()){
        ui->pauseButton->setText("Resume");
        timer->stop();
    }
    else{ timer->start();
    ui->pauseButton->setText("Pause");
    }

    if(spawnTimer->isActive()) spawnTimer->stop();
    else spawnTimer->start();

    if(treeTimer->isActive()) treeTimer->stop();
    else treeTimer->start();
}
void MainWindow::notify_life_lost(int lives) {
    if(lives>0)
    {
        timer->stop();
        spawnTimer->stop();
        QMessageBox::information(this, "Life Lost", QString("You have lost a life. ") + QString::number(player.lives) + QString(" Lives Left"));
        timer->start();
        spawnTimer->start();
    }
}

void MainWindow::gameOver() {
    timer->stop();
    spawnTimer->stop();
    QMessageBox::information(this, "Game Over", "Lost all your lives");
}
