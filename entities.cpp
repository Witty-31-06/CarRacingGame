#include "entities.h"

Entity::Entity(QString path) {
    QPixmap pic = QPixmap(path);
    image = new QGraphicsPixmapItem(pic);
    xlen = pic.width();
    this->ylen = pic.height();

};
MainPlayer::MainPlayer(QString path) : Entity(path){
        lives = 3;
        score = 0;
        laneNo = LANE_CENTER;  // Default lane

}
Greeneries::Greeneries(QString path) : Entity(path) {

}

Obstacles::Obstacles(QString path) : Entity(path) {

}
