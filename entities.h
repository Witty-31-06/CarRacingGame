#ifndef ENTITIES_H
#define ENTITIES_H


//#include "qtypes.h"
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
    quint32 ylen;
    quint32 xlen;
    Region laneNo;
    QString path;
    QGraphicsPixmapItem *image;
    Entity(QString);
    Entity(QPixmap);

    inline QGraphicsPixmapItem* getPixmap() {
        return image;
    }
    inline void moveDown(qint32 displacement) {
        coords = QPoint(coords.x(), coords.y() + displacement);
    }

    inline bool isOutOfBounds(quint32 sceneHeight) {
        return coords.y()+ylen/2+10 > sceneHeight;
    }
    inline void setCoords(QPoint c) {
        coords = c;
        qDebug()<<"HEHE";
    }
    ~Entity() {
        delete image;
    }
};

class Obstacles : public Entity {
public:
    Obstacles(QString);
    Obstacles(QPixmap);

};

class Greeneries : public Entity {
public:
    Greeneries(QString);
    Greeneries(QPixmap);
};

class MainPlayer : public Entity {
public:

    qint8 lives;
    quint64 score;

    MainPlayer(QString);
    MainPlayer(QPixmap);
};

#endif // ENTITIES_H
