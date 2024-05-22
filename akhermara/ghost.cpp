#include "ghost.h"
#include <iostream>
#include <filesystem>
#include <random>
#include <algorithm>


using namespace std;
Ghost::Ghost(Texture& t, Sprite s, IntRect rect, int x, int y) {
    s.setTexture(t);
    s.setTextureRect(rect);
    s.setPosition(x, y);
    direction = "none";
    posX = x;
    posY = y;
    sprite = s;
    decisionDelay = 0.5f;

}

void Ghost::draw(RenderWindow& window) {
    window.draw(sprite);
}

void Ghost::moveRandom(int pix) {

    static mt19937 rng(random_device{}());  // Create a static random number generator
    static uniform_int_distribution<> dist(0, 3); // Uniform distribution between 0 and 3

    static int lastDirection = -1; // Initialize to an invalid direction

    if (timer.getElapsedTime().asSeconds() > 0.2) {
        timer.restart();

        int randomDirection;
        do {
            randomDirection = dist(rng);
        } while (randomDirection == lastDirection);  // Avoid repeating the last direction



        lastDirection = randomDirection; // Update last direction
        // cout << randomDirection << endl;


        switch (randomDirection) {
        case 0:
            chooseDirection("up");
            break;
        case 1:
            chooseDirection("down");
            break;
        case 2:
            chooseDirection("left");
            break;
        case 3:
            chooseDirection("right");
            break;
        }


    }

    move(pix);
}


void Ghost::checkColAndMove(vector<Tile> map, int pix) {
    if (firstMove)
    {
        chooseDirection("up");
        firstMove = false;
    }
    else
    {
        moveRandom(pix);
    }

    if (directionToCheck != "none")
    {
        string dir = getDirection();
        setDirection(directionToCheck);
        move(pix);  // garab et7arak

        if (checkCollision(map))
        {
            move(-pix);  // e3ks eldirection
            setDirection(dir);  // rga3 eldirection lladem

            if (checkCollision(map))
            {
                move(-pix);  // law lsa fe collision e3ks eldirection tani 
                setDirection("none");  // w raga3 aldirection l none
                directionToCheck = "none";
            }

        }
        else
        {           // law mafesh collision rg3 el directionToCheck l none 

            setDirection(dir);
            directionToCheck = "none";

        }
    }
    else if (checkCollision(map))       // law fe collision bs mafesh directiontocheck e3ks al move
    {
        move(-pix);
        setDirection("none");
        cout << "dddddddddddddddddddddddddddddd";
    }
}

bool Ghost::checkCollision(vector<Tile> tilemap) {
    for (int i = 0; i < tilemap.size(); i++) {
        if ((tilemap[i].getPosX() < posX + 64) && (tilemap[i].getPosX() + 32 > posX) &&
            (tilemap[i].getPosY() < posY + 64) && (tilemap[i].getPosY() + 32 > posY)) {
            //std::cout << "Collision at Tile " << i << " (" << tilemap[i].getPosX() << ", " << tilemap[i].getPosY() << ")" << endl;
            return true;
        }
    }
    return false;
}


void Ghost::chooseDirection(string dir)
{
    if (getDirection() == "none") // pacman mesh moving
    {
        setDirection(dir);

    }
    else // pacman beymoving
    {
        directionToCheck = dir;
    }

}


void Ghost::move(int pix)
{
    if (direction == "right")
    {
        posX += pix;
        sprite.move(pix, 0);
    }
    else if (direction == "left")
    {
        posX -= pix;
        sprite.move(-pix, 0);
    }
    else if (direction == "up")
    {
        posY -= pix;
        sprite.move(0, -pix);
    }
    else if (direction == "down")
    {
        posY += pix;
        sprite.move(0, pix);
    }
}


string Ghost::getOppositeDirection(string dir) {
    if (dir == "up") return "down";
    if (dir == "down") return "up";
    if (dir == "left") return "right";
    if (dir == "right") return "left";
    return "none";
}

int Ghost::getDirectionIndex(const std::string& dir) {
    if (dir == "up") return 0;
    if (dir == "down") return 1;
    if (dir == "left") return 2;
    if (dir == "right") return 3;
    return -1; // Default case for no direction
}



int Ghost::getPosY() {
    return posY;
}

int Ghost::getPosX() {
    return posX;
}
void Ghost::setGhostData(int posx, int posy)
{
    sprite.setPosition(posx, posy);
    posX = posx;
    posY = posy;
}

void Ghost::setDirection(string dir) {
    direction = dir;
}

string Ghost::getDirection() {
    return direction;
}

// bfs

void Ghost::updatePathToPacman(vector<vector<int>>& grid, int goalX, int goalY) {

    pathIndex = 0;
    this->path.clear();
    queue<pair<int, int>> queue;
    map<pair<int, int>, pair<int, int>> cameFrom;
    pair<int, int> start = { posX / 32, posY / 32 };
    pair<int, int> goal = { goalX / 32, goalY / 32 };
    cout << posX << " " << posY;
    queue.push(start);
    cameFrom[start] = { -1, -1 };

    while (!queue.empty()) {

        pair<int, int> current = queue.front();

        queue.pop();

        if (current == goal) {

            break;
        }


        vector<pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
        for (auto& dir : directions) {
            pair<int, int> next = { current.first + dir.first, current.second + dir.second };


            if (next.first >= 0 && next.second < grid.size() && next.second >= 0 && next.first < grid[0].size() &&
                ((grid[next.second][next.first] == 0 || grid[next.second][next.first] == 2)
                    && (grid[next.second + 1][next.first] == 0 || grid[next.second + 1][next.first] == 2)
                    && (grid[next.second][next.first + 1] == 0 || grid[next.second][next.first + 1] == 2)) &&
                (grid[next.second + 1][next.first + 1] == 0 || grid[next.second + 1][next.first + 1] == 2) &&
                cameFrom.find(next) == cameFrom.end()) {
                cout << "1";
                queue.push(next);
                cameFrom[next] = current;
            }
        }
    }

    for (pair<int, int> at = goal;; at = cameFrom[at]) {
        path.push_back(at);
        if (at == start) {

            //std::cout << "Reached start." << std::endl;
            break;
        }
    }
    reverse(path.begin(), path.end());


    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i].first << " " << path[i].second << endl;
    }

    this->path = path;

}


void Ghost::followPath() {
    if (path.empty()) {
        cout << "No path to follow." << endl;
        return;
    }

    if (movementClock.getElapsedTime().asSeconds() >= 0.015) {
        if (pathIndex < path.size()) {
            int targetX = path[pathIndex].first * 32;
            int targetY = path[pathIndex].second * 32;


            int deltaX = targetX - posX;
            int deltaY = targetY - posY;
            int step = 4;


            int stepsToTake = max(abs(deltaX), abs(deltaY));
            if (stepsToTake > 0) {
                posX += step * deltaX / stepsToTake;
                posY += step * deltaY / stepsToTake;
                sprite.setPosition(posX, posY);
            }


            if (abs(deltaX) <= step && abs(deltaY) <= step) {
                posX = targetX;
                posY = targetY;
                sprite.setPosition(posX, posY);
                pathIndex++;
            }

            movementClock.restart();
        }
        else {
            cout << "End of path reached." << endl;
            pathIndex = 0;
            path.clear();
        }
    }
}
