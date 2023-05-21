#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cmath>
#include <iomanip>

class Point {
public:
    int64_t x, y;
    Point() : Point(0, 0) {}
    Point(int64_t x, int64_t y) : x(x), y(y) {}

    Point operator+(Point other) { return {x + other.x, y + other.y}; }
    Point operator-(Point other) { return {x - other.x, y - other.y}; }
    inline int64_t operator*(Point other) { return x * other.x + y * other.y; }
    inline int64_t operator^(Point other) { return x * other.y - y * other.x; }
    bool operator==(Point other) { return x == other.x && y == other.y; }

    inline static uint64_t SqLen(Point point) { return point.x * point.x + point.y * point.y; }

    inline static int64_t TriangleArea(Point a, Point b, Point c) {
        return (b - a).x * (c - a).y - (b - a).y * (c - a).x;
    }
};

std::istream& operator>>(std::istream &in, Point &p) { 
    in >> p.x >> p.y;
    return in;
}

std::ostream& operator<<(std::ostream &out, Point &p) { 
    out << p.x << " " << p.y << "\n";
    return out;            
}


std::vector<Point> Graham(std::vector<Point> points) {
    // find point to start with
    Point p0 = points[0];
    for (Point p : points) {
        if (p.x < p0.x || (p.x == p0.x && p.y < p0.y)) {
            p0 = p;
        }
    }

    // sort by polar angle
        std::sort(points.begin(), points.end(), [&](Point a, Point b){
        int64_t cur_area = (a - p0) ^ (b - p0);
        return cur_area < 0 || (cur_area == 0 && Point::SqLen(p0 - a) > Point::SqLen(p0 - b));
    });

    std::vector<Point> hull;
    for (Point p : points) {
        // pop point from stack while the figure is not convex
        while (hull.size() >= 2) {
            Point new_vector = p - hull.back();
            Point last_vector = hull.back() - hull[hull.size() - 2];

            if ((new_vector ^ last_vector) <= 0) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(p);
    }
    return hull;
}

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i];
    }

    std::vector<Point> convex_hull = Graham(points);

    int64_t area = 0;
    for (uint64_t i = 1; i < convex_hull.size() - 1; ++i) {
        area += Point::TriangleArea(convex_hull[0], convex_hull[i + 1], convex_hull[i]);
    }

    std::cout << convex_hull.size() << "\n";
    std::cout << convex_hull[convex_hull.size() - 1];
    for (uint64_t i = 0; i < convex_hull.size() - 1; ++i) {
        std::cout << convex_hull[i];
    }
    std::cout << std::setprecision(1) << std::fixed << static_cast<double>(llabs(area)) / 2;

    return 0; 
}
