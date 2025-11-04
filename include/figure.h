#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <iostream>
#include <memory>

template<ScalarType T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual Point<T> geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    virtual operator double() const { return area(); }
};

template<ScalarType T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& f) {
    f.print(os);
    return os;
}

template<ScalarType T>
std::istream& operator>>(std::istream& is, Figure<T>& f) {
    f.read(is);
    return is;
}

#endif