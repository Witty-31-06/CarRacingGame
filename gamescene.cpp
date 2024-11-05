#include "gamescene.h"

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>


gameScene::gameScene(int w, int h, int fps, QVector<QPixmap> cars, QVector<QPixmap> trees) {
    entities = cars;
    this->trees = trees;
    laneDividerFraction = 0.01f;
    laneFraction =  0.13f;
    greeneriesFraction = 0.3f;
    sceneHeight = h;
    sceneWidth = w;
    this->fps = fps;
    speed = sceneHeight/2.0; //Speed of obstacles in height px/second
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
    map[LEFT_GREEN] = (roadBoundary1 + 0)/2.0-200;
    map[RIGHT_GREEN] = (roadBoundary2 + sceneWidth)/2.0-200;
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
    int roadBoundaryRight = sceneWidth - greeneriesWidth;
    int laneWidth = laneFraction * sceneWidth;
    int dividerWidth = laneDividerFraction * sceneWidth;

    int dividerLeftX = roadBoundaryLeft + laneWidth + dividerWidth / 2;
    int dividerRightX = roadBoundaryRight - (laneWidth + dividerWidth / 2);

    QPen dashedPen(Qt::white, dividerWidth);
    dashedPen.setStyle(Qt::SolidLine);

    int segmentHeight = 40; // Height of each strip segment
    int gap = 60; // Space between segments

    // Create dashed segments for left divider
    for (int y = 0; y < sceneHeight; y += segmentHeight + gap) {
        QGraphicsLineItem* segment = addLine(dividerLeftX, y, dividerLeftX, y + segmentHeight, dashedPen);
        dividerLeft.append(segment);
    }

    // Create dashed segments for right divider
    for (int y = 0; y < sceneHeight; y += segmentHeight + gap) {
        QGraphicsLineItem* segment = addLine(dividerRightX, y, dividerRightX, y + segmentHeight, dashedPen);
        dividerRight.append(segment);
    }
}



void gameScene::updateRoadStrips() {
    for (QGraphicsLineItem* segment : dividerLeft) {
        // Move segment down
        qreal newY = segment->line().y1() + displacement_per_frame;

        // If it goes off-screen, reset to the top
        if (newY > sceneHeight) {
            newY = -segment->line().length(); // Reset to just above the top
        }

        segment->setLine(segment->line().x1(), newY, segment->line().x2(), newY + segment->line().length());
    }

    for (QGraphicsLineItem* segment : dividerRight) {
        // Move segment down
        qreal newY = segment->line().y1() + displacement_per_frame;

        // If it goes off-screen, reset to the top
        if (newY > sceneHeight) {
            newY = -segment->line().length();
        }

        segment->setLine(segment->line().x1(), newY, segment->line().x2(), newY + segment->line().length());
    }
}




QRectF gameScene::getRoadBoundary() const {
    // Calculate greeneries width based on the fraction
    int greeneriesWidth = sceneWidth * greeneriesFraction;

    // Calculate road boundaries
    int roadWidth = sceneWidth - (2 * greeneriesWidth);  // Total road width, excluding greeneries
    int roadBoundaryLeft = greeneriesWidth;  // Left boundary starts after greeneries
    int roadBoundaryRight = roadBoundaryLeft + roadWidth;  // Right boundary is after the road width

    // Return the rectangle representing the road
    return QRectF(roadBoundaryLeft, 0,
                  roadWidth,
                  sceneHeight);
}



void gameScene::renderMainCar(MainPlayer& player) {
    QGraphicsPixmapItem* car = player.getPixmap();
    QPointF currPos = car->scenePos();
    qreal x = currPos.x();
    x = qMax(x, (qreal)map[LANE_LEFT]);
    x = qMin(x, (qreal)map[LANE_RIGHT]);
    // player.setCoords(QPoint(x, currPos.x*))
    player.setImage();
    if(!car->scene())
    {
        player.setCoords(QPoint(map[LANE_CENTER], sceneHeight-300));
        addItem(car);
    }
}

void gameScene::spawnTrees() {
    //Choosing a random Obstacle
    QPixmap entity = trees[QRandomGenerator::global()->bounded(trees.size())];
    Greeneries* tree = new Greeneries(entity);

    //Choosing a random lane
    Region randomLane = (Region)(3 + QRandomGenerator::global()->bounded(2));


    //Choosing random spawn y coords
    int ycoord = -300 - QRandomGenerator::global()->bounded(50);
    tree->setCoords(QPoint(map[randomLane], ycoord));
    activeTrees.append(tree);
}

void gameScene::renderGreeneries() {


    for(auto it = activeTrees.begin(); it != activeTrees.end();) {
        Greeneries* tree = *it;
        QGraphicsPixmapItem *pic = tree->getPixmap();
        tree->moveDown(displacement_per_frame);
        pic->setPos(tree->coords);
        if(!pic->scene())
        {

            addItem(pic);
        }
        else if(tree->isOutOfBounds(sceneHeight)) {
            removeItem(pic);

            it = activeTrees.erase(it);
        } else {
            it++;
        }
    }
}
void gameScene::spawnObstacle() {

    //Choosing a random Obstacle
    QPixmap entity = entities[QRandomGenerator::global()->bounded(entities.size())];
    Obstacles* obstacle = new Obstacles(entity);

    //Choosing a random lane
    Region randomLane = (Region)QRandomGenerator::global()->bounded(3); // 0: LEFT, 1: CENTER, 2: RIGHT


    //Choosing random spawn y coords
    int ycoord = -300 - QRandomGenerator::global()->bounded(50);
    obstacle->setCoords(QPoint(map[randomLane], ycoord));
    activeObstacles.append(obstacle);
}
void gameScene::renderObstacles(MainPlayer &player) {

    for(auto it = activeObstacles.begin(); it != activeObstacles.end();) {
        Obstacles* obstacle = *it;
        QGraphicsPixmapItem *pic = obstacle->getPixmap();
        obstacle->moveDown(displacement_per_frame);
        pic->setPos(obstacle->coords);
        if(!pic->scene())
        {

            addItem(pic);
        }

        if (pic->collidesWithItem(player.getPixmap())) {
            player.lives -= 1;
            emit updateLives(player.lives);

            if (player.lives <= 0) {
                emit gameOver();
            }

            // Remove the collided obstacle
            removeItem(pic);
            it = activeObstacles.erase(it);
        }
        else if(obstacle->isOutOfBounds(sceneHeight)) {
            removeItem(pic);
            player.score++;
            emit updateScore();
            it = activeObstacles.erase(it);
        } else {
            it++;
        }
    }
}









