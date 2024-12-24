#include <iostream>
#include <math.h>
using namespace std;

struct Point
{
    double x = 0;
    double y = 0;

    void rot(double angle)
    {
        double new_x = x * cos(angle) - y * sin(angle);
        double new_y = x * sin(angle) + y * cos(angle);
        x = new_x;
        y = new_y;
    }

    void rot(int degree)
    {
        double pi = atan(1) * 4;
        double angle = double(degree) / 180 * pi;
        rot(angle);
    }

    double norm()
    {
        return sqrt(x * x + y * y);
    }

    double arg()
    {
        return atan2(y, x);
    }

    double operator*(Point &other)
    {
        return x * other.x + y * other.y;
    }

    double operator^(Point &other)
    {
        return x * other.y - y * other.x;
    }

    Point operator+(Point &other)
    {
        Point ans;
        ans.x = x + other.x;
        ans.y = y + other.y;
        return ans;
    }

    Point operator-(Point &other)
    {
        Point ans;
        ans.x = x - other.x;
        ans.y = y - other.y;
        return ans;
    }

    int ccw(Point B, Point C)
    {
        Point A = *this;
        Point AB = B - A;
        Point AC = C - A;
        double cross = AB ^ AC;
        if (cross > 0)
        {
            return 1;
        }
        else if (cross == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
        return true;
    }
};

ostream &operator<<(ostream &os, Point p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
