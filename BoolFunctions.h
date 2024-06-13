#pragma once
#include "Map.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>

class BoolFunctions
{
public:
    static bool ThereIsZero(int map[][9], int& i, int& j);
    static bool ThereIsZero(int map[][9]);
    static bool KolomSafe(int map[][9], int kolom, int number);
    static bool BarisSafe(int map[][9], int baris, int number);
    static bool isSafe(int map[][9], int row, int col, int number, const int region[][9]);
    static bool isSafe(Map map, int row, int col, int number);
    static bool solveSudoku(Map& map, sf::RenderWindow& window, Menu& menu);
    static bool solveSudoku(Map& map);
    static bool isMapValid(Map map);
    static bool isInt(char _char);
    static void generateSudoku(Map& map, int min, int max);
    static void save(Map& map);
    static int countNumbers(int arr[9][9]);

    static bool solveSudoku2(Map& map);
};
