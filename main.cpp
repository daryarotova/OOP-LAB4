#include <iostream>
#include <memory>
#include "include/array.h"
#include "include/rectangle.h"
#include "include/trapeze.h"
#include "include/rhomb.h"

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;

    int n;
    std::cout << "Количество фигур: ";
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int choice;
        std::cout << "Тип фигуры " << i + 1 << ":\n";
        std::cout << "1 - Прямоугольник\n";
        std::cout << "2 - Трапеция\n";
        std::cout << "3 - Ромб\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        std::shared_ptr<Figure<double>> figure;

        switch (choice) {
            case 1:
                figure = std::make_shared<Rectangle<double>>();
                break;
            case 2:
                figure = std::make_shared<Trapeze<double>>();
                break;
            case 3:
                figure = std::make_shared<Rhomb<double>>();
                break;
            default:
                i--;
                continue;
        }

        std::cout << "Введите 4 вершины:\n";
        std::cin >> *figure;
        figures.Add(figure);
    }

    std::cout << "\nВсе фигуры:\n";
    for (size_t i = 0; i < figures.Size(); i++) {
        std::cout << "Фигура " << i << ":\n";
        std::cout << *figures[i] << std::endl;
        Point<double> center = figures[i]->geometricCenter();
        std::cout << "Центр: " << center << std::endl;
        std::cout << "Площадь: " << figures[i]->area() << "\n\n";
    }

    double total = 0.0;
    for (size_t i = 0; i < figures.Size(); i++) {
        total += figures[i]->area();
    }
    std::cout << "Общая площадь: " << total << std::endl;

    char removeChoice;
    std::cout << "Удалить фигуру? (y/n): ";
    std::cin >> removeChoice;

    if (removeChoice == 'y' || removeChoice == 'Y') {
        size_t index;
        std::cout << "Индекс: ";
        std::cin >> index;

        if (index < figures.Size()) {
            figures.Remove(index);

            std::cout << "\nПосле удаления:\n";
            for (size_t i = 0; i < figures.Size(); i++) {
                std::cout << "Фигура " << i << ":\n";
                std::cout << *figures[i] << std::endl;
                Point<double> center = figures[i]->geometricCenter();
                std::cout << "Центр: " << center << std::endl;
                std::cout << "Площадь: " << figures[i]->area() << "\n\n";
            }

            double newTotal = 0.0;
            for (size_t i = 0; i < figures.Size(); i++) {
                newTotal += figures[i]->area();
            }
            std::cout << "Общая площадь: " << newTotal << std::endl;
        }
    }

    return 0;
}