#pragma once
#include <SFML/Graphics.hpp>
#include<stack>
#include <sstream>
#include<unordered_map>

using namespace sf;
using namespace std;

class MainMenu
{

public:
    MainMenu(float length, float width);
    unordered_map<int, Text> menuTexts;
    unordered_map<int, Sprite> levelSprites;
    unordered_map<int, Text> winTexts;
    unordered_map<int, Text> loseTexts;
    void drawmenu(RenderWindow& window);
    void drawLevels(RenderWindow& window);
    void drawWinTexts(RenderWindow& window);
    void drawloseTexts(RenderWindow& window);
    void up(int cn);
    void down(int cn);
    void left();
    void right();
    int selectChoice; //hardness selector
    int levelCntr; //levels maps selector
    int winChoice; //win options selector
    int loseChoice; //lose options selector
    Texture l[3];
    ~MainMenu();
private:
    Font font;
};