#include "pacman.h"

pacman::pacman(Texture& t, Sprite s, IntRect rect, int posx, int posy)
{
    s.setScale(3.8, 3.8);
    directionToCheck = "none";
    s.setTexture(t);
    s.setTextureRect(rect);

    direction = "none";
    posX = posx;
    posY = posy;
    s.setPosition(posX, posY);
    sprite = s;
    currentFrameX = 0;
    currentFrameY = 0;
    totalFramesX = 6;
    totalFramesY = 4;
    frameWidth = rect.width / totalFramesX;
    frameHeight = rect.height / totalFramesY;
}

void pacman::draw(RenderWindow& window) {
    window.draw(sprite);
}

void pacman::animate() {

    sprite.setTextureRect(IntRect(currentFrameX * frameWidth, currentFrameY * frameHeight, frameWidth, frameHeight));
}

void pacman::updateAnimation() {
    if (direction == "right") {
        currentFrameY = 0; // First row for right directions
        currentFrameX = (currentFrameX + 1) % totalFramesX;
    }
    else if (direction == "up") {
        currentFrameY = 1; // Second row for up direction
        currentFrameX = (currentFrameX + 1) % totalFramesX;
    }
    else if (direction == "left") {
        currentFrameY = 2; // First row for left directions
        currentFrameX = (currentFrameX + 1) % totalFramesX;
    }
    else if (direction == "down") {
        currentFrameY = 3; // Fourth row for down direction
        currentFrameX = (currentFrameX + 1) % totalFramesX;
    }
    animate();
}

bool pacman::checkCollision(std::vector <Tile> tilemap)
{
    for (int i = 0; i < tilemap.size(); i++)
    {
        if ((tilemap[i].getPosX() < posX + 64) && (tilemap[i].getPosX() + 32 > posX) && (tilemap[i].getPosY() < posY + 64) && (tilemap[i].getPosY() + 32 > posY))
        {
            return true;
        }

    }


    return false;

}


void pacman::checkColAndMove(std::vector <Tile> map, int pix)
{

    if (directionToCheck != "none")
    {
        string dir = getDirection();
        setDirection(directionToCheck);
        move(pix);
        if (checkCollision(map))
        {
            move(-pix);
            setDirection(dir);
            if (checkCollision(map))
            {
                move(-pix);
                setDirection("none");
                directionToCheck = "none";
            }

        }
        else
        {
            setFace(getDirection());
            setDirection(directionToCheck);
            directionToCheck = "none";

        }
    }
    else if (checkCollision(map))
    {
        move(-pix);
        setDirection("none");
    }

}

void pacman::setDirection(std::string dir)
{
    direction = dir;
}



std::string pacman::getDirection()
{
    return direction;
}




void pacman::setFace(std::string face)
{
    if (face == "right")
    {
        sprite.setTextureRect(IntRect(0, 0, 64, 64));
    }
    else if (face == "left")
    {
        sprite.setTextureRect(IntRect(66, 0, 64, 64));
    }
    else if (face == "up")
    {
        sprite.setTextureRect(IntRect(132, 0, 64, 64));
    }
    else if (face == "down")
    {
        sprite.setTextureRect(IntRect(198, 0, 64, 64));
    }

}



void pacman::chooseDirection(std::string dir)
{
    if (getDirection() == "none") // pacman mesh moving
    {
        setDirection(dir);
        setFace(dir);
    }
    else // pacman beymoving
    {
        directionToCheck = dir;
    }
}



void pacman::move(int pix)
{
    if (direction == "right")
    {
        posXStack.push(pix);
        posYStack.push(0);
    }
    else if (direction == "left")
    {
        posXStack.push(-pix);
        posYStack.push(0);
    }
    else if (direction == "up")
    {
        posXStack.push(0);
        posYStack.push(-pix);
    }
    else if (direction == "down")
    {
        posXStack.push(0);
        posYStack.push(pix);
    }

    if (!posXStack.empty() && !posYStack.empty()) {
        int deltaX = posXStack.top();
        int deltaY = posYStack.top();

        posX += deltaX;
        posY += deltaY;

        sprite.move(deltaX, deltaY);

        posXStack.pop();
        posYStack.pop();
    }
}




int pacman::getPosY()
{
    return posY;
}
int pacman::getPosX()
{
    return posX;
}

void pacman::setPosX(int x)
{
    posX = x;
}

void pacman::setPosY(int y)
{
    posY = y;
}


bool pacman::checkCollisionWithGhost(Ghost& ghost) {
    int pacX = posX;
    int pacY = posY;

    int ghostX = ghost.getPosX();
    int ghostY = ghost.getPosY();

    if (pacX < ghostX + 64 && pacX + 64 > ghostX && pacY < ghostY + 64 && pacY + 64 > ghostY) {

        return true;

    }

    return false;
}
