#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP

#include <SFML/Graphics.hpp>

#include "Vector2f.hpp"

class Pheromone
{
    public:
        sf::Clock lifetime;
        bool isLiving;

        Pheromone(int antIndex);
        Pheromone(float x, float y, int antIndex);

        void update();
        void draw(sf::RenderWindow &window);

        bool operator==(const Pheromone &p) const;

        Vector2f getPos();

        int getAntIndex();

    private:
        Vector2f pos;
        void init();
        sf::CircleShape shape;
        int antIndex;
};

#endif
