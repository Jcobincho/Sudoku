#pragma once
#include "Drawable.h"

class Map : public Drawable
{
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    sf::Font arialFont;

public:
    const int region[9][9];

    int vertexArr2[9][9];
    int vertexArr[9][9];

    Map(sf::Texture _mapTexture, sf::Font arialFont);

    void draw(sf::RenderWindow& window) override;

    void clear();

    void reset();

    void clearVertexArr2();

    int getVertexArrValue(int row, int col) const;
    int getVertexArr2Value(int row, int col) const;

    void setVertexArrValue(int row, int col, int value);
    void setVertexArr2Value(int row, int col, int value);
};
