#include "Menu.h"
#include"Map.h"
#include"Numb.h"
#include"RectangleShape.h"
#include <iostream>

#include"ButtonPlay.h"
#include"ButtonExit.h"
#include"ButtonSolve.h"
#include"ButtonSolveSpecial.h"
#include"ButtonGenerate.h"
#include"ButtonSave.h"
#include"ButtonReset.h"
#include"ButtonLatwy.h"
#include"ButtonSredni.h"
#include"ButtonTrudny.h"

//#include"Mapa.h"

Menu::Menu(sf::Texture mapTexture) : Drawable(720, 50)
{
	playButtonTexture.loadFromMemory(&img_ButtonPlay_png, img_ButtonPlay_png_len);
	solveButtonTexture.loadFromMemory(&img_ButtonSolve_png, img_ButtonSolve_png_len);
	solve2ButtonTexture.loadFromMemory(&img_ButtonSolveSpecial_png, img_ButtonSolveSpecial_png_len);
	exitButtonTexture.loadFromMemory(&img_ButtonExit_png, img_ButtonExit_png_len);
	generateButtonTexture.loadFromMemory(&img_Button_png, img_Button_png_len);
	saveButtonTexture.loadFromMemory(&img_ButtonSave_png, img_ButtonSave_png_len);
	resetButtonTexture.loadFromMemory(&img_ButtonReset_png, img_ButtonReset_png_len);
	generateEasyButtonTexture.loadFromMemory(&img_Buttonlatwy_png, img_Buttonlatwy_png_len);
	generateMediumButtonTexture.loadFromMemory(&img_Buttonsredni_png, img_Buttonsredni_png_len);
	generateHardButtonTexture.loadFromMemory(&img_Buttontrudny_png, img_Buttontrudny_png_len);

	playButtonSprite.setTexture(playButtonTexture);
	solveButtonSprite.setTexture(solveButtonTexture);
	solve2ButtonSprite.setTexture(solve2ButtonTexture);
	generateButtonSprite.setTexture(generateButtonTexture);
	exitButtonSprite.setTexture(exitButtonTexture);
	saveButtonSprite.setTexture(saveButtonTexture);
	resetButtonSprite.setTexture(resetButtonTexture);
	generateEasyButtonSprite.setTexture(generateEasyButtonTexture);
	generateMediumButtonSprite.setTexture(generateMediumButtonTexture);
	generateHardButtonSprite.setTexture(generateHardButtonTexture);

	playButtonSprite.setPosition(820, 50);
	solveButtonSprite.setPosition(820, 114);
	solve2ButtonSprite.setPosition(820, 178);
	exitButtonSprite.setPosition(820, 242);
	generateButtonSprite.setPosition(820, 306);
	saveButtonSprite.setPosition(820, 370);
	resetButtonSprite.setPosition(820, 434);
	generateEasyButtonSprite.setPosition(550, 50);
	generateMediumButtonSprite.setPosition(550, 114);
	generateHardButtonSprite.setPosition(550, 178);

	playButtonSprite.setScale(0.5, 0.5);
	solveButtonSprite.setScale(0.5, 0.5);
	solve2ButtonSprite.setScale(0.5, 0.5);
	generateButtonSprite.setScale(0.5, 0.5);
	exitButtonSprite.setScale(0.5, 0.5);
	saveButtonSprite.setScale(0.5, 0.5);
	resetButtonSprite.setScale(0.5, 0.5);
	generateEasyButtonSprite.setScale(0.5, 0.5);
	generateMediumButtonSprite.setScale(0.5, 0.5);
	generateHardButtonSprite.setScale(0.5, 0.5);
}

void Menu::draw(sf::RenderWindow& window)
{
	if (!playing)
	{
		window.draw(playButtonSprite);
		window.draw(solveButtonSprite);
		window.draw(solve2ButtonSprite);
		window.draw(generateButtonSprite);
		window.draw(saveButtonSprite);
		window.draw(resetButtonSprite);
		window.draw(generateEasyButtonSprite);
		window.draw(generateMediumButtonSprite);
		window.draw(generateHardButtonSprite);
	}
	window.draw(exitButtonSprite);
}

sf::Sprite Menu::getButton(int id)
{
	if (id == 0)
	{
		return playButtonSprite;
	}
	else if (id == 1)
	{
		return solveButtonSprite;
	}
	else if (id == 2)
	{
		return solve2ButtonSprite;
	}
	else if (id == 4)
	{
		return generateButtonSprite;
	}
	else if (id == 5)
	{
		return saveButtonSprite;
	}
	else if (id == 6)
	{
		return resetButtonSprite;
	}
	else if (id == 7)
	{
		return generateEasyButtonSprite;
	}
	else if (id == 8)
	{
		return generateMediumButtonSprite;
	}
	else if (id == 9)
	{
		return generateHardButtonSprite;
	}
	else
	{
		return exitButtonSprite;
	}
}

void Menu::printVertex(Map map, sf::RenderWindow& window)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << map.getVertexArrValue(i, j) << " ";

			if (map.getVertexArr2Value(i, j) != 0)
			{
				numb.setFillColor(sf::Color::Blue);
				numb.setString(ToString::ConvertToString(map.getVertexArrValue(i, j)));
				numb.setPosition((j + 1) * 52, (i + 1) * 52);
				window.draw(numb);
			}
			else if (map.getVertexArrValue(i, j) != 0)
			{
				numb.setFillColor(sf::Color::Black);
				numb.setString(ToString::ConvertToString(map.getVertexArrValue(i, j)));
				numb.setPosition((j + 1) * 52, (i + 1) * 52);
				window.draw(numb);
			}
			if (i == 0 && j == 0)
			{
				rect[i][j].setPosition((j + 1) * 50, (i + 1) * 50);
			}
			else
			{
				rect[i][j].setPosition((j + 1) * 52, (i + 1) * 52);
			}
			window.draw(rect[i][j]);
		}
		std::cout << std::endl;
	}
}
