#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "qgraphicsscene.h"

class gameScene: public QGraphicsScene
{
private:

    qfloat16 laneFraction;
    qfloat16 laneDividerFraction;
    qfloat16 greeneriesFraction;
    int sceneWidth;
    int sceneHeight;
public:
    gameScene(int w, int h);
    void drawRoadBoundaries();
    void drawRoadStrips();
    void drawGreeneries();
};

#endif // GAMESCENE_H
