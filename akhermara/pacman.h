#include <SFML/Graphics.hpp>
#include<iostream>
#include <stack>
#include <vector>
#include "ghost.h"
#include "map.h"
using namespace sf;
using namespace std;
class pacman {

    string direction;
    bool isMoving;
    int currentFrameX;
    int currentFrameY;
    int totalFramesY;
    int totalFramesX;
    float frameWidth;
    float frameHeight;
    stack<int> posXStack;
    stack<int> posYStack;
public:
    int posX;
    int posY;
    Sprite sprite;
    string directionToCheck;
    pacman(Texture&, Sprite, IntRect, int, int);
    void checkColAndMove(vector <Tile>, int pix = 2);
    void draw(RenderWindow& window);
    bool checkCollision(vector <Tile>);
    void setDirection(string);
    string getDirection();
    void move(int);
    void setFace(string);
    void chooseDirection(string);
    void animate();
    void updateAnimation();
    int getPosY();
    int getPosX();
    void setPosY(int);
    void setPosX(int);
    bool checkCollisionWithGhost(Ghost& ghost);

};
