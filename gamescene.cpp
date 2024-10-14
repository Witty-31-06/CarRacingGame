#include "gamescene.h"
#include "qdebug.h"

gameScene::gameScene(int w, int h) {
    laneDividerFraction = 0.05;
    laneFraction =  0.2;
    greeneriesFraction = 0.15;
    sceneHeight = h;
    sceneWidth = w;
    //0.2*3+0.15*2+0.05*2
}
void gameScene::drawGreeneries() {
    // Calculate scene width and height


    // Calculate greeneries width based on the fraction
    int greeneriesWidth = sceneWidth * greeneriesFraction;

    // Left greenery (as a rectangle)
    addRect(0, 0, greeneriesWidth, sceneHeight, QPen(Qt::green), QBrush(Qt::green));

    // Right greenery
    addRect(sceneWidth - greeneriesWidth, 0, greeneriesWidth, sceneHeight, QPen(Qt::green), QBrush(Qt::green));

    qDebug()<<sceneWidth<<sceneHeight<<greeneriesWidth;
}
void gameScene::drawRoadBoundaries() {
    // Calculate scene width and height


    // Calculate positions for road boundaries
    int greeneriesWidth = sceneWidth * greeneriesFraction;
    int roadWidth = sceneWidth - (2 * greeneriesWidth);  // Total road width
    int leftBoundaryX = greeneriesWidth;
    int rightBoundaryX = greeneriesWidth + roadWidth;

    // Draw left boundary
    QGraphicsLineItem *leftBoundary = addLine(leftBoundaryX, 0, leftBoundaryX, sceneHeight, QPen(Qt::white, 3));

    // Draw right boundary
    QGraphicsLineItem *rightBoundary = addLine(rightBoundaryX, 0, rightBoundaryX, sceneHeight, QPen(Qt::white, 3));
}
void gameScene::drawRoadStrips() {
    // Calculate scene width and height

    // Calculate road and lane sizes
    int greeneriesWidth = sceneWidth * greeneriesFraction;
    int roadWidth = sceneWidth - (2 * greeneriesWidth);
    int laneWidth = roadWidth * laneFraction;
    int laneDividerWidth = roadWidth * laneDividerFraction;

    // Calculate positions of the dividers
    int leftDividerX = greeneriesWidth + laneWidth;  // First lane divider
    int rightDividerX = leftDividerX + laneWidth + laneDividerWidth;  // Second lane divider

    // Draw dashed lines for lane dividers
    QPen dashedPen(Qt::white);
    dashedPen.setStyle(Qt::DashLine);
    dashedPen.setWidth(2);

    // First lane divider
    QGraphicsLineItem *leftLaneDivider = addLine(leftDividerX, 0, leftDividerX, sceneHeight, dashedPen);

    // Second lane divider
    QGraphicsLineItem *rightLaneDivider = addLine(rightDividerX, 0, rightDividerX, sceneHeight, dashedPen);
}
