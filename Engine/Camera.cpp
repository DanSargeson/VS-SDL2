#include "Camera.h"

/*
Camera::Camera(){

    this->direction = FREEZE;

    this->camera = { 0, 0, 0, 0 };
}*/

Camera::Camera(int x = 0, int y = 0, int w = 600, int h = 800, int maxSize = 100){

    this->mDirection = FREEZE;

    this->velocityX = 0;
    velocityY = 0;

    vel.X = 0;
    vel.Y = 0;

    this->camera = {x, y, w, h };

    //maxSize /= 64;

    this->camSpeed = 64.f;

    this->maxGridSize = (maxSize * 64);
}

void Camera::setVelocity(int vel){

    this->camSpeed = vel;
}

int Camera::getVelocity(){

    return this->velocityX;
}

void Camera::moveCamera(int direction = 0, int axis = -1){

    //TODO: Move the camera in relation to the rest of the tilemap.... should be the same as how to move a dot, I think.

    mDirection = direction;

    switch(mDirection){

    case FREEZE:

            //this->velocityX = 0;
            //velocityY = 0;
            if(axis == X_AXIS){

                vel.X = 0;
            }
            if(axis == Y_AXIS){

                vel.Y = 0;
            }
            break;

    case LEFT:


        this->vel.X = -camSpeed;    //MAGIC NUMBER
        break;

    case RIGHT:

        this->vel.X = camSpeed; //MAGIC NUMBER
        break;

    case UP:

        this->vel.Y = -camSpeed;
        break;

    case DOWN:

        this->vel.Y = camSpeed;
        break;

    default:
        break;
    }

//    SDL_Delay(0.5);
}

void Camera::moveCam2(int direction, float time){


    camSpeed = 256.f;
    mDirection = direction;

    switch(mDirection){

    case FREEZE:

            vel.X = camSpeed * (time * 64);
            //this->velocityX = 0;
            //velocityY = 0;
//            if(axis == X_AXIS){
//
//                vel.X = 0;
//            }
//            if(axis == Y_AXIS){
//
//                vel.Y = 0;
//            }
            break;

    case LEFT:

        this->vel.X = -camSpeed  * time;    //MAGIC NUMBER
        break;

    case RIGHT:

        this->vel.X = camSpeed * time; //MAGIC NUMBER
        break;

    case UP:

        this->vel.Y = -camSpeed * time;
        break;

    case DOWN:

        this->vel.Y = camSpeed * time;
        break;

    default:
        break;
    }
}

void Camera::stopCam2(int direction, float time){

     camSpeed = 256.f;
    mDirection = direction;

    switch(mDirection){

    case FREEZE:

            vel.X = camSpeed * (time * 64);
            //this->velocityX = 0;
            //velocityY = 0;
//            if(axis == X_AXIS){
//
//                vel.X = 0;
//            }
//            if(axis == Y_AXIS){
//
//                vel.Y = 0;
//            }
            break;

    case LEFT:

        this->vel.X = -camSpeed  * time;    //MAGIC NUMBER
        break;

    case RIGHT:

        this->vel.X = camSpeed * time; //MAGIC NUMBER
        break;

    case UP:

        this->vel.Y = -camSpeed * time;
        break;

    case DOWN:

        this->vel.Y = camSpeed * time;
        break;

    default:
        break;
    }
}



SDL_Rect Camera::getCamera(){

    return this->camera;
}

void Camera::setCameraDimensions(int x, int y, int w, int h){

    this->camera = {x, y, w, h};
}

void Camera::update(){


//    if(mDirection == LEFT || mDirection == RIGHT){
//
//        this->camera.x += velocityX;
//    }
//    else if(mDirection == UP || mDirection == DOWN){
//
//        this->camera.y += velocityY;
//    }

    if(mDirection != FREEZE){

        camera.x += vel.X;
        camera.y += vel.Y;
    }


    if(camera.x < 0){

        camera.x = 0;
    }
    if((camera.x + camera.w) >= maxGridSize){    //TODO: MAGIC NUMBER....S

        camera.x = (maxGridSize - camera.w) - 32;
    }

    if(camera.y < 0){

        camera.y = 0;
    }
    if((camera.y + camera.h) >= (maxGridSize)){    //TODO: MAGIC NUMBER....S

        camera.y = (maxGridSize - camera.h) - 40;
    }

//    SDL_Delay(50);
}
