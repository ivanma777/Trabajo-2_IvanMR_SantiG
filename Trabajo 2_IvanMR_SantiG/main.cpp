#include <SFML/Graphics.hpp>
#include "Point.h"

int main()
{
    // Vector de puntos
    std::vector<Point> points;

    // Añadir puntos
    srand(static_cast<unsigned>(time(nullptr)));

    generateRandomPoints(points, 20, 800, 600);
    // Crear ventana
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Convex Hull");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        // Dibujar puntos
        for (const Point& p : points)
        {
            sf::CircleShape pointShape(5.f);

            pointShape.setFillColor(sf::Color::White);

            // Ajuste para centrar el círculo
            pointShape.setPosition({ p.x - 5.f, p.y - 5.f });

            window.draw(pointShape);
        }

        window.display();
    }

    return 0;
}