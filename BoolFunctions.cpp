#include "BoolFunctions.h"
#include <iostream>
#include <random>
#include<fstream>
#include <stack>
#include <numeric>

using namespace std;

bool BoolFunctions::ThereIsZero(int map[][9], int& i, int& j)
{
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (map[i][j] == 0) return true;
        }
    }
    return false;
} 

bool BoolFunctions::ThereIsZero(int map[][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j] == 0) return true;
        }
    }
    return false;
}

bool BoolFunctions::KolomSafe(int map[][9], int kolom, int number)
{
    for (int i = 0; i < 9; i++)
    {
        if (map[i][kolom] == number)
            return false;
    }
    return true;
}

bool BoolFunctions::BarisSafe(int map[][9], int baris, int number)
{
    for (int i = 0; i < 9; i++)
    {
        if (map[baris][i] == number) return false;
    }
    return true;
}

bool BoolFunctions::isSafe(int map[][9], int row, int col, int number, const int region[][9])
{
    if (!KolomSafe(map, col, number) || !BarisSafe(map, row, number))
    {
        return false;
    }

    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;

    for (int r = boxRowStart; r < boxRowStart + 3; r++)
    {
        for (int d = boxColStart; d < boxColStart + 3; d++)
        {
            if (map[r][d] == number)
            {
                return false;
            }
        }
    }

    return true;
}

bool BoolFunctions::isSafe(Map map, int row, int col, int number)
{
    int regId = map.region[row][col];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map.region[i][j] == regId && row != i && col != j)
            {
                if (map.vertexArr[i][j] == number)
                {
                    return false;
                }
            }
        }
        if (map.vertexArr[row][i] == number && i != col) return false;
        if (map.vertexArr[i][col] == number && i != row) return false;
    }
    return true;
}

bool BoolFunctions::solveSudoku(Map& map, sf::RenderWindow& window, Menu& menu)
{
    sf::Event event;
    if (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return true;
        }
    }

    int x, y;
    bool result = false;
    window.clear();
    system("cls");

    map.draw(window);
    menu.printVertex(map, window);

    window.display();
    if (!ThereIsZero(map.vertexArr, y, x))
    {
        return true;
    }
    for (int i = 1; i <= 9; i++) {
        if (isSafe(map.vertexArr, y, x, i, map.region))
        {
            map.vertexArr[y][x] = i;
            result = solveSudoku(map, window, menu);
            if (result == true)
            {
                return true;
            }
        }
    }
    map.vertexArr[y][x] = 0;
    return false;
}

bool BoolFunctions::solveSudoku(Map& map)
{
    int x, y;
    bool result = false;
    if (!ThereIsZero(map.vertexArr, y, x))
    {
        return true;
    }
    for (int i = 1; i <= 9; i++)
    {
        if (isSafe(map.vertexArr, y, x, i, map.region))
        {
            map.vertexArr[y][x] = i;
            result = solveSudoku(map);
            if (result == true)
            {
                return true;
            }
        }
    }

    map.vertexArr[y][x] = 0;
    return false;
}

bool BoolFunctions::isMapValid(Map map)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map.vertexArr[i][j] != 0)
            {
                if (!isSafe(map, i, j, map.vertexArr[i][j]))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool BoolFunctions::isInt(char _char)
{
    return ('0' <= _char && '9' >= _char);
}

void BoolFunctions::generateSudoku(Map& map,int min, int max)
{
    map.clear();
    map.clearVertexArr2();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(min, max);
    int filledCells = distribution(gen);

    while (filledCells < min)
    {
        filledCells = distribution(gen);
    }

    int currentFilledCells = 0;
    while (currentFilledCells < filledCells)
    {
        int row, col, num;
        do
        {
            row = std::uniform_int_distribution<int>(0, 8)(gen);
            col = std::uniform_int_distribution<int>(0, 8)(gen);
            num = std::uniform_int_distribution<int>(1, 9)(gen);
        } while (!isSafe(map.vertexArr, row, col, num, map.region) || map.vertexArr[row][col] != 0);

        map.vertexArr[row][col] = num;
        map.vertexArr2[row][col] = num;
        ++currentFilledCells;
    }

    if (!isMapValid(map) || !BoolFunctions::solveSudoku2(map))
    {
        // If the generated Sudoku has no solution or is not valid, retry
        generateSudoku(map, min,max);
    }
}


void BoolFunctions::save(Map& map)
{
    std::ofstream saveFile("map.txt");
    if (saveFile.is_open())
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                saveFile << map.getVertexArrValue(i, j) << " ";
            }
            saveFile << std::endl;
        }
        saveFile.close();
    }
    
}

int BoolFunctions::countNumbers(int arr[9][9]) {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (arr[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}

bool BoolFunctions::solveSudoku2(Map& map)
{
    int x, y;
    if (!ThereIsZero(map.vertexArr, y, x))
    {
        return true;
    }

    for (int i = 1; i <= 9; i++)
    {
        if (isSafe(map.vertexArr, y, x, i, map.region))
        {
            map.vertexArr[y][x] = i;
            if (solveSudoku2(map))
            {
                map.vertexArr[y][x] = 0;
                return true;
            }
            map.vertexArr[y][x] = 0;
        }
    }

    return false;
}