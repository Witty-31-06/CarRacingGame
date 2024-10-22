#include "entities.h"

Entity::Entity(QString path) {
    QPixmap pic = QPixmap(path).scaled(250,250,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    image = new QGraphicsPixmapItem(pic);
    xlen = pic.width();
    this->ylen = pic.height();

};


Entity::Entity(QPixmap pic)
{
    image = new QGraphicsPixmapItem(pic);
    xlen = pic.width();
    ylen = pic.height();
}
MainPlayer::MainPlayer(QString path) : Entity(path){
        lives = 3;
        score = 0;
        laneNo = LANE_CENTER;  // Default lane

}
MainPlayer::MainPlayer(QPixmap pic) : Entity(pic) {}

Greeneries::Greeneries(QString path) : Entity(path) {

}
Greeneries::Greeneries(QPixmap pic) : Entity(pic) {}

Obstacles::Obstacles(QString path) : Entity(path) {

}

Obstacles::Obstacles(QPixmap pic) : Entity(pic) {}
