#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QVariant>
// #include "qtypes.h"
#include "qgraphicsscene.h"
#include "entities.h"

class gameScene: public QGraphicsScene
{
    Q_OBJECT
private:
    float laneFraction;
    float laneDividerFraction;
    float greeneriesFraction;
    quint16 roadBoundary1, roadBoundary2;
    quint16 divider1,  divider2;
    quint16 sceneWidth;
    quint32 displacement_per_frame;
    uint fps;
    quint16 sceneHeight;
    QVector<QPixmap> entities;  // List of available entities
    QList<Obstacles *> activeObstacles;  // List of currently spawned obstacles

    QHash<Region, qreal> map;
    quint32 speed;
public:

    gameScene(int w, int h, int fps, QVector<QPixmap> q);
    void drawRoadBoundaries();
    void drawRoadStrips();
    void drawGreeneries();
    void addImage(const QString &filePath, int x, int y);
    void renderMainCar(MainPlayer&);
    void renderObstacles(MainPlayer&);
    void renderGreeneries();
    void spawnObstacle();

signals:
    void updateLives(int lives);
    void gameOver();
    void updateScore();
};

#endif // GAMESCENE_H
