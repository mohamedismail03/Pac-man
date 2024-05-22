#include <SFML/GRAPHICS.HPP>
#include "MainMenu.h"
#include <iostream>
using namespace std;
using namespace sf;

MainMenu::MainMenu(float width, float length) {
	font.loadFromFile("Titania-Regular.ttf");

	l[0].loadFromFile("level 1.png");
	l[1].loadFromFile("level 2.png");
	l[2].loadFromFile("level 3.png");

	//ba7ot l sprites gwa l unorderedmap kol wahed b index
	for (int i = 0; i < 3; i++) {
		Sprite sprite;
		sprite.setTexture(l[i]);
		sprite.setScale(i == 0 ? 0.8, 0.8 : 0.7, 0.7); //brdo 5dtha mn chatgpt 
		sprite.setPosition(830 - 450 * i, 400); //5dtha mn chatgpt 3lshan kont b3ml position mo5tlf kol mara
		levelSprites[i] = sprite;
	}

	string menuOptions[] = { "EASY", "MEDIUM", "HARD", "EXIT" };
	//ba7ot l texts gwa l unorderedmap kol wahed b index
	for (int i = 0; i < 4; i++) {
		Text text;
		text.setFont(font);
		text.setString(menuOptions[i]);
		text.setFillColor(i == 0 ? Color::Yellow : Color::White); //brdo 5dtha mn chatgpt 2
		text.setPosition(560, 640 + i * 80); //brdo 5dtha mn chatgpt 3
		text.setScale(1.7f, 1.7f);
		menuTexts[i] = text;
	}

	string winOptions[] = { "Save Score & Go To Next Level", "Save Score & Return To Main Menu" };
	//ba7ot l texts gwa l unorderedmap kol wahed b index
	for (int i = 0; i < 2; i++) {
		Text text;
		text.setFont(font);
		text.setString(winOptions[i]);
		text.setFillColor(i == 0 ? Color::Yellow : Color::White);
		text.setPosition(380, 550 + i * 80);
		text.setScale(1, 1);
		winTexts[i] = text;
	}
	string loseOptions[] = { "Your Highst Score: ", "Replay The Current Game", "Return To Main Menu" };
	for (int i = 0; i < 3; i++) {
		Text text;
		text.setFont(font);
		text.setString(loseOptions[i]);
		text.setFillColor(i == 1 ? Color::Yellow : Color::White);
		text.setPosition(380, 550 + i * 80);
		text.setScale(1, 1);
		loseTexts[i] = text;
	}

	selectChoice = 0;
	levelCntr = 0;
	winChoice = 0;
	loseChoice = 0;
}

void MainMenu::drawmenu(RenderWindow& window) {
	for (auto it : menuTexts) {
		window.draw(it.second);
	}
}
void MainMenu::drawLevels(RenderWindow& window) {
	for (auto it : levelSprites) {
		window.draw(it.second);
	}
}
void MainMenu::drawWinTexts(RenderWindow& window) {
	for (auto it : winTexts) {
		window.draw(it.second);
	}
}
void MainMenu::drawloseTexts(RenderWindow& window)
{
	for (auto it : loseTexts) {
		window.draw(it.second);
	}
}
//for the main menu
void MainMenu::up(int cn) {
	switch (cn) {
	case 0:
		if (selectChoice - 1 >= -1)
		{
			menuTexts[selectChoice].setFillColor(Color::White);
			selectChoice--;
			if (selectChoice == -1) {
				selectChoice == 2;
			}

			menuTexts[selectChoice].setFillColor(Color::Yellow);
		}
		break;
	case 1:
		if (winChoice - 1 >= -1)
		{
			winTexts[winChoice].setFillColor(Color::White);
			winChoice--;
			if (winChoice == -1) {
				winChoice == 2;
			}

			winTexts[winChoice].setFillColor(Color::Yellow);
		}
		break;
	case 2:
		if (loseChoice - 1 >= -1)
		{
			loseTexts[loseChoice].setFillColor(Color::White);
			loseChoice--;
			if (loseChoice == -1) {
				loseChoice == 2;
			}
			loseTexts[loseChoice].setFillColor(Color::Yellow);
		}
	}



}
void MainMenu::down(int cn) {
	switch (cn) {
	case 0:
		if (selectChoice + 1 <= 4)
		{
			menuTexts[selectChoice].setFillColor(Color::White);
			selectChoice++;
			if (selectChoice == 4) {
				selectChoice == 0;
			}

			menuTexts[selectChoice].setFillColor(Color::Yellow);
		}
		break;
	case 1:
		if (winChoice + 1 <= 2) {
			winTexts[winChoice].setFillColor(Color::White);
			winChoice++;
			if (winChoice == 2) {
				winChoice == 0;
			}

			winTexts[winChoice].setFillColor(Color::Yellow);
		}
		break;
	case 2:
		if (loseChoice + 1 <= 2) {
			loseTexts[loseChoice].setFillColor(Color::White);
			loseChoice++;
			if (loseChoice == 2) {
				loseChoice == 0;
			}

			loseTexts[loseChoice].setFillColor(Color::Yellow);
		}
	}

}
void MainMenu::left()
{

	if (levelCntr + 1 <= 3)
	{
		levelSprites[levelCntr].setScale(0.7, 0.7);
		levelCntr++;
		if (levelCntr == 3) {
			levelCntr == 0;
		}
		levelSprites[levelCntr].setScale(0.8, 0.8);
	}

}

void MainMenu::right()
{

	if (levelCntr - 1 >= -1)
	{
		levelSprites[levelCntr].setScale(0.7, 0.7);
		levelCntr--;
		if (levelCntr == -1) {
			levelCntr == 2;
		}
		levelSprites[levelCntr].setScale(0.8, 0.8);
	}

}

MainMenu::~MainMenu()
{
}
