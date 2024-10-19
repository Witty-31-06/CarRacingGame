#ifndef ENTITIES_H
#define ENTITIES_H


#include "qtypes.h"
#include <QString>
#include <QGraphicsPixmapItem>
enum Region {
    LANE_LEFT,
    LANE_CENTER,
    LANE_RIGHT,
    OUTSIDE_ROAD
};

class Entity {
public:
    QPoint coords;
    quint32 xmin;
    quint32 ymin;
    quint32 xmax;
    quint32 ymax;
    quint32 ylen;
    quint32 xlen;
    Region laneNo;
    QString path;
    QGraphicsPixmapItem *image;
    Entity(QString);

    inline QGraphicsPixmapItem* getPixmap() {
        return image;
    }
};

class Obstacles : public Entity {
public:
    Obstacles(QString);
};

class Greeneries : public Entity {
public:
    Greeneries(QString);
};

class MainPlayer : public Entity {
public:

    qint8 lives;
    quint64 score;

    MainPlayer(QString);
};

#endif // ENTITIES_H
