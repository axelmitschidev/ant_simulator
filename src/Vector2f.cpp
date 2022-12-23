#include <iostream>
#include <cmath>

#include "Vector2f.hpp"

Vector2f::Vector2f() : x(0.0f), y(0.0f) {}
Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

void Vector2f::add(Vector2f v)
{
    this->x += v.x;
    this->y += v.y;
}

void Vector2f::sub(Vector2f v)
{
    this->x += v.x;
    this->y += v.y;
}

void Vector2f::debbug(std::string label)
{
    std::cout << label << ": (" << this->x << ", " << this->y << ")\n";
}

void Vector2f::setDirection(float deg)
{
    float radiant = deg * M_PI / 180;
    this->x += cos(radiant);
    this->y += sin(radiant);
}

float Vector2f::getDirection()
{
    return atan2(this->y, this->x) * 180 / M_PI;
}

void Vector2f::setMagnitude(float size)
{
    float radiant = this->getDirection() * M_PI / 180;
    this->x = cos(radiant) * size;
    this->y = sin(radiant) * size;
}

float Vector2f::getMagnitude()
{
    return sqrt(this->y * this->y + this->x * this->x);
}
