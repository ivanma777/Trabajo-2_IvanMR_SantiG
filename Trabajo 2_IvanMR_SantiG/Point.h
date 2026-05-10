#pragma once
#include <vector>

struct Point
{
    float x;
    float y;

    Point();
    Point(float px, float py);
};

extern Point* p0;

// Funciones
void printPoints(const std::vector<Point>& points);
void generateRandomPoints(std::vector<Point>& points, int amount, int width, int height);

float distSq(Point a, Point b);
int orientation(Point p, Point q, Point r);
bool polarOrder(const Point& a, const Point& b);

std::vector<Point> grahamScan(std::vector<Point> points);