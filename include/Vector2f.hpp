#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include <string>

class Vector2f
{
    public:
        float x, y;

        Vector2f();
        Vector2f(float x, float y);

        void add(Vector2f v);
        void sub(Vector2f v);

        void debbug(std::string label);

        void setDirection(float deg);
        float getDirection();

        void setMagnitude(float size);
        float getMagnitude();
};

#endif
