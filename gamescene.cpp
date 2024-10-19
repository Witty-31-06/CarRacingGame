#include "gamescene.h"

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

gameScene::gameScene(int w, int h, int fps, QList<Entity *> q) {
    entities = q;
    laneDividerFraction = 0.01;
    laneFraction =  0.13;
    greeneriesFraction = 0.3;
    sceneHeight = h;
    sceneWidth = w;
    this->fps = fps;
    speed = sceneHeight/3.0; //Speed of obstacles in height px/second
    displacement_per_frame = speed/fps;


    roadBoundary1  = sceneWidth * greeneriesFraction;
    roadBoundary2 = sceneWidth - roadBoundary1;


    int greeneriesWidth = sceneWidth * greeneriesFraction;
    int roadBoundaryLeft = greeneriesWidth;
    int roadBoundaryRight = sceneWidth-greeneriesWidth;
    int laneWidth = laneFraction*sceneWidth;
    int dividerWidth = laneDividerFraction*sceneWidth;

    int dividerLeftX = roadBoundaryLeft + laneWidth + dividerWidth/2;
    int dividerRightX = roadBoundaryRight - (laneWidth + dividerWidth / 2);

    divider1 = dividerLeftX;
    divider2 = dividerRightX;

    map[LANE_CENTER] = (divider1+divider2)/2 - 65;
    map[LANE_RIGHT] = (divider2 + roadBoundary2)/2 -65;
    map[LANE_LEFT] = (roadBoundary1 + divider1)/2 -65;
    setBackgroundBrush(QBrush(QColor(169, 169, 169)));
    //30----10----5----10----5----10----30







}
void gameScene::drawGreeneries() {
    // Calculate scene width and height


    // Calculate greeneries width based on the fraction
    quint32 greeneriesWidth = sceneWidth * greeneriesFraction;
    roadBoundary1 = greeneriesWidth;
    // Left greenery (as a rectangle)
    addRect(0, 0, greeneriesWidth, sceneHeight, QPen(Qt::green), QBrush(Qt::green));

    roadBoundary2 = sceneWidth - greeneriesWidth;
    addRect(roadBoundary2, 0, greeneriesWidth, sceneHeight, QPen(Qt::green), QBrush(Qt::green));
}
void gameScene::drawRoadBoundaries() {

    // Calculate positions for road boundaries
    int greeneriesWidth = sceneWidth * greeneriesFraction;
    int roadWidth = sceneWidth - (2 * greeneriesWidth);  // Total road width
    int leftBoundaryX = greeneriesWidth;
    int rightBoundaryX = greeneriesWidth + roadWidth;

    // Draw left boundary
    QGraphicsLineItem *leftBoundary = addLine(leftBoundaryX, 0, leftBoundaryX, sceneHeight, QPen(Qt::black));

    // Draw right boundary
    QGraphicsLineItem *rightBoundary = addLine(rightBoundaryX, 0, rightBoundaryX, sceneHeight, QPen(Qt::black));
}
void gameScene::drawRoadStrips() {


    int greeneriesWidth = sceneWidth * greeneriesFraction;
    int roadBoundaryLeft = greeneriesWidth;
    int roadBoundaryRight = sceneWidth-greeneriesWidth;
    int roadWidth = sceneWidth - (2 * greeneriesWidth) - 2;
    int laneWidth = laneFraction*sceneWidth;
    int dividerWidth = laneDividerFraction*sceneWidth;

    int dividerLeftX = roadBoundaryLeft + laneWidth + dividerWidth/2;
    int dividerRightX = roadBoundaryRight - (laneWidth + dividerWidth / 2);

    divider1 = dividerLeftX;
    divider2 = dividerRightX;
    QPen dashedPen(Qt::white, dividerWidth);
    dashedPen.setStyle(Qt::DashLine);

    dashedPen.setDashPattern(QVector<qreal>() << 5 << 4);

    addLine(dividerLeftX, 0, dividerLeftX, sceneHeight, dashedPen);

    addLine(dividerRightX, 0, dividerRightX, sceneHeight, dashedPen);
}


void gameScene::renderMainCar(MainPlayer& player) {
    QGraphicsPixmapItem* car = player.getPixmap();
    QPointF currPos = car->scenePos();
    qreal x = currPos.x();
    quint32 newX= map[player.laneNo];
    if(qAbs(x-newX) > 0.1)
    {

        car->setPos(map[player.laneNo], sceneHeight-300);
        // addItem(car);
    }
    if(!car->scene())
    {
        addItem(car);
    }
}

void gameScene::renderObstacles() {
    static int spawnCountdown = 0;

    if (spawnCountdown <= 0) {
        int obstacleCount = QRandomGenerator::global()->bounded(1, 3);
        for (int i = 0; i < obstacleCount; i++) {
            Region lanes[] = {LANE_LEFT, LANE_CENTER, LANE_RIGHT};
            Region lane = lanes[QRandomGenerator::global()->bounded(0, 3)];

            Entity* entity = entities[QRandomGenerator::global()->bounded(entities.size())];

            Obstacles* obstacle = static_cast<Obstacles*>(entity);

            QGraphicsPixmapItem* obstaclePixmap = obstacle->getPixmap();

            obstaclePixmap->setPos(map[lane], -100);

            if (!obstaclePixmap->scene()) {
                addItem(obstaclePixmap);
            }

            activeObstacles.append(obstacle);
        }

        spawnCountdown = fps * 2;
    }

    spawnCountdown--;

    for (int i = 0; i < activeObstacles.size(); ++i) {
        Obstacles* obstacle = activeObstacles[i];
        QGraphicsPixmapItem* obstaclePixmap = obstacle->getPixmap();

        qreal newY = obstaclePixmap->y() + displacement_per_frame;
        obstaclePixmap->setPos(obstaclePixmap->x(), newY);

        if (newY > sceneHeight) {
            removeItem(obstaclePixmap);

            activeObstacles.removeAt(i);
            i--;
        }
    }
}



