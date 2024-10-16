#ifndef ENTITIES_H
#define ENTITIES_H

#include "qtypes.h"
#include <QString>
#include <QPixmap>
enum CarLanes {
    LANE_LEFT,
    LANE_CENTER,
    LANE_RIGHT
};

class Entity : public QPixmap{
public:
    int xmin;
    int ymin;
    int xmax;
    int ymax;
    int ylen;
    int xlen;
    QString path;
    Entity(QString);
};

class Obstacles : public Entity {
    Obstacles(QString);
};

class Greeneries : public Entity {
    Greeneries(QString);
};

class MainPlayer : public Entity {
public:
    CarLanes laneNo;
    qint8 lives;
    quint64 score;

    MainPlayer(QString);
};

#endif // ENTITIES_H
