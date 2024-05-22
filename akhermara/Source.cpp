#include <SFML/Audio.hpp>
#include "pacman.h"
#include "map.h"
#include "MainMenu.h"
#include <queue>
#include <fstream>

using namespace std;
using namespace sf;
bool f = false;


void drawObjects(RenderWindow& window, Map& map, pacman& pacman, Ghost& ghost1,
    Ghost& ghost2, Ghost& ghost3, Text& scoreCounttext, Texture& spriteSheet
    , Texture& foodTexture, int ScreensCntr, Sprite MenuBackGround, Texture& Menubackground,
    MainMenu& menu, Sprite back, bool& lose, Sprite winScreen, Texture& winscreen, bool& win) {

    window.clear(Color::Black);
    if (ScreensCntr == 0) {

        window.draw(back);
        menu.drawmenu(window);
    }

    else if (ScreensCntr == 1 || ScreensCntr == 2 || ScreensCntr == 3) {
        window.draw(MenuBackGround);
        menu.drawLevels(window);
    }
    //easy
    else if (menu.selectChoice == 0) {
        if (lose != true && win != true) {
            pacman.move(4);
            pacman.updateAnimation();
            pacman.checkColAndMove(map.getTilemap(), 4);

            ghost1.checkColAndMove(map.getTilemap(), 4);
            ghost2.checkColAndMove(map.getTilemap(), 4);
            ghost3.checkColAndMove(map.getTilemap(), 4);

        }
        map.removeFood(window, pacman.getPosX(), pacman.getPosY());
        if (menu.levelCntr == 0) {
            map.generate(spriteSheet, foodTexture, 264, "Map1.txt");
        }
        else if (menu.levelCntr == 1) {
            map.generate(spriteSheet, foodTexture, 264, "Map2.txt");
        }
        else if (menu.levelCntr == 2) {
            map.generate(spriteSheet, foodTexture, 264, "Map3.txt");
        }

        map.drawmap(window);
        window.draw(scoreCounttext);
        ghost1.draw(window);
        ghost2.draw(window);
        ghost3.draw(window);
        pacman.draw(window);
    }
    //medium
    else if (menu.selectChoice == 1) {
        if (lose != true && win != true) {
            pacman.move(4);
            pacman.updateAnimation();
            pacman.checkColAndMove(map.getTilemap(), 4);

            ghost1.checkColAndMove(map.getTilemap(), 5);
            ghost2.checkColAndMove(map.getTilemap(), 5);
            ghost3.checkColAndMove(map.getTilemap(), 5);
        }
        map.removeFood(window, pacman.getPosX(), pacman.getPosY());
        if (menu.levelCntr == 0) {
            map.generate(spriteSheet, foodTexture, 264, "Map1.txt");
        }
        else if (menu.levelCntr == 1) {
            map.generate(spriteSheet, foodTexture, 264, "Map2.txt");
        }
        else if (menu.levelCntr == 2) {
            map.generate(spriteSheet, foodTexture, 264, "Map3.txt");
        }

        map.drawmap(window);
        window.draw(scoreCounttext);
        ghost1.draw(window);
        ghost2.draw(window);
        ghost3.draw(window);
        pacman.draw(window);
    }

    //hard(bfs)
    else if (menu.selectChoice == 2) {

        if (lose != true && win != true) {
            pacman.move(4);
            pacman.updateAnimation();
            pacman.checkColAndMove(map.getTilemap(), 4);

            ghost2.checkColAndMove(map.getTilemap(), 6);
            ghost3.checkColAndMove(map.getTilemap(), 6);

            if (ghost1.timer.getElapsedTime().asSeconds() > 1 && map.generateWorking == true)
            {
                ghost1.ifound = false;
                cout << "yes";
                ghost1.updatePathToPacman(Map::logicalGrid, pacman.getPosX(), pacman.getPosY());
                cout << "no";
                ghost1.ifound = true;
                ghost1.timer.restart();
            }

            ghost1.followPath();

        }


        map.removeFood(window, pacman.getPosX(), pacman.getPosY());
        if (menu.levelCntr == 0) {
            map.generate(spriteSheet, foodTexture, 264, "Map1.txt");
        }
        else if (menu.levelCntr == 1) {
            map.generate(spriteSheet, foodTexture, 264, "Map2.txt");
        }
        else if (menu.levelCntr == 2) {
            map.generate(spriteSheet, foodTexture, 264, "Map3.txt");
            if (f != true) {
                for (int i = 0; i < Map::logicalGrid.size(); i++)
                {
                    cout << endl;
                    for (int j = 0; j < Map::logicalGrid[i].size(); j++)
                        cout << Map::logicalGrid[i][j];
                }
                f = true;
            }

        }

        map.drawmap(window);
        window.draw(scoreCounttext);
        ghost1.draw(window);
        ghost2.draw(window);
        ghost3.draw(window);
        pacman.draw(window);
    }
}

