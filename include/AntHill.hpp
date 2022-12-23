#ifndef ANTHILL_HPP
#define ANTHILL_HPP

#include <SFML/Graphics.hpp>

#include "Vector2f.hpp"

class AntHill
{
    public:
        AntHill();
        AntHill(float x, float y);

        void draw(sf::RenderWindow &window);

    private:
        Vector2f pos;
        sf::CircleShape shape;

        void init();
};


#endif