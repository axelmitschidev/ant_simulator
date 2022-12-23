#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>

#include "Vector2f.hpp"

class Food
{
    public:
        bool isTransporting;
        Vector2f pos;
        Food();
        Food(float x, float y);

        void draw(sf::RenderWindow &window);

        Vector2f getPos();

    private:
        sf::CircleShape shape;
        void init();
};

#endif