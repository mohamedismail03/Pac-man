#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "map.h" 
//#ifndef GHOST_H
//#define GHOST_H
using namespace std;

class Ghost {
private:

    int posX;
    int posY;
    string direction;
    bool isMoving;
    size_t pathIndex;
    Clock movementClock;
    float decisionDelay;
    bool firstMove;

public:
    bool ifound = false;
    Clock timer;
    pair<int, int> gridPosition;// Grid position of the ghost
    vector<pair<int, int>> path;;
    Sprite sprite;
    string directionToCheck;
    Ghost(Texture&, Sprite, IntRect, int, int);
    void draw(RenderWindow&);
    void moveRandom(int);
    void move(int pix);
    void checkColAndMove(vector<Tile>, int);
    bool checkCollision(vector<Tile>);
    void chooseDirection(string);
    int getPosY();
    int getPosX();
    void setDirection(string dir);
    void setGhostData(int posx, int posy);
    string getDirection();
    void updatePathToPacman(vector<vector<int>>& grid, int startX, int startY);
    void followPath();
    string getOppositeDirection(string dir);
    int getDirectionIndex(const std::string& dir);

};
