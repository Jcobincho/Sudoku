#pragma once
#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "Map.h"
#include "ToString.h"

class Menu : public Drawable
{
	sf::Texture playButtonTexture, solveButtonTexture, solve2ButtonTexture, exitButtonTexture, generateButtonTexture, saveButtonTexture, resetButtonTexture, generateEasyButtonTexture, generateMediumButtonTexture, generateHardButtonTexture;
	sf::Sprite playButtonSprite, solveButtonSprite, solve2ButtonSprite, exitButtonSprite, generateButtonSprite, saveButtonSprite, resetButtonSprite, generateEasyButtonSprite, generateMediumButtonSprite, generateHardButtonSprite;

public:
	
	

	bool playing = false;

	Menu(sf::Texture mapTexture);

	void draw(sf::RenderWindow& window);

	sf::Sprite getButton(int id);

	void printVertex(Map map, sf::RenderWindow& window);
};
