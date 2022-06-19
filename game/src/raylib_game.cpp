#include "raylib.h"
#include "WindowVars.h"
#include "Player.h"
#include "KeyboardEventHandler.h"
#include "Enemy.h"
#include <string>
#include <iostream>
#include "CollisionDetect.h"
#include <vector>
#include "Lives.h"
#include "PowerUp.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION 
#include "FileRead.h"
#include <map>
//#define GUI_TEXTBOX_EXTENDED_IMPLEMENTATION
//#include "gui_textbox_extended.h"
#include <limits.h>
#include <unordered_map>
#include <algorithm>
//TODO: MAKE HUGE CLEANUP ASAP
//REMOVE MAGIC NUMBERS
//Do something with ugly button displaying, move to seperate class or something
int main()
{
	//Initialize Player and enemies
	//TODO: move somewhere else lol
	Player player(WindowVars::width / 8,
		WindowVars::height / 2,
		50);
	Enemy enemy = Enemy();
	std::vector<Enemy*> enemies;
	enemies.push_back(new Enemy());
	enemies.push_back(new Enemy(300, 200, 100));
	enemies.push_back(new Enemy(900, 400, 100));
	std::vector<PowerUp*> powerups;


	//Initialize Music
	InitAudioDevice();
	Music music = LoadMusicStream("resources/music2.mp3");
	SetMusicVolume(music, 1.0f);
	PlayMusicStream(music);

	// set up the window
	InitWindow(WindowVars::width, WindowVars::height, WindowVars::windowHeader.c_str());
	SetTargetFPS(GetMonitorRefreshRate(0));

	//Initialize Textures
	Lives::loadTexture();

	//Initialize some variables
	//TODO: move somewhere else lol
	bool direction = false; //false ->
							//true <-
	bool newEnemy = false;
	bool newPowerup = false;
	int enemyCounter = 0;
	int pointsToAddEnemy = 2;
	int pointsToAddPowerup = 3;
	int points = 0;
	std::string pointString = "Points ";
	PowerUp powerup = PowerUp();;
	float buttonHeigth = 120;
	float buttonWidth = 240;
	int temp;
	int fontSize = 120;
	char gameName[] = "Not after Sowing";
	char name[] = "default";
	//Set style of raygui.h
	GuiSetStyle(DEFAULT, TEXT_SIZE, 50);
	auto data = FileRead::file_read("resources/highscore.txt");
	std::map<int, std::string, std::greater<int>> highScores;
	for (int i = 0; i < data.size() / 2; i++)
	{
		highScores[stoi(data[2 * i + 1])] = data[2 * i];
	}
	std::unordered_map<int, Color> leaderBoardColor = { {0,GOLD}, {1,LIGHTGRAY}, {2,BROWN} };
	//Switch :number - function
	unsigned char menuChoice = '1';
	int drawIterator = 0;
	bool highScore = false;

	int enemySpeed = 8;



	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GRAY);
		UpdateMusicStream(music);
		switch (menuChoice)
		{
		case '1': // Main Menu
			temp = MeasureText(gameName, fontSize);
			DrawText(gameName, WindowVars::width / 2 - temp / 2, WindowVars::height / 4 - fontSize / 2, fontSize, LIGHTGRAY);
			if (GuiButton(Rectangle{ (float)WindowVars::width / 2 - buttonWidth / 2,(float)WindowVars::height / 2 - buttonHeigth / 2,buttonWidth,buttonHeigth }, "Play"))
			{
				menuChoice = '3';
			}
			if (GuiButton(Rectangle{ (float)WindowVars::width / 2 - buttonWidth / 2 - 45,(float)WindowVars::height / 2 - buttonHeigth / 2 + buttonHeigth * 1 + 10 ,buttonWidth + 90,buttonHeigth }, "Leaderboard"))
			{
				menuChoice = '2';
			}
			if (GuiButton(Rectangle{ (float)WindowVars::width / 2 - buttonWidth / 2,(float)WindowVars::height / 2 - buttonHeigth / 2 + buttonHeigth * 2 + 20 ,buttonWidth,buttonHeigth }, "Exit"))
			{
				EndDrawing();
				CloseWindow();
				return 0; //Close Window
			}
			break;
		case '2': // LeaderBoard

			for each (auto score in highScores)
			{
				temp = MeasureText((score.second + " " + std::to_string(score.first)).c_str(), fontSize);
				DrawText((score.second + " " + std::to_string(score.first)).c_str(), WindowVars::width / 2 - temp / 2, WindowVars::height / 4 - fontSize / 2 + fontSize * drawIterator, fontSize, leaderBoardColor[drawIterator]);
				drawIterator++;
			}
			drawIterator = 0;
			if (GuiButton(Rectangle{ (float)WindowVars::width / 2 - buttonWidth / 2 - 90,(float)WindowVars::height - 100 - buttonHeigth / 2,buttonWidth + 180,buttonHeigth }, "Back to Main Menu"))
			{
				menuChoice = '1';
			}
			break;
		case '3': // Insert Name
			temp = MeasureText("Insert Name and Hit ENTER", 64);
			DrawText("Insert Name and Hit ENTER", WindowVars::width / 2 - temp / 2, WindowVars::height / 4 - 64 / 2, 64, LIGHTGRAY);
			if (GuiTextBox(Rectangle{ (float)WindowVars::width / 2 - buttonWidth / 2 - 45,(float)WindowVars::height / 2 - buttonHeigth / 2 + buttonHeigth * 1 + 10 - 200,buttonWidth + 90,buttonHeigth }, name, 40, true))
			{
				if (std::string(name).length() == 0)
				{
					std::cout << "Name can't be empty";
				}
				else
				{
					menuChoice = '4';
				}

			}
			break;
		case '4': // Game
			if (Lives::numberOfLives)
			{
				//std::cout << IsMusicStreamPlaying(music);
				KeyboardEventHandler::handleChange(&player, player.getSpeed());
				DrawCircle(player.getXPos(), player.getYPos(), player.getSpec(), RED);
				DrawText((pointString + std::to_string(points)).c_str(), 40, 40, 64, BLACK);
				for each (auto enemy in enemies)
				{
					DrawRectangle(enemy->getXPos(), enemy->getYPos(), enemy->getSpec(), enemy->getSpec(), enemy->getColor());
					if (PowerUp::isSlowDownActivated)
					{
						enemy->updatePos(4);
					}
					else enemy->updatePos(enemySpeed);
					if (CollisionDetect::checkCollision<Player, Enemy>(&player, enemy))
					{
						//enemy->setColor(RED);
						Lives::numberOfLives--;
						direction = false;
						player.setXPos(WindowVars::width / 8);
						player.setYPos(WindowVars::height / 2);
					}
					else
					{
						enemy->setColor(BLUE);
					}
					Lives::drawLives();
				}

				if (GetTime() - PowerUp::getTimer() > 5.0f)
				{
					PowerUp::resetTimer();
					player.setSpeed(10);
					PowerUp::isSlowDownActivated = false;
					PowerUp::isMoveFasterActivated = false;
				}


				for (std::vector<PowerUp*>::iterator it = powerups.begin(); it < powerups.end(); it++)
				{
					DrawTexture((*it)->getTexture(), (*it)->getXPos(), (*it)->getYPos(), WHITE);
					(*it)->addYPos(3);
					if (CollisionDetect::checkCollision<Player, PowerUp>(&player, (*it)))
					{
						if ((*it)->getPowerUpType() == 1)
						{
							for (int i = 0; i < enemies.size() / 2; i++)
							{
								enemies.pop_back();
							}
						}
						else if ((*it)->getPowerUpType() == 2)
						{

							if (enemies.size() > 2)
							{
								enemies.pop_back();
								enemies.pop_back();
							}
						}
						else if ((*it)->getPowerUpType() == 3)
						{
							PowerUp::isSlowDownActivated = true;
							PowerUp::startTimer();
						}
						else if ((*it)->getPowerUpType() == 4)
						{
							PowerUp::isMoveFasterActivated = true;
							player.setSpeed(13);
							PowerUp::startTimer();
						}
						
						powerups.erase(it);
						break;
						
					}
					if ((*it)->getYPos() > 766)
					{
						powerups.erase(it);
						break;
					}
				}
				if (newEnemy == true)
				{
					enemies.push_back(new Enemy(GetRandomValue(150, 1200), GetRandomValue(0, 766), GetRandomValue(50, 100)));
					newEnemy = false;
					pointsToAddEnemy = pointsToAddEnemy + 2;

				}
				else if ((points / (pointsToAddEnemy)) % 2 == 1)
				{
					newEnemy = true;
				}

				if (newPowerup == true)
				{
					powerups.push_back(new PowerUp());
					newPowerup = false;
					pointsToAddPowerup = pointsToAddPowerup + 3;

				}
				else if ((points / (pointsToAddPowerup)) % 2 == 1)
				{
					newPowerup = true;
				}


				if (direction == false)
				{
					if (player.getXPos() > 1316)
					{
						direction = true;
						points++;
					}
				}
				else if (direction == true)
				{
					if (player.getXPos() < 50)
					{
						direction = false;
						points++;
					}
				}
				if (direction == true)
				{
					int a = MeasureText("Direction <-", 64);
					DrawText("Direction <-", WindowVars::width / 2 - a / 2, 692, 64, BLACK);
				}
				else if (direction == false)
				{
					int a = MeasureText("Direction ->", 64);
					DrawText("Direction ->", WindowVars::width / 2 - a / 2, 692, 64, BLACK);
				}

			}
			else if (Lives::numberOfLives <= 0)
			{

				int i = 0;
				int a = MeasureText("New HIGHSCORE check LEADERBOARD", 50);
				std::pair<int, std::string> toDelete = { 0,"" };
				for each (std::pair<int, std::string> obj in highScores)
				{
					if (obj.first < points)
					{
						highScore = true;
						toDelete = obj;
					}

				}

				if (toDelete.second != "")
				{
					highScores.erase(--highScores.end());
					highScores.insert({ points , std::string(name) });
				}
				points = 0;
				if (highScore)
				{
					DrawText("New HIGHSCORE check LEADERBOARD", WindowVars::width / 2 - a / 2, WindowVars::height / 4 - 75, 50, BLACK);
				}
				a = MeasureText("Game Over", 150);
				DrawText("Game Over", WindowVars::width / 2 - a / 2, WindowVars::height / 2 - 75, 150, BLACK);
				int b = MeasureText("Hit SPACEBAR to RESTART", 80);
				DrawText("Hit SPACEBAR to RESTART", WindowVars::width / 2 - b / 2, WindowVars::height / 2 - 75 + 150, 80, BLACK);
				//DO S
				if (IsKeyDown(KEY_SPACE))
				{
					Lives::numberOfLives = 3;
					points = 0;
					while (enemies.size() != 3)
					{
						enemies.pop_back();
					}
					pointsToAddEnemy = 2;
					pointsToAddPowerup = 3;
					if (powerups.size() != 0) powerups.clear();
				}
				if (GuiButton(Rectangle{ (float)WindowVars::width / 2 - buttonWidth / 2 - 90,(float)WindowVars::height - 100 - buttonHeigth / 2,buttonWidth + 180,buttonHeigth }, "Back to Main Menu"))
				{
					Lives::numberOfLives = 3;
					points = 0;
					while (enemies.size() != 3)
					{
						enemies.pop_back();
					}
					pointsToAddEnemy = 2;
					menuChoice = '1';
					highScore = false;
					pointsToAddPowerup = 3;
					if (powerups.size() != 0) powerups.clear();
				}
			}
			break;
		}

		EndDrawing();
	}
	return 0;
}