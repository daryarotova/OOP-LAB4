#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T>
concept ScalarType = std::is_scalar_v<T>;

template<ScalarType T>
struct Point {
    T x{};
    T y{};

    Point() = default;
    Point(T x_, T y_) : x(x_), y(y_) {}

    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point<T>& p) {
        is >> p.x >> p.y;
        return is;
    }

    bool operator==(const Point<T>& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point<T>& other) const {
        return !(*this == other);
    }
};

#endif