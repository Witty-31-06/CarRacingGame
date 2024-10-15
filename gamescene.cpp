#include "gamescene.h"
#include "qdebug.h"

gameScene::gameScene(int w, int h) {
    laneDividerFraction = 0.01;
    laneFraction =  0.13;
    greeneriesFraction = 0.3;
    sceneHeight = h;
    sceneWidth = w;
    setBackgroundBrush(QBrush(QColor(169, 169, 169)));
    //30----10----5----10----5----10----30
}
void gameScene::drawGreeneries() {
    // Calculate scene width and height


    // Calculate greeneries width based on the fraction
    int greeneriesWidth = sceneWidth * greeneriesFraction;

    // Left greenery (as a rectangle)
    addRect(0, 0, greeneriesWidth, sceneHeight, QPen(Qt::green), QBrush(Qt::green));

    // Right greenery
    addRect(sceneWidth - greeneriesWidth, 0, greeneriesWidth, sceneHeight, QPen(Qt::green), QBrush(Qt::green));
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

    QPen dashedPen(Qt::white, dividerWidth);
    dashedPen.setStyle(Qt::DashLine);

    dashedPen.setDashPattern(QVector<qreal>() << 3 << 4);

    addLine(dividerLeftX, 0, dividerLeftX, sceneHeight, dashedPen);

    addLine(dividerRightX, 0, dividerRightX, sceneHeight, dashedPen);
}


