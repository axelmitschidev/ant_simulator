#include <iostream>

#include "Pheromone.hpp"
#include "constants.hpp"

Pheromone::Pheromone(int antIndex) {
    this->pos.x = 0.0f;
    this->pos.y = 0.0f;
    this->antIndex = antIndex;
    this->isLiving = true;
    this->init();
}

Pheromone::Pheromone(float x, float y, int antIndex) {
    this->pos.x = x;
    this->pos.y = y;
    this->antIndex = antIndex;
    this->isLiving = true;
    this->init();
}

void Pheromone::update()
{
    sf::Time elapsed = this->lifetime.getElapsedTime();
    if (elapsed.asSeconds() > PHEROMONE_LIFETIME) this->isLiving = false;
}

void Pheromone::draw(sf::RenderWindow &window)
{
    this->shape.setPosition(this->pos.x, this->pos.y);
    int opacity = 255 - (int)(this->lifetime.getElapsedTime().asSeconds() / PHEROMONE_LIFETIME * 255);
    this->shape.setFillColor(sf::Color(100, 100, 255, opacity));
    window.draw(this->shape);
}

bool Pheromone::operator==(const Pheromone &p) const
{
    return !this->isLiving;
}

Vector2f Pheromone::getPos()
{
    return this->pos;
}

int Pheromone::getAntIndex()
{
    return this->antIndex;
}

void Pheromone::init()
{
    this->shape = sf::CircleShape(3, 3);
    this->lifetime = sf::Clock();
}