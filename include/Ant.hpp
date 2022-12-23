#ifndef ANT_HPP
#define ANT_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "Vector2f.hpp"
#include "Pheromone.hpp"

class Ant
{
    public:
        Ant(int index);
        Ant(float x, float y, int index);

        void update(std::list<Pheromone> *pheromones);
        void draw(sf::RenderWindow &window);

    private:
        Vector2f pos;
        Vector2f vel;
        sf::RectangleShape shape;
        int index;
        sf::Clock clock;

        void init();
};

#endif
