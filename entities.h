#ifndef ENTITIES_H
#define ENTITIES_H

#include "qtypes.h"
enum CarLanes {
    LANE_LEFT,
    LANE_CENTER,
    LANE_RIGHT
};

class Entity {
public:
    int xmin;
    int ymin;
    int xmax;
    int ymax;
    int ylen;
    int xlen;
    Entity();
};

class Obstacles : public Entity {

};

class Greeneries : public Entity {

};

class MainPlayer : public Entity {
public:
    CarLanes laneNo;
    qint8 lives;
    quint64 score;

    MainPlayer() {
        lives = 3;
        score = 0;
        laneNo = LANE_CENTER;  // Default lane
    }
};

#endif // ENTITIES_H
