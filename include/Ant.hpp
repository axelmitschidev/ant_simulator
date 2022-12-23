#ifndef ANT_HPP
#define ANT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <list>

#include "Vector2f.hpp"
#include "Pheromone.hpp"
#include "Food.hpp"
#include "AntHill.hpp"

class Ant
{
    public:
        Ant(int index);
        Ant(float x, float y, int index);

        void update(std::list<Pheromone> *pheromones, std::list<Food>* foods, AntHill* anthill);
        void draw(sf::RenderWindow &window);

    private:
        Vector2f pos;
        Vector2f vel;
        sf::RectangleShape shape;
        int index;
        sf::Clock clock;
        std::string state;
        sf::Clock stateClock;
        Food* food;

        void init();
};

#endif
