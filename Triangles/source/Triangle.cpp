#include "Triangle.h"

Triangle::Triangle(const vec2& p1, const vec2& p2, const vec2& p3, const float inMovementSpeed)
    : points{ p1, p2, p3 }
    , sfTriangle(sf::Triangles, 3)
    , movementSpeed(inMovementSpeed)
{
    for (int i = 0; i < 3; i++)
    {
        sfTriangle[i].position = points[i];
        sfTriangle[i].color = sf::Color::Green;
    }
}

void Triangle::move(float scaleX, float scaleY)
{
    for (int i = 0; i < 3; i++)
    {
        points[i].x += (scaleX * movementSpeed);
        points[i].y += (scaleY * movementSpeed);
        sfTriangle[i].position = points[i];
    }
}

void Triangle::setColor(sf::Color inColor)
{
    for (int i = 0; i < 3; i++)
    {
        sfTriangle[i].color = inColor;
    }
}

void Triangle::setMovementSpeed(const float newMovementSpeed)
{
    movementSpeed = newMovementSpeed;
}

bool Triangle::isColliding(triangle& triangle1, triangle& triangle2)
{
    int aX = triangle1[0].x;
    int aY = triangle1[0].y;

    int bX = triangle1[1].x;
    int bY = triangle1[1].y;

    int cX = triangle1[2].x;
    int cY = triangle1[2].y;

    int aX2 = triangle2[0].x;
    int aY2 = triangle2[0].y;

    int bX2 = triangle2[1].x;
    int bY2 = triangle2[1].y;

    int cX2 = triangle2[2].x;
    int cY2 = triangle2[2].y;


    int triangle1Area = (aX * (bY - cY) + bX * (cY - aY) + cX * (aY - bY)) / 2;

    int segment1Area = (aX * (bY - aY2) + bX * (aY2 - aY) + aX2 * (aY - bY)) / 2;

    int segment2Area = (aX * (aY2 - cY) + aX2 * (cY - aY) + cX * (aY - aY2)) / 2;

    int segment3Area = (aX2 * (bY - cY) + bX * (cY - aY2) + cX * (aY2 - bY)) / 2;

    return triangle1Area != (segment1Area + segment2Area + segment3Area);
}
