#include "Point.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(float px, float py)
{
    x = px;
    y = py;
}

void printPoints(const std::vector<Point>& points)
{
    for (const Point& p : points)
    {
        std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
    }
}

void generateRandomPoints(std::vector<Point>& points, int amount, int width, int height)
{
    points.clear();

    for (int i = 0; i < amount; i++)
    {
        float x = rand() % width;
        float y = rand() % height;

        points.push_back(Point(x, y));
    }
}

//metodo graham
int orientation(Point p, Point q, Point r)
{
    float value = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (value == 0)
        return 0;

    return (value > 0) ? 1 : 2;
}