#ifndef RHOMB_H
#define RHOMB_H

#include "figure.h"
#include <vector>
#include <memory>
#include <cmath>

template<ScalarType T>
class Rhomb : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> vertices;
    
    void initializeVertices() {
        vertices.clear();
        for (int i = 0; i < 4; ++i) {
            vertices.push_back(std::make_unique<Point<T>>());
        }
    }

public:
    Rhomb() { initializeVertices(); }
    
    Rhomb(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4) {
        initializeVertices();
        *vertices[0] = Point<T>(x1, y1);
        *vertices[1] = Point<T>(x2, y2);
        *vertices[2] = Point<T>(x3, y3);
        *vertices[3] = Point<T>(x4, y4);
    }
    
    Rhomb(const Rhomb<T>& other) {
        initializeVertices();
        for (size_t i = 0; i < 4; ++i) {
            *vertices[i] = *other.vertices[i];
        }
    }
    
    Rhomb<T>& operator=(const Rhomb<T>& other) {
        if (this != &other) {
            for (size_t i = 0; i < 4; ++i) {
                *vertices[i] = *other.vertices[i];
            }
        }
        return *this;
    }

    Point<T> geometricCenter() const override {
        T cx = 0;
        T cy = 0;
        for (const auto& p : vertices) {
            cx += p->x;
            cy += p->y;
        }
        return Point<T>(cx / 4, cy / 4);
    }

    double area() const override {
        T d1 = std::sqrt(std::pow(vertices[0]->x - vertices[2]->x, 2) + 
                        std::pow(vertices[0]->y - vertices[2]->y, 2));
        T d2 = std::sqrt(std::pow(vertices[1]->x - vertices[3]->x, 2) + 
                        std::pow(vertices[1]->y - vertices[3]->y, 2));
        return static_cast<double>(d1 * d2 / 2);
    }

    void print(std::ostream& os) const override {
        os << "Rhomb: ";
        for (const auto& p : vertices) {
            os << *p << " ";
        }
        os << "| Center: " << geometricCenter() << " | Area: " << area();
    }

    void read(std::istream& is) override {
        for (auto& p : vertices) {
            is >> *p;
        }
    }

    bool operator==(const Figure<T>& other) const override {
        auto rhs = dynamic_cast<const Rhomb<T>*>(&other);
        if (!rhs) return false;
        
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (*vertices[i] != *rhs->vertices[i]) {
                return false;
            }
        }
        return true;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rhomb<T>>(*this);
    }
};

#endif