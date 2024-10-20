#ifndef GAMESCENE_H
#define GAMESCENE_H
#include<QFloat16>
#include <QVariant>
// #include "qtypes.h"
#include "qgraphicsscene.h"
#include "entities.h"

class gameScene: public QGraphicsScene
{
private:

    qfloat16 laneFraction;
    qfloat16 laneDividerFraction;
    qfloat16 greeneriesFraction;
    quint16 roadBoundary1, roadBoundary2;
    quint16 divider1,  divider2;
    quint16 sceneWidth;
    quint32 displacement_per_frame;
    uint fps;
    quint16 sceneHeight;
    QList<QPixmap> entities;  // List of available entities
    QList<Obstacles *> activeObstacles;  // List of currently spawned obstacles
    QHash<Region, quint32> map;
    quint32 speed;
public:

    gameScene(int w, int h, int fps, QList<QPixmap> q);
    void drawRoadBoundaries();
    void drawRoadStrips();
    void drawGreeneries();
    void addImage(const QString &filePath, int x, int y);
    void renderMainCar(MainPlayer&);
    void renderObstacles();
    void renderGreeneries();
    void spawnObstacle();
};

#endif // GAMESCENE_H
