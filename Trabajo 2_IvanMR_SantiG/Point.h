
#pragma once
#include <vector>

struct Point
{
    float x;
    float y;

    Point();
    Point(float px, float py);
};

// Funciones
void printPoints(const std::vector<Point>& points);

void generateRandomPoints(std::vector<Point>& points, int amount, int width, int height);