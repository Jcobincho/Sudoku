#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include"RectangleShape.h"
#include"Numb.h"
#include"Drawable.h"
#include"Map.h"
#include"ToString.h"
#include "Menu.h"
#include "BoolFunctions.h"

#include "Font.h"
#include "Mapa.h"

#include <windows.h>

#pragma warning(disable : 4996)
using namespace std;


vector<string> split(const string& s, char delim)
{
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim))
	{
		tokens.push_back(item);
	}
	return tokens;
}


int main()
{
	ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
	sf::RenderWindow window(sf::VideoMode(1080, 600), "Sudoku !");

	sf::Font arialFont;
	//arialFont.loadFromFile("arial.ttf");
	arialFont.loadFromMemory(&arial_ttf, arial_ttf_len);


	numb.setFont(arialFont);
	numb.setColor(sf::Color::Black);
	numb.setCharacterSize(44);

	sf::Texture mapTexture;
	//mapTexture.loadFromFile("img/map.jpg");
	mapTexture.loadFromMemory(&img_map_jpg, img_map_jpg_len);
	Map map(mapTexture, arialFont);

	Menu menu(mapTexture);

	std::string str;
	sf::Text text, mousePostString, warningText, resultText, modeText;
	text.setPosition(16, 16);
	text.setFont(arialFont);
	text.setColor(sf::Color::Black);
	mousePostString.setPosition(50, 540);
	mousePostString.setFont(arialFont);
	mousePostString.setColor(sf::Color::Black);
	mousePostString.setString("Y: 0 X: 0");
	warningText.setFont(arialFont);
	warningText.setColor(sf::Color::Black);
	warningText.setPosition(540, 274);
	modeText.setFont(arialFont);
	modeText.setColor(sf::Color::Black);
	modeText.setPosition(840, 540);
	modeText.setString("Edytuj!");
	resultText.setFont(arialFont);
	resultText.setColor(sf::Color::Black);
	resultText.setPosition(540, 290);

	vector<string> v;

	sf::Texture selected, unselected;
	sf::Sprite selectedGrid, unselectedGrid;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			rect[i][j].setSize(sf::Vector2f(52, 52));
			rect[i][j].setFillColor(sf::Color(0, 0, 0, 0));
		}
	}

	bool playing = false;

	int mouseX = 0, mouseY = 0, selectedX = 0, selectedY = 0;

	bool boardGenerated = false;

	while (window.isOpen())
	{

		sf::Vector2f mousePost = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (rect[i][j].getGlobalBounds().contains(mousePost))
				{
					mouseX = j;
					mouseY = i;
				}
			}
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					if (event.text.unicode == '\b' && str != "")
						str.erase(str.size() - 1, 1);
					else if (event.text.unicode == '\b' && str == "") {}
					else
					{
						if (!playing)
						{
							str += static_cast<char>(event.text.unicode);
							if (BoolFunctions::isInt(static_cast<char>(event.text.unicode)))
							{
								map.vertexArr[selectedY][selectedX] = static_cast<char>(event.text.unicode) - '0';
							}
						}
						else
						{
							str += static_cast<char>(event.text.unicode);
							if (BoolFunctions::isInt(static_cast<char>(event.text.unicode)) && static_cast<char>(event.text.unicode) - '0' != 0)
							{
								if (BoolFunctions::isSafe(map.vertexArr, selectedY, selectedX, static_cast<char>(event.text.unicode) - '0', map.region))
								{
									map.vertexArr[selectedY][selectedX] = static_cast<char>(event.text.unicode) - '0';
									warningText.setString("");
									if (!BoolFunctions::ThereIsZero(map.vertexArr))
									{
										resultText.setString("Rozwiazano!");
									}
								}
								else
								{
									warningText.setString("Niepoprawny \nnumer");
								}
							}
							else if (static_cast<char>(event.text.unicode) - '0' == 0)
							{
								map.vertexArr[selectedY][selectedX] = static_cast<char>(event.text.unicode) - '0';
							}
						}
					}
					text.setString(str);
				}
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				if (str != "")
				{
					v = split(str, ' ');
					if (v.front() == "open" && str != "")
					{
						std::ifstream file;
						file.open(v.back());
						if (file.is_open())
						{
							for (int i = 0; i < 9; i++)
							{
								for (int j = 0; j < 9; j++)
								{
									file >> map.vertexArr[i][j];
								}
							}
							warningText.setString("");
						}
						else
						{
							warningText.setString("Nie znaleziono pliku\nError: " + v.back());
						}
						file.close();
					}
				}
				if (str == "solve")
				{
					if (BoolFunctions::isMapValid(map))
					{
						rect[selectedY][selectedX].setFillColor(sf::Color(0, 0, 0, 0));

						if (BoolFunctions::solveSudoku(map))
						{
							resultText.setString("Rozwiazano!");
						}
						else
						{
							resultText.setString("Niema\npoprawnego\nRozwiazania!");
						}
					}
					else
					{
						resultText.setString("Niema\npoprawnego\nRozwiazania!");
					}
				}
				else if (str == "exit")
				{
					window.close();
				}
				else if (str == "reset")
				{
					map.clearVertexArr2();
					map.reset();
				}
				else if (str == "clear")
				{
					map.clearVertexArr2();
					map.clear();
				}
				else if (str == "play")
				{
					if (BoolFunctions::isMapValid(map))
					{
						playing = true;
						modeText.setString("Graj!");
						warningText.setString("");
						resultText.setString("");
						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								map.vertexArr2[i][j] = map.vertexArr[i][j];
							}
						}
					}
					else
					{
						resultText.setString("Niema\npoprawnego\nRozwiazania!");
					}
				}
				else if (str == "edit")
				{
					playing = false;
					modeText.setString("Edytuj!");
					map.clearVertexArr2();
				}
				str = "";
				text.setString(str);
				while (!v.empty())
				{
					v.pop_back();
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (!playing) {
					warningText.setString("");

					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							if (rect[i][j].getGlobalBounds().contains(mousePost))
							{
								rect[i][j].setFillColor(sf::Color(255, 255, 0, 128));
								selectedX = j;
								selectedY = i;
							}
							else
							{
								rect[i][j].setFillColor(sf::Color(0, 0, 0, 0));
							}
						}
					}
					mousePostString.setString("Y: " + to_string(selectedY) + " X: " + to_string(selectedX));
					for (int i = 0; i < 10; i++)
					{
						if (menu.getButton(i).getGlobalBounds().contains(mousePost))
						{
							if (i == 0)
							{
								if (BoolFunctions::countNumbers(map.vertexArr) < 17) {
									warningText.setString("Nieskaczonosc\nrozwiazan");
									
								}
								else if (BoolFunctions::isMapValid(map))
								{
									playing = true;
									menu.playing = true;
									modeText.setString("Graj!");
									warningText.setString("");
									resultText.setString("");
									for (int i = 0; i < 9; i++)
									{
										for (int j = 0; j < 9; j++)
										{
											map.vertexArr2[i][j] = map.vertexArr[i][j];
										}
									}
								}
								else
								{
									resultText.setString("Niema\poprawnego\nRozwiazania!");
								}
							}
							else if (i == 1)
							{
								if (BoolFunctions::countNumbers(map.vertexArr) < 17) {
									warningText.setString("Nieskaczonosc\nrozwiazan");

								}
								else if (BoolFunctions::isMapValid(map))
								{
									rect[selectedY][selectedX].setFillColor(sf::Color(0, 0, 0, 0));
									if (BoolFunctions::solveSudoku(map))
									{
										if (BoolFunctions::isMapValid(map))
											resultText.setString("Rozwiazano!");
										else
											resultText.setString("Rozwiazano!");
									}
									else
									{
										resultText.setString("Niema\npoprawnego\nRozwiazania!");
									}
								}
								else
								{
									resultText.setString("Niema\poprawnego\nRozwiazania!");
								}
							}
							else if (i == 2)
							{
								std::ifstream file;
								file.open("map.txt");

								if (file.is_open()) {
									Map tempMap(mapTexture, arialFont);
									int nonZeroCount = 0;

									for (int i = 0; i < 9; i++) {
										for (int j = 0; j < 9; j++) {
											file >> tempMap.vertexArr[i][j];
											if (tempMap.vertexArr[i][j] != 0) {
												nonZeroCount++;
											}
										}
									}

									file.close();
									if (BoolFunctions::isMapValid(tempMap) && BoolFunctions::solveSudoku(tempMap) && nonZeroCount >= 17) {
										file.open("map.txt");

										if (file.is_open()) {
											for (int i = 0; i < 9; i++) {
												for (int j = 0; j < 9; j++) {
													file >> map.vertexArr[i][j];
												}
											}

											warningText.setString("");
										}
										else {
											warningText.setString("Nie znaleziono pliku\nError: " + v.back());
										}

										file.close();
									}
									else {
										for (int i = 0; i < 9; i++) {
											for (int j = 0; j < 9; j++) {
												map.vertexArr[i][j] = 0;
											}
										}

										if (nonZeroCount < 17) {
											warningText.setString("Nieskonczosc\nrozwiazan.");
										}
										else {
											warningText.setString("");
											warningText.setString("Nierozwi¹zywalna mapa.");
										}
									}
								}
							}
							else if (i == 4)
							{
								BoolFunctions::generateSudoku(map,17,23);
								modeText.setString("Edytuj!");
							}
							else if (i == 5)
							{
								BoolFunctions::save(map);
								warningText.setString("Zapisano!");
							}
							else if (i == 6)
							{
								map.clear();
								map.clearVertexArr2();
							}
							else if (i == 7)
							{
								BoolFunctions::generateSudoku(map,30,31);
								modeText.setString("Edytuj!");
							}
							else if (i == 8)
							{
								BoolFunctions::generateSudoku(map,24,25);
								modeText.setString("Edytuj!");
								}
							else if (i == 9)
							{
								BoolFunctions::generateSudoku(map,17,18);
								modeText.setString("Edytuj!");
							}
							else
							{
								window.close();
							}
						}
					}
				}
				else
				{
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							if (rect[i][j].getGlobalBounds().contains(mousePost))
							{
								if (map.vertexArr2[i][j] == 0)
								{
									rect[i][j].setFillColor(sf::Color(0, 255, 0, 128));
									selectedX = j;
									selectedY = i;
								}
							}
							else
							{
								rect[i][j].setFillColor(sf::Color(0, 0, 0, 0));
							}
						}
					}

					warningText.setString("");
					mousePostString.setString("Y: " + to_string(selectedY) + " X: " + to_string(selectedX));

					if (menu.getButton(3).getGlobalBounds().contains(mousePost))
					{
						playing = false;
						menu.playing = false;
						modeText.setString("Edytuj!");
						map.clearVertexArr2();
					}
				}

			}
		}


		window.clear(sf::Color::White);
		system("cls");

		map.draw(window);
		menu.printVertex(map, window);
		window.draw(text);
		window.draw(mousePostString);
		window.draw(warningText);
		window.draw(modeText);
		window.draw(resultText);
		menu.draw(window);

		window.display();
	}

	return 0;
}