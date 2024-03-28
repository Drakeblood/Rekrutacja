#include <SFML/Graphics.hpp>

#include "Triangle.h"

int main()
{
    auto window = sf::RenderWindow{ { 1280u, 768u }, "Triangles" };
    window.setFramerateLimit(60);

    Triangle hero(vec2{ 400, 100 }, vec2{ 300, 300 }, vec2{ 500, 300 });
    Triangle enemy(vec2{ 200, 400 }, vec2{ 100, 600 }, vec2{ 300, 600 });

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) hero.move(-1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) hero.move(1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) hero.move(0.f, -1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) hero.move(0.f, 1.f);

        if (Triangle::isColliding(enemy.getTriangle(), hero.getTriangle()))
        {
            if (hero.getColor() != sf::Color::Red)
            {
                enemy.setColor(sf::Color::Red);
                hero.setColor(sf::Color::Red);
            }
        }
        else 
        {
            if (hero.getColor() != sf::Color::Green)
            {
                enemy.setColor(sf::Color::Green);
                hero.setColor(sf::Color::Green);
            }
        }

        window.clear();
        window.draw(enemy.getVertexArray());
        window.draw(hero.getVertexArray());
        window.display();

        window.clear();
        window.display();
    }
}