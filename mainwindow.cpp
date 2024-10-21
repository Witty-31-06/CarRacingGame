#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamescene.h"

#define fps 30
MainWindow::MainWindow(QWidget *parent)
    :player(":/car_game/main_car.png"),
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**resources**/
    // entities.append(Entity());
    entities.emplaceBack(":/car_game/pink_car.png");
    entities.emplaceBack(":/car_game/red_car.png");
    entities.emplaceBack(":/car_game/white_car.png");
    entities.emplaceBack(":/car_game/yellow_car.png");




    ui->livesLabel->setText(QString("Lives: ") + QString("❤️ ").repeated(player.lives));
    ui->scoreLabel->setText(QString("Score: ") + QString::number(player.score));



}
void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_A) {

        switch(player.laneNo) {
        case LANE_CENTER:
        case LANE_LEFT:
            player.laneNo = LANE_LEFT;
            break;


        case LANE_RIGHT:
            player.laneNo = LANE_CENTER;
            break;
        default:
            break;
        }

    }
    else if (event->key() == Qt::Key_D) {
        switch(player.laneNo) {
        case LANE_CENTER:
        case LANE_RIGHT:
            player.laneNo = LANE_RIGHT;
            break;
        case LANE_LEFT:
            player.laneNo = LANE_CENTER;
            break;
        default:
            break;
        }
    }

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
    timer = new QTimer(this);
    spawnTimer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::game_loop);
    connect(spawnTimer, &QTimer::timeout, base, &gameScene::spawnObstacle);
    timer->start(1000/fps);
    spawnTimer->start(2000);
    ui->gameWindow->setScene(base);
}

void MainWindow::drawGameScene() {
    // Get the width and height of the QGraphicsView's viewport
    int width = ui->gameWindow->viewport()->width();
    int height = ui->gameWindow->viewport()->height();

    ui->gameWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create a new gameScene instance and set its dimensions
    gameScene *scene = new gameScene(width, height, fps,entities);
    ui->gameWindow->setScene(scene);

    // Set the scene rect to match the viewport size
    scene->setSceneRect(0, 0, width, height);

    scene->drawGreeneries();
    scene->drawRoadBoundaries();
    scene->drawRoadStrips();

    base = scene;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    drawGameScene();
}
void MainWindow::game_loop() {

    base->renderMainCar(player);
    base->renderObstacles();
    // base->renderGreeneries();

    ui->gameWindow->setScene(base);
}
