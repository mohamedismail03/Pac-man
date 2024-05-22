#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "map.h"
#include <iostream>
using namespace std;

vector<vector<int>>Map::logicalGrid;

//maaaaaaaaaaaaaap
void Map::removeFood(RenderWindow& window, int pacPosX, int pacPosY)
{   
    eatfood.loadFromFile("eatfood.wav"); // sound
    eatFood.setBuffer(eatfood);
    
    for (auto it = foodmap.begin(); it != foodmap.end(); ++it) {
        int foodPosX = it->getfPosX();
        int foodPosY = it->getfPosY();
            
        if (pacPosX == foodPosX && pacPosY == foodPosY) {

            eatFood.play();

            foodmap.erase(it);
            if (scoreStack.empty()) {
                ScoreCount += 100;
                scoreStack.push(ScoreCount);
            }
            else {
                ScoreCount = scoreStack.top() + 100;
                saveScore(ScoreCount);
                scoreStack.pop();
                scoreStack.push(ScoreCount);


            }

            break;
        }
    }
}

void Map::drawmap(RenderWindow& window)
{
    for (int i = 0; i < tilemap.size(); i++)
    {
        tilemap[i].draw(window);
    }

    for (int i = 0; i < foodmap.size(); i++)
    {
        foodmap[i].drawFood(window);
    }
    window.draw(scoretext);
}

void Map::generate(Texture& tileTexture, Texture& foodTexture, int xOfRect, string maptochoose)
{

    Sprite tile;
    int cntr = 0;
    ifstream openfile(maptochoose);

    if (count == 0) {
        if (openfile.is_open())
        {
            logicalGrid.clear();
            string line;
            int lineCount = 0;

            scorefont.loadFromFile("Titania-Regular.ttf");
            scoretext.setFont(scorefont);
            scoretext.setString("Score: ");
            scoretext.setCharacterSize(35);
            scoretext.setFillColor(Color::White);
            scoretext.setPosition(10, 1025);

            while (getline(openfile, line))
            {
                vector<int> gridRow;

                for (int column = 0; column < 40; column++)
                {
                    if (line[column] == '1')
                    {
                        Tile block(tileTexture, tile, column * 32, lineCount * 32, xOfRect);
                        tilemap.push_back(block);
                        gridRow.push_back(1);
                    }

                    else if (line[column] == '2')
                    {
                        gridRow.push_back(2);
                    }
                    else if (line[column] == '0') {

                        gridRow.push_back(0);
                    }
                }
                for (int column = 0; column < line.length(); column++)

                {
                    if (line[column] == '0')
                    {

                        int sX = 32, sY = 32;
                        food block(foodTexture, tile, column * 32, lineCount * 32, sX, sY, xOfRect);
                        if (cntr != 0) {
                            foodmap.push_back(block);
                            // ashan el start mfhosh food

                        }
                        cntr++; 

                    }
                }
                Map::logicalGrid.push_back(gridRow);
                lineCount++;
            }
        }
    }
    count++;
    openfile.close();
    generateWorking = true;

}
std::vector <Tile> Map::getTilemap()
{
    return tilemap;
}

vector<food> Map::foodvec()
{
    return foodmap;
}

void Map::saveScore(int score)
{
    std::ofstream scoreFile("scores.txt", std::ios::app); // Open file in append mode
    if (scoreFile.is_open()) {
        scoreFile << score << std::endl; // Write the score followed by a newline
        scoreFile.close();
    }
    else {
        std::cout << "Unable to open file to save score." << std::endl;
    }
}

//Tileeeeeeeeeeeeee

Tile::Tile(Texture& t, Sprite s, int x, int y, int xOfRect, int sX, int sY)
{
    sizeX = sX;
    sizeY = sY;
    posX = x;
    posY = y;
    s.setTexture(t);
    s.setTextureRect(sf::IntRect(xOfRect, 0, 32, 32));
    s.setPosition(x, y);
    sprite = s;

}
int Tile::getPosY()
{
    return posY;
}
int Tile::getPosX()
{
    return posX;
}
void Tile::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
//foooooooood


food::food(Texture& foodTexture, Sprite food, int fposx, int fposy, int sX, int sY, int xOfRect)
{

    fsizeY = sY;
    fposX = fposx;
    fposY = fposy;
    food.setTexture(foodTexture);
    food.setTextureRect(sf::IntRect(0, 0, 512, 512));
    food.setScale(0.06, 0.06);
    food.setPosition(fposx, fposy);
    Food = food;
    middlePosition = Vector2f(fposx + sX / 2.f, fposy + sY / 2.f);
}

int food::getfPosY()
{
    return fposY;
}

int food::getfPosX()
{
    return fposX;
}

void food::setfPos(int fposx, int fposy)
{
    fposX = fposx;
    fposY = fposy;
}


Sprite food::getSprite()
{
    return Food;
}
void food::drawFood(RenderWindow& window)
{
    Food.setPosition(middlePosition);
    window.draw(Food);
}
