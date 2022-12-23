#include <random>
#include <iostream>

#include "constants.hpp"
#include "Ant.hpp"

std::mt19937 generator(time(nullptr));
std::uniform_real_distribution<double> distributionDirection(-ANT_RAND_DIRECTION, ANT_RAND_DIRECTION);
std::uniform_real_distribution<double> distributionSpawn(0, 360);

Ant::Ant(int index) {
    this->pos.x = 0.0f;
    this->pos.y = 0.0f;
    this->index = index;
    this->clock = sf::Clock();
    this->state = "searching";
    this->stateClock = sf::Clock();
    this->init();
}

Ant::Ant(float x, float y, int index) {
    this->pos.x = x;
    this->pos.y = y;
    this->index = index;
    this->clock = sf::Clock();
    this->state = "searching";
    this->stateClock = sf::Clock();
    this->init();
}

void Ant::update(std::list<Pheromone>* pheromones, std::list<Food>* foods, AntHill* anthill)
{
    if (this->state == "searching")
    {
        Vector2f buff = Vector2f(this->vel.x, this->vel.y);
        for (auto it = pheromones->begin(); it != pheromones->end(); ++it) {
            if (sqrt(pow(it->getPos().x - this->pos.x, 2) + pow(it->getPos().y - this->pos.y, 2)) < ANT_VIEW_RADIUS &&
                it->getAntIndex() != this->index &&
                it->type == 'f') {
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

        if (sqrt(pow(anthill->pos.x + 100 - this->pos.x, 2) + pow(anthill->pos.y + 100 - this->pos.y, 2)) <= 100) {
            this->stateClock.restart();
        }

        float newDirection = this->vel.getDirection() + distributionDirection(generator);
        this->vel.setDirection(newDirection);

        this->pos.add(this->vel);

        sf::Time stateElapsed = this->stateClock.getElapsedTime();
        if (stateElapsed.asSeconds() <= STATE_PHEROMONE_TIME) {
            sf::Time elapsed = this->clock.getElapsedTime();
            if (elapsed.asSeconds() > PHEROMONE_FREQUENCY) {
                pheromones->push_back(Pheromone(this->pos.x, this->pos.y, this->index, 'h'));
                this->clock.restart();
            }
        }

        for (auto it = foods->begin(); it != foods->end(); ++it) {
            if (sqrt(pow(it->getPos().x - this->pos.x, 2) + pow(it->getPos().y - this->pos.y, 2)) <= 6 && !it->isTransporting) {
                
                this->vel.x = -this->vel.x;
                this->vel.y = -this->vel.y;
                this->food = &(*it);
                this->food->isTransporting = true;
                this->stateClock.restart();
                this->state = "collecting";
                break;
            }
        };
        
    }

    if (this->state == "collecting")
    {
        Vector2f buff = Vector2f(this->vel.x, this->vel.y);
        for (auto it = pheromones->begin(); it != pheromones->end(); ++it) {
            if (sqrt(pow(it->getPos().x - this->pos.x, 2) + pow(it->getPos().y - this->pos.y, 2)) < ANT_VIEW_RADIUS &&
                it->getAntIndex() != this->index &&
                it->type == 'h') {
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
        
        if (this->food != nullptr) {
            Food* p_food = this->food;
            p_food->pos.x = this->pos.x - 6;
            p_food->pos.y = this->pos.y - 6;
        }

        sf::Time stateElapsed = this->stateClock.getElapsedTime();
        if (stateElapsed.asSeconds() <= STATE_PHEROMONE_TIME) {
            sf::Time elapsed = this->clock.getElapsedTime();
            if (elapsed.asSeconds() > PHEROMONE_FREQUENCY) {
                pheromones->push_back(Pheromone(this->pos.x, this->pos.y, this->index, 'f'));
                this->clock.restart();
            }
        }
        if (sqrt(pow(this->pos.x - (anthill->pos.x) - 100, 2) + pow(this->pos.y - (anthill->pos.y) - 100, 2)) <= 100) {
            this->vel.x = -this->vel.x;
            this->vel.y = -this->vel.y;
            this->stateClock.restart();
            this->food = nullptr;
            this->state = "searching";
        }
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
    this->food = nullptr;
}
