#ifndef ANTHILL_HPP
#define ANTHILL_HPP

#include <SFML/Graphics.hpp>

#include "Vector2f.hpp"

class AntHill
{
    public:
        Vector2f pos;
        
        AntHill();
        AntHill(float x, float y);

        void draw(sf::RenderWindow &window);

    private:
        sf::CircleShape shape;

        void init();
};


#endif