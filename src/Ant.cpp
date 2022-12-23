#include <random>

#include "constants.hpp"
#include "Ant.hpp"

std::mt19937 generator(time(nullptr));
std::uniform_real_distribution<double> distributionDirection(-40, 40);
std::uniform_real_distribution<double> distributionSpawn(0, 360);

Ant::Ant(int index) {
    this->pos.x = 0.0f;
    this->pos.y = 0.0f;
    this->index = index;
    this->init();
}

Ant::Ant(float x, float y, int index) {
    this->pos.x = x;
    this->pos.y = y;
    this->index = index;
    this->clock = sf::Clock();
    this->init();
}

void Ant::update(std::list<Pheromone>* pheromones)
{
    Vector2f buff = Vector2f(this->vel.x, this->vel.y);
    for (auto it = pheromones->begin(); it != pheromones->end(); ++it) {
        if (sqrt(pow(it->getPos().x - this->pos.x, 2) + pow(it->getPos().y - this->pos.y, 2)) < ANT_VIEW_RADIUS &&
            it->getAntIndex() != this->index)
        {
            int power = 1 - (int)(it->lifetime.getElapsedTime().asSeconds() / PHEROMONE_LIFETIME);
            buff.x += (it->getPos().x - this->pos.x) * it->lifetime.getElapsedTime().asSeconds() * power;
            buff.y += (it->getPos().y - this->pos.y) * it->lifetime.getElapsedTime().asSeconds() * power;
        }
    };

    this->vel.x += buff.x / PHEROMONE_REDUCER;
    this->vel.y += buff.y / PHEROMONE_REDUCER;
    this->vel.setMagnitude(ANT_SPEED);

    if (this->pos.x < 0) this->vel.x = -this->vel.x;
    if (this->pos.y < 0) this->vel.y = -this->vel.y;
    if (this->pos.x > WINDOW_WIDTH) this->vel.x = -this->vel.x;
    if (this->pos.y > WINDOW_HEIGHT) this->vel.y = -this->vel.y;

    float newDirection = this->vel.getDirection() + distributionDirection(generator);
    this->vel.setDirection(newDirection);

    this->pos.add(this->vel);

    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() > PHEROMONE_FREQUENCY)
    {
        pheromones->push_back(Pheromone(this->pos.x, this->pos.y, this->index));
        this->clock.restart();
    }
}

void Ant::draw(sf::RenderWindow &window)
{
    this->shape.setRotation(this->vel.getDirection());
    this->shape.setPosition(this->pos.x, this->pos.y);
    window.draw(this->shape);
}

void Ant::init()
{
    this->vel.setDirection(distributionSpawn(generator));
    this->shape = sf::RectangleShape(sf::Vector2f(18, 6));
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(1);
    this->shape.setOrigin(sf::Vector2f(9, 3));
}