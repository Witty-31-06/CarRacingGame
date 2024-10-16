#include "entities.h"

Entity::Entity(QString path) :QPixmap(path){

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
