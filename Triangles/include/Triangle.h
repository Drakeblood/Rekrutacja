#pragma once

#include <array>
#include<SFML/Graphics.hpp>

struct vec2
{
    float x, y;

    operator sf::Vector2f()
    {
        return sf::Vector2f(x, y);
    }

    static float dot(const vec2& v1, const vec2& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static float cross(const vec2& v1, const vec2& v2)
    {
        return v1.x * v2.y - v1.y * v2.x;
    }
};

struct triangle
{
    std::array<vec2, 3> points;

    vec2& operator[](int index) { return points[index]; }
};

class Triangle
{
public:
    Triangle(const vec2& p1, const vec2& p2, const vec2& p3, const float inMovementSpeed = 12.f);

    void move(float scaleX, float scaleY);
    void setColor(sf::Color inColor);
    void setMovementSpeed(const float newMovementSpeed);

    const sf::VertexArray& getVertexArray() const { return sfTriangle; }
    const sf::Color& getColor() const { return sfTriangle[0].color; }
    triangle getTriangle() const { return tri; }

    static bool isColliding(triangle& triangle1, triangle& triangle2);

private:
    vec2 points[3];
    triangle tri;
    sf::VertexArray sfTriangle;

    float movementSpeed;
};