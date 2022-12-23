#include "Food.hpp"

Food::Food()
{
    this->pos = Vector2f(0, 0);
    this->init();
}

Food::Food(float x, float y)
{
    this->pos = Vector2f(x, y);
    this->init();
}

void Food::draw(sf::RenderWindow &window)
{
    this->shape.setPosition(this->pos.x, this->pos.y);
    window.draw(this->shape);
}

Vector2f Food::getPos()
{
    return this->pos;
}

void Food::init()
{
    this->isTransporting = false;
    this->shape = sf::CircleShape(6, 10);
    this->shape.setFillColor(sf::Color(100, 255, 100, 150));
}