void resetgame(int& ScreensCntr, pacman& pacman, Ghost& ghost1,
    Ghost& ghost2, Ghost& ghost3, Map& map) {

    pacman.setDirection("none");
    ghost1.setGhostData(600, 352);
    ghost2.setGhostData(600, 352);
    ghost3.setGhostData(600, 352);
    map.scoreStack.push(0);
    map.foodmap.clear();
    map.tilemap.clear();
    map.count = 0;
    pacman.setPosX(32);
    pacman.setPosY(32);
    pacman.sprite.setPosition(32, 32);


}

void handleRLUDEvents(int& ScreensCntr, Event& event, MainMenu& menu, bool& win,
    bool& lose, Sound& Intro, SoundBuffer& intro) {


    //hardness:selectedChoice/////levels:levelCntr
    if (ScreensCntr == 0) {
        ///use them only in main menu

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
            menu.up(0);

        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
            menu.down(0);

        }
    }
    if (ScreensCntr == 1) {
        ///use them only in levels screen

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left) {
            menu.left();

        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right) {
            menu.right();

        }
    }

    if (ScreensCntr == 0 || ScreensCntr == 1) { Intro.play(); }

    if (win == true) {
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
            menu.up(1);

        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
            menu.down(1);

        }
    }

    if (lose == true) {
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
            menu.up(2);

        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
            menu.down(2);

        }
    }
}

