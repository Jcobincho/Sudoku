#pragma once
#include <SFML/Graphics.hpp>

class Drawable
{
protected:
    sf::Vector2f position;

public:
    Drawable(float x, float y);
    virtual void draw(sf::RenderWindow& window) = 0;
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
};
