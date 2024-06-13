#include "Map.h"
#include"Numb.h"
#include"ToString.h"
//#include"Font.h"

Map::Map(sf::Texture _mapTexture, sf::Font arialFont) : Drawable(50, 50), region{ {1, 1, 2, 2, 2, 2, 2, 3, 3},
                                                            {1, 1, 1, 2, 2, 2, 3, 3, 3},
                                                            {4, 1, 1, 1, 2, 3, 3, 3, 5},
                                                            {4, 4, 1, 6, 6, 6, 3, 5, 5},
                                                            {4, 4, 4, 6, 6, 6, 5, 5, 5},
                                                            {4, 4, 7, 6, 6, 6, 8, 5, 5},
                                                            {4, 7, 7, 7, 9, 8, 8, 8, 5},
                                                            {7, 7, 7, 9, 9, 9, 8, 8, 8},
                                                            {7, 7, 9, 9, 9, 9, 9, 8, 8} }
{
    //arialFont.loadFromMemory(&arial_ttf, arial_ttf_len);
    mapTexture = _mapTexture;
    mapSprite.setTexture(mapTexture);
    mapSprite.setPosition(50, 50);
    mapSprite.setScale(sf::Vector2f(0.25, 0.25));

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            vertexArr[i][j] = 0;
            vertexArr2[i][j] = 0;
        }
    }
}

void Map::draw(sf::RenderWindow& window)
{
    window.draw(mapSprite);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (vertexArr[i][j] != 0)
            {
                //numb.setPosition(50 + j * 52, 50 + i * 52);
                //numb.setString(ToString::ConvertToString(vertexArr[i][j]));
                window.draw(numb);
            }
        }
    }
}

void Map::clear()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            vertexArr[i][j] = 0;
        }
    }
}

void Map::reset()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            vertexArr[i][j] = vertexArr2[i][j];
        }
    }
}

void Map::clearVertexArr2()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            vertexArr2[i][j] = 0;
        }
    }
}

int Map::getVertexArrValue(int row, int col) const
{
    return vertexArr[row][col];
}

int Map::getVertexArr2Value(int row, int col) const
{
    return vertexArr2[row][col];
}

void Map::setVertexArrValue(int row, int col, int value) 
{
    vertexArr[row][col] = value;
}

void Map::setVertexArr2Value(int row, int col, int value)
{
    vertexArr2[row][col] = value;
}