void handlePacmanEvents(pacman& pacman, int& ScreensCntr, bool& win, Event& event, bool& lose)
{
    //FOR PACMAN MOVEMENT
    if (ScreensCntr >= 4 && win != true && lose != true) {


        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
        {

            pacman.chooseDirection("right");
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
        {
            pacman.chooseDirection("left");
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
        {
            pacman.chooseDirection("up");
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
        {
            pacman.chooseDirection("down");
        }
    }

}

void handleLevelsEvents(pacman& pacman, int& ScreensCntr, bool& win, Event& event,
    RenderWindow& window, Map& map, Texture& foodTexture, Texture& spriteSheet, bool& whenEnter
    , bool& lose, Ghost& ghost1, Ghost& ghost2, Ghost& ghost3, MainMenu& menu, Sound& Intro, SoundBuffer& intro) {
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && whenEnter == false) {
        whenEnter = true;

        if (menu.selectChoice == 3) {
            window.close();
        }

        if (menu.selectChoice == 0 && menu.levelCntr == 0 && ScreensCntr == 1) {
            ScreensCntr = 4; //level 1 easy
        }
        if (menu.selectChoice == 0 && menu.levelCntr == 1 && ScreensCntr == 1) {
            ScreensCntr = 7; //level 2 easy

        }
        if (menu.selectChoice == 0 && menu.levelCntr == 2 && ScreensCntr == 1) {
            ScreensCntr = 10; //level 3 easy

        }


        if (menu.selectChoice == 1 && menu.levelCntr == 0 && ScreensCntr == 1) {
            ScreensCntr = 5; //level 1 medium

        }
        if (menu.selectChoice == 1 && menu.levelCntr == 1 && ScreensCntr == 1) {
            ScreensCntr = 8; //level 2 medium

        }
        if (menu.selectChoice == 1 && menu.levelCntr == 2 && ScreensCntr == 1) {
            ScreensCntr = 11; //level 3 medium

        }


        if (menu.selectChoice == 2 && menu.levelCntr == 0 && ScreensCntr == 1) {
            ScreensCntr = 6; //level 1 hard

        }
        if (menu.selectChoice == 2 && menu.levelCntr == 1 && ScreensCntr == 1) {
            ScreensCntr = 9; //level 2 hard

        }
        if (menu.selectChoice == 2 && menu.levelCntr == 2 && ScreensCntr == 1) {
            ScreensCntr = 12; //level 3 hard

        }

        if (ScreensCntr >= 4) { Intro.pause(); }

        if (menu.selectChoice == 0 && ScreensCntr == 0 || menu.selectChoice == 1 && ScreensCntr == 0 || menu.selectChoice == 2 && ScreensCntr == 0) {
            ScreensCntr = 1;

        }

        //WIN
        if (menu.winChoice == 0 && win == true) {
            ScreensCntr = 1;
            map.scoreStack.push(0);
            map.foodmap.clear();
            map.tilemap.clear();
            map.count = 0;
            if (menu.levelCntr == 0) {
                map.generate(spriteSheet, foodTexture, 264, "Map1.txt");
            }
            else if (menu.levelCntr == 1) {
                map.generate(spriteSheet, foodTexture, 264, "Map2.txt");
            }
            else if (menu.levelCntr == 2) {
                map.generate(spriteSheet, foodTexture, 264, "Map3.txt");
            }

            win = false;

        }
        else if (menu.winChoice == 1 && win == true) {
            ScreensCntr = 0;
            resetgame(ScreensCntr, pacman, ghost1, ghost2, ghost3, map);

            win = false;
        }


        //LOSE

        if (menu.loseChoice == 1 && lose == true) {
            resetgame(ScreensCntr, pacman, ghost1, ghost2, ghost3, map);

            if (menu.levelCntr == 0) {
                map.generate(spriteSheet, foodTexture, 264, "Map1.txt");

            }
            else if (menu.levelCntr == 1) {
                map.generate(spriteSheet, foodTexture, 264, "Map2.txt");

            }
            else if (menu.levelCntr == 2) {
                map.generate(spriteSheet, foodTexture, 264, "Map3.txt");

            }

            lose = false;
        }
        else if (menu.loseChoice == 2 && lose == true) {

            ScreensCntr = 0;
            resetgame(ScreensCntr, pacman, ghost1, ghost2, ghost3, map);
            lose = false;
        }

    }
    else if (event.type != Event::KeyPressed && whenEnter == true) {
        whenEnter = false;
    }
}

void handleScoreEvents(Text& scoreCounttext, int& ScreensCntr, bool& win, Event& event,
    RenderWindow& window, Map& map, MainMenu& menu, Sprite winScreen, Texture& winscreen,
    bool& lose, pacman& pacman, Ghost& ghost1, Ghost& ghost2, Ghost& ghost3, Sprite loseScreen, Texture& losescreen) {

    scoreCounttext.setString(to_string(map.scoreStack.top()));

    if (ScreensCntr >= 4) {
        if (map.foodmap.empty()) {
            scoreCounttext.setString("WIN!!");
            window.draw(winScreen);
            menu.drawWinTexts(window);
            win = true;

        }
    }

    if ((pacman.checkCollisionWithGhost(ghost1)
        || pacman.checkCollisionWithGhost(ghost2)
        || pacman.checkCollisionWithGhost(ghost3)) && ScreensCntr >= 4) {
        window.draw(loseScreen);
        menu.drawloseTexts(window);
        lose = true;
    }
}


int main() {

    Texture spriteSheet;
    spriteSheet.loadFromFile("spriteSheet.png");

    Texture pacmanTex;
    pacmanTex.loadFromFile("PacMan.png");
    Vector2f position;
    Sprite pacmanSprite;

    pacman pacman(pacmanTex, pacmanSprite, IntRect(0, 0, 96, 64), 32, 32);

    Texture foodTexture;
    foodTexture.loadFromFile("food.png");

    //to change screens
    int ScreensCntr = 0;
    bool whenEnter = false;
    bool win = false;
    bool lose = false;

    Sprite ghostSprite; // Renamed from ghost to ghostSprite
    Texture ghosttext[2];
    ghosttext[0].loadFromFile("ghost1.png");
    ghosttext[1].loadFromFile("ghost2.png");
    Ghost ghost1(spriteSheet, ghostSprite, IntRect(0, 0, 64, 64), 600, 352);
    Ghost ghost2(ghosttext[0], ghostSprite, IntRect(0, 0, 64, 64), 600, 352);
    Ghost ghost3(ghosttext[1], ghostSprite, IntRect(0, 0, 64, 64), 600, 352);

    Map map;

    MainMenu menu(1280, 1090);
    Texture background;
    background.loadFromFile("mainbackground.png");
    Sprite back(background);

    Sprite MenuBackGround;
    Texture Menubackground;
    Menubackground.loadFromFile("MenuBackGround.png");
    MenuBackGround.setTexture(Menubackground);

    Sprite winScreen;
    Texture winscreen;
    winScreen.setPosition(250, 200);
    winscreen.loadFromFile("winScreen.png");
    winScreen.setScale(0.8, 0.8);
    winScreen.setTexture(winscreen);

    Sprite loseScreen;
    Texture losescreen;
    loseScreen.setPosition(250, 200);
    losescreen.loadFromFile("loseScreen.png");
    loseScreen.setScale(0.8, 0.8);
    loseScreen.setTexture(losescreen);

    Text scoreCounttext;
    Font scoreCountfont;
    map.scoreStack.push(0);
    scoreCountfont.loadFromFile("Titania-Regular.ttf");
    scoreCounttext.setFont(scoreCountfont);
    scoreCounttext.setCharacterSize(35);
    scoreCounttext.setFillColor(Color::White);
    scoreCounttext.setPosition(140, 1025);

    Text highScoreText;
    highScoreText.setFont(scoreCountfont);
    highScoreText.setCharacterSize(35);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(420, 80);

    RenderWindow window(VideoMode(1280, 1090, 32), "Pac-Man");

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    Event event;

    //sound 
    SoundBuffer intro;
    intro.loadFromFile("intro.wav");
    Sound Intro;
    Intro.setBuffer(intro);




    while (window.isOpen()) //MAIN LOOP
    {

        while (window.pollEvent(event))
        {


            handlePacmanEvents(pacman, ScreensCntr, win, event, lose);
            handleRLUDEvents(ScreensCntr, event, menu, win, lose, Intro, intro);
            handleLevelsEvents(pacman, ScreensCntr, win, event, window, map, foodTexture, spriteSheet, whenEnter, lose, ghost1, ghost2, ghost3, menu, Intro, intro);


        }

        drawObjects(window, map, pacman, ghost1, ghost2, ghost3, scoreCounttext, spriteSheet, foodTexture, ScreensCntr, MenuBackGround, Menubackground, menu, back, lose, winScreen, winscreen, lose);
        handleScoreEvents(scoreCounttext, ScreensCntr, win, event, window, map, menu, winScreen, winscreen, lose, pacman, ghost1, ghost2, ghost3, loseScreen, losescreen);

        window.draw(highScoreText);
        window.display();

    }


    return 0;

}
