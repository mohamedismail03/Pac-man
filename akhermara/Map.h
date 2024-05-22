#pragma once
#include <SFML/Graphics.hpp>
#include<stack>
#include <sstream>
#include <fstream>
#include <algorithm> 
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

//Tile Class

class Tile
{
    int sizeX;
    int sizeY;
    int posX;
    int posY;
    Sprite sprite;

public:
    Tile(Texture&, Sprite, int, int, int xOfRect = 264, int sX = 32, int sY = 32);
    int getPosY();
    int getPosX();
    void draw(RenderWindow& window);

};

//Food Class

class food
{

    Sprite Food;
    int fsizeX;
    int fsizeY;
    int fposX;
    int fposY;
public:
    food(Texture& foodTexture, Sprite food, int fposx, int fposy, int sX, int sY, int xOfRect = 264);
    int getfPosY();
    int getfPosX();
    void setfPos(int fposx, int fposy);
    void drawFood(RenderWindow& window);
    Sprite getSprite();
    Vector2f middlePosition;


};

//Map Class

class Map
{
    vector <food> foodvec();
    int ScoreCount = 0;

public:
    void saveScore(int score);
    int count = 0;
    bool generateWorking = false;
    static vector<vector<int>> logicalGrid;
    Text scoretext;
    Font scorefont;
    stack<int> scoreStack;
    void drawmap(RenderWindow& window);
    void generate(Texture& tileTexture, Texture& foodTexture, int xOfRect = 264, string maptochoose = "");
    void removeFood(RenderWindow& window, int pacPosX, int pacPosY);
    vector <Tile> getTilemap();
    vector<food> foodmap;
    vector <Tile> tilemap;
    SoundBuffer eatfood;
    Sound eatFood;
    
};

