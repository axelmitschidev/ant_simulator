#include "AntHill.hpp"

AntHill::AntHill()
{
    this->pos = Vector2f(0, 0);
    this->init();
}

AntHill::AntHill(float x, float y)
{
    this->pos = Vector2f(x, y);
    this->init();
}

void AntHill::draw(sf::RenderWindow &window)
{
    this->shape.setPosition(this->pos.x, this->pos.y);
    window.draw(this->shape);
}

void AntHill::init()
{
    this->shape = sf::CircleShape(100, 20);
    this->shape.setFillColor(sf::Color(100, 100, 255));
}
