#include "Drawable.h"

Drawable::Drawable(float x, float y) : position(x, y) {}

sf::Vector2f Drawable::getPosition()
{
    return position;
}

void Drawable::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}
