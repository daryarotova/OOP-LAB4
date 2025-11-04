#include <gtest/gtest.h>
#include <sstream>
#include "../include/rectangle.h"
#include "../include/trapeze.h"
#include "../include/rhomb.h"
#include "../include/array.h"

TEST(FigureTest, RectangleConstructorAndArea) {
    Rectangle<double> rect(0, 0, 2, 0, 2, 2, 0, 2);
    EXPECT_NEAR(double(rect), 4.0, 1e-5);
}

TEST(FigureTest, RectangleGeometricCenter) {
    Rectangle<double> rect(0, 0, 4, 0, 4, 2, 0, 2);
    Point<double> center = rect.geometricCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-5);
    EXPECT_NEAR(center.y, 1.0, 1e-5);
}

TEST(FigureTest, RhombConstructorAndArea) {
    Rhomb<double> rhomb(0, 1, 1, 0, 0, -1, -1, 0);
    EXPECT_NEAR(double(rhomb), 2.0, 1e-5);
}

TEST(FigureTest, RhombGeometricCenter) {
    Rhomb<double> rhomb(0, 2, 2, 0, 0, -2, -2, 0);
    Point<double> center = rhomb.geometricCenter();
    EXPECT_NEAR(center.x, 0.0, 1e-5);
    EXPECT_NEAR(center.y, 0.0, 1e-5);
}

TEST(FigureTest, TrapezeConstructorAndArea) {
    Trapeze<double> trap(0, 0, 4, 0, 3, 2, 1, 2);
    EXPECT_NEAR(double(trap), 6.0, 1e-5);
}

TEST(FigureTest, TrapezeGeometricCenter) {
    Trapeze<double> trap(0, 0, 4, 0, 3, 2, 1, 2);
    Point<double> center = trap.geometricCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-5);
    EXPECT_NEAR(center.y, 1.0, 1e-5);
}

TEST(FigureTest, FigureComparison) {
    Rectangle<double> rect1(0, 0, 2, 0, 2, 2, 0, 2);
    Rectangle<double> rect2(0, 0, 2, 0, 2, 2, 0, 2);
    EXPECT_TRUE(rect1.operator==(rect2));
}

TEST(FigureTest, RectangleStreamInputOutput) {
    Rectangle<double> rect;
    std::istringstream iss("0 0 2 0 2 2 0 2");
    iss >> rect;
    std::ostringstream oss;
    oss << rect;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Rectangle") != std::string::npos);
}

TEST(FigureTest, RhombStreamInputOutput) {
    Rhomb<double> rhomb;
    std::istringstream iss("0 1 1 0 0 -1 -1 0");
    iss >> rhomb;
    std::ostringstream oss;
    oss << rhomb;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Rhomb") != std::string::npos);
}

TEST(FigureTest, TrapezeStreamInputOutput) {
    Trapeze<double> trap;
    std::istringstream iss("0 0 4 0 3 2 1 2");
    iss >> trap;
    std::ostringstream oss;
    oss << trap;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Trapeze") != std::string::npos);
}

TEST(FigureArrayTest, AddAndTotalArea) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto rect = std::make_shared<Rectangle<double>>();
    auto rhomb = std::make_shared<Rhomb<double>>();
    
    std::istringstream rect_iss("0 0 2 0 2 2 0 2");
    std::istringstream rhomb_iss("0 1 1 0 0 -1 -1 0");
    
    rect_iss >> *rect;
    rhomb_iss >> *rhomb;
    
    arr.Add(rect);
    arr.Add(rhomb);
    
    double total = 0.0;
    for (size_t i = 0; i < arr.Size(); i++) {
        total += arr[i]->area();
    }
    
    EXPECT_NEAR(total, 4.0 + 2.0, 1e-5);
}

TEST(FigureArrayTest, RemoveFigure) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto rect = std::make_shared<Rectangle<double>>();
    std::istringstream iss("0 0 2 0 2 2 0 2");
    iss >> *rect;
    
    arr.Add(rect);
    EXPECT_EQ(arr.Size(), 1);
    
    arr.Remove(0);
    EXPECT_EQ(arr.Size(), 0);
}

TEST(FigureArrayTest, ArrayCopyConstructor) {
    Array<std::shared_ptr<Figure<double>>> arr1;
    
    auto rect = std::make_shared<Rectangle<double>>();
    std::istringstream iss("0 0 2 0 2 2 0 2");
    iss >> *rect;
    
    arr1.Add(rect);
    
    Array<std::shared_ptr<Figure<double>>> arr2(arr1);
    EXPECT_EQ(arr1.Size(), arr2.Size());
    EXPECT_NEAR(arr1[0]->area(), arr2[0]->area(), 1e-5);
}

TEST(FigureArrayTest, ArrayMoveConstructor) {
    Array<std::shared_ptr<Figure<double>>> arr1;
    
    auto rect = std::make_shared<Rectangle<double>>();
    std::istringstream iss("0 0 2 0 2 2 0 2");
    iss >> *rect;
    
    arr1.Add(rect);
    
    Array<std::shared_ptr<Figure<double>>> arr2(std::move(arr1));
    EXPECT_EQ(arr1.Size(), 0);
    EXPECT_EQ(arr2.Size(), 1);
    EXPECT_NEAR(arr2[0]->area(), 4.0, 1e-5);
}

TEST(FigureArrayTest, DifferentTypesInArray) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto rect = std::make_shared<Rectangle<double>>();
    auto rhomb = std::make_shared<Rhomb<double>>();
    auto trap = std::make_shared<Trapeze<double>>();
    
    std::istringstream rect_iss("0 0 2 0 2 2 0 2");
    std::istringstream rhomb_iss("0 1 1 0 0 -1 -1 0");
    std::istringstream trap_iss("0 0 4 0 3 2 1 2");
    
    rect_iss >> *rect;
    rhomb_iss >> *rhomb;
    trap_iss >> *trap;
    
    arr.Add(rect);
    arr.Add(rhomb);
    arr.Add(trap);
    
    EXPECT_EQ(arr.Size(), 3);
    
    double total = 0.0;
    for (size_t i = 0; i < arr.Size(); i++) {
        total += arr[i]->area();
    }
    
    EXPECT_NEAR(total, 4.0 + 2.0 + 6.0, 1e-5);
}

TEST(FigureArrayTest, ArrayForSpecificTypes) {
    Array<std::shared_ptr<Rectangle<double>>> rectArray;
    
    auto rect1 = std::make_shared<Rectangle<double>>();
    auto rect2 = std::make_shared<Rectangle<double>>();
    
    std::istringstream iss1("0 0 2 0 2 2 0 2");
    std::istringstream iss2("1 1 3 1 3 3 1 3");
    
    iss1 >> *rect1;
    iss2 >> *rect2;
    
    rectArray.Add(rect1);
    rectArray.Add(rect2);
    
    EXPECT_EQ(rectArray.Size(), 2);
    EXPECT_NEAR(rectArray[0]->area(), 4.0, 1e-5);
    EXPECT_NEAR(rectArray[1]->area(), 4.0, 1e-5);
}

TEST(FigureTest, CloneMethod) {
    Rectangle<double> rect(0, 0, 2, 0, 2, 2, 0, 2);
    auto cloned = rect.clone();
    
    EXPECT_NEAR(rect.area(), cloned->area(), 1e-5);
    EXPECT_TRUE(rect.operator==(*cloned));
}

TEST(FigureTest, DoubleConversion) {
    Rectangle<double> rect(0, 0, 3, 0, 3, 2, 0, 2);
    double area = static_cast<double>(rect);
    EXPECT_NEAR(area, 6.0, 1e-5);
}
