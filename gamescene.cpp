#include "gamescene.h"
#include "qdebug.h"

gameScene::gameScene(int w, int h) {
    laneDividerFraction = 0.05;
    laneFraction =  0.1;
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
    // addLine(dividerLeftX, 0, dividerLeftX, sceneHeight-, QPen(Qt::white, dividerWidth));
}
