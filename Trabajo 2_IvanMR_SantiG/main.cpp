#include <SFML/Graphics.hpp>
#include <optional>
#include <ctime>
#include "Point.h"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    // generar puntos aleatorios
    std::vector<Point> points;
    generateRandomPoints(points, 20, 800, 600);

    // calcular convex hull
    std::vector<Point> hull = grahamScan(points);

    // crear la ventana del programa
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Convex Hull - Graham Scan");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        if (hull.size() >= 2)
        {
            sf::VertexArray lines(sf::PrimitiveType::LineStrip, hull.size() + 1);
            for (int i = 0; i <= (int)hull.size(); i++)
            {
                int idx = i % hull.size();
                lines[i].position = { hull[idx].x, hull[idx].y };
                lines[i].color = sf::Color::Cyan;
            }
            window.draw(lines);
        }

        //  Dibujar todos los puntos
        for (const Point& p : points)
        {
            sf::CircleShape dot(5.f);
            dot.setFillColor(sf::Color::White);
            dot.setOrigin({ 5.f, 5.f });
            dot.setPosition({ p.x, p.y });
            window.draw(dot);
        }

        for (const Point& p : hull)
        {
            sf::CircleShape dot(7.f);
            dot.setFillColor(sf::Color::Yellow);
            dot.setOrigin({ 7.f, 7.f });
            dot.setPosition({ p.x, p.y });
            window.draw(dot);
        }

        window.display();
    }

    return 0;
}