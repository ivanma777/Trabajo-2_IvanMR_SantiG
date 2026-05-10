#include "Point.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <stack>

// Definicion del puntero global a P0
Point* p0 = nullptr;

// Constructores
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

// Utilidades
void printPoints(const std::vector<Point>& points)
{
    for (const Point& p : points)
        std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
}

void generateRandomPoints(std::vector<Point>& points, int amount, int width, int height)
{
    points.clear();
    for (int i = 0; i < amount; i++)
        points.push_back(Point((float)(rand() % width), (float)(rand() % height)));
}

//Distancia al cuadrado entre dos puntos
float distSq(Point a, Point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

//Orientacion de 3 puntos
// 0 = colineal, 1 = horario, 2 = antihorario
int orientation(Point p, Point q, Point r)
{
    float value = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);
    if (value == 0) return 0;
    return (value > 0) ? 1 : 2;
}

//Comparador por angulo polar respecto a p0 
bool polarOrder(const Point& a, const Point& b)
{
    int o = orientation(*p0, a, b);
    if (o == 0)
        return distSq(*p0, a) < distSq(*p0, b); // mas cercano primero
    return o == 2; // antihorario primero
}

// Graham Scan 
std::vector<Point> grahamScan(std::vector<Point> pts)
{
    int n = pts.size();
    if (n < 3) return pts;

    //buscar P0
    int minIdx = 0;
    for (int i = 1; i < n; i++)
        if (pts[i].y < pts[minIdx].y ||
            (pts[i].y == pts[minIdx].y && pts[i].x < pts[minIdx].x))
            minIdx = i;

    std::swap(pts[0], pts[minIdx]);
    p0 = &pts[0]; // puntero a P0

    //ordenar los n-1 puntos restantes
    std::sort(pts.begin() + 1, pts.end(), polarOrder);

    //eliminar colineales 
    std::vector<Point> f;
    f.push_back(pts[0]);
    for (int i = 1; i < n; )
    {
        int j = i;
        while (j < n - 1 && orientation(*p0, pts[j], pts[j + 1]) == 0)
            j++;
        f.push_back(pts[j]);
        i = j + 1;
    }

    //menos de 3 puntos
    if (f.size() < 3) return f;

    //crear stack y push 3 primeros
    std::stack<Point> S;
    S.push(f[0]);
    S.push(f[1]);
    S.push(f[2]);

    //acabar con el resto
    for (int i = 3; i < (int)f.size(); i++)
    {
        // quitar puntos antihorarios
        while (S.size() > 1)
        {
            Point top = S.top(); S.pop();
            if (orientation(S.top(), top, f[i]) == 2) // antihorario
            {
                S.push(top);
                break;
            }
        }
        S.push(f[i]);
    }

    // extraer resultado
    std::vector<Point> hull;
    while (!S.empty())
    {
        hull.push_back(S.top());
        S.pop();
    }
    std::reverse(hull.begin(), hull.end());
    return hull;
}