#ifndef ENTITIES_H
#define ENTITIES_H


//#include "qtypes.h"
#include <QString>
#include <QDebug>
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
    qint32 ylen;
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
    inline void moveHorizontally(qint32 displacement) {

        coords = QPoint(coords.x() + displacement, coords.y());
        qDebug()<<coords;
    }
    inline void setImage() {
        image->setPos(coords);
    }
    inline bool isOutOfBounds(quint32 sceneHeight) {
        // qDebug()<<(coords.y() - ylen)<<sceneHeight;
        return (coords.y() - ylen) > (qint32)sceneHeight ;
    }
    inline void setCoords(QPoint c) {
        coords = c;
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
