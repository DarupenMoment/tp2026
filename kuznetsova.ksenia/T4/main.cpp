#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>
#include <clocale>
#include <cmath>
<<<<<<< HEAD

=======
>>>>>>> main
#include "Rectangle.h"
#include "Ring.h"
#include "Square.h"
#include "CompositeShape.h"
<<<<<<< HEAD
#include "Shape.h"
#include "Point.h"
=======
#include"Shape.h"
#include"Point.h"
>>>>>>> main

void printShapeInfo(const Shape& shape) {
    Point center = shape.getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << shape.getName() << ", ("
        << center.x << ", " << center.y << "), "
        << shape.getArea();
}

void printComposite(const CompositeShape& composite) {
    std::cout << "[";
    printShapeInfo(composite);
    std::cout << ";\n";

    for (size_t i = 0; i < composite.getSize(); ++i) {
        std::cout << "  ";
        printShapeInfo(*composite.getShape(i));
        if (i != composite.getSize() - 1) {
            std::cout << ",\n";
        }
        else {
            std::cout << "\n";
        }
    }
    std::cout << "]";
}

void testRectangle() {
<<<<<<< HEAD
    std::cout << "\nRECTANGLE TESTING\n";
    Rectangle rect(Point(1, 1), Point(5, 4));
    std::cout << "Rectangle created with corners (1,1) and (5,4)\n";
=======
    std::cout << "\nTЕСТИРОВАНИЕ ПРЯМОУГОЛЬНИКА\n";

    Rectangle rect(Point(1, 1), Point(5, 4));
    std::cout << "Создан прямоугольник с углами (1,1) и (5,4)\n";
>>>>>>> main
    std::cout << "  ";
    printShapeInfo(rect);
    std::cout << "\n";

<<<<<<< HEAD
    std::cout << "Move by (2, -1):\n";
=======
    std::cout << "Перемещение на (2, -1):\n";
>>>>>>> main
    rect.move(2, -1);
    std::cout << "  ";
    printShapeInfo(rect);
    std::cout << "\n";

<<<<<<< HEAD
    std::cout << "Scale x2:\n";
=======
    std::cout << "Масштабирование x2:\n";
>>>>>>> main
    rect.scale(2.0);
    std::cout << "  ";
    printShapeInfo(rect);
    std::cout << "\n";
}

void testRing() {
<<<<<<< HEAD
    std::cout << "\nRING TESTING\n";
    Ring ring(Point(3, 3), 5, 2);
    std::cout << "Ring created with center (3,3), outer radius=5, inner=2\n";
=======
    std::cout << "\nТЕСТИРОВАНИЕ КОЛЬЦА\n";

    Ring ring(Point(3, 3), 5, 2);
    std::cout << "Создано кольцо с центром (3,3), внешний радиус=5, внутренний=2\n";
>>>>>>> main
    std::cout << "  ";
    printShapeInfo(ring);
    std::cout << "\n";

<<<<<<< HEAD
    std::cout << "Move by (-1, 2):\n";
=======
    std::cout << "Перемещение на (-1, 2):\n";
>>>>>>> main
    ring.move(-1, 2);
    std::cout << "  ";
    printShapeInfo(ring);
    std::cout << "\n";

<<<<<<< HEAD
    std::cout << "Scale x0.5:\n";
=======
    std::cout << "Масштабирование x0.5:\n";
>>>>>>> main
    ring.scale(0.5);
    std::cout << "  ";
    printShapeInfo(ring);
    std::cout << "\n";
}

void testSquare() {
<<<<<<< HEAD
    std::cout << "\nSQUARE TESTING\n";
    Square square(Point(0, 0), 4);
    std::cout << "Square created with bottom-left (0,0) and side=4\n";
=======
    std::cout << "\nТЕСТИРОВАНИЕ КВАДРАТА\n";

    Square square(Point(0, 0), 4);
    std::cout << "Создан квадрат с левым нижним углом (0,0) и стороной 4\n";
>>>>>>> main
    std::cout << "  ";
    printShapeInfo(square);
    std::cout << "\n";

<<<<<<< HEAD
    std::cout << "Move by (3, 2):\n";
=======
    std::cout << "Перемещение на (3, 2):\n";
>>>>>>> main
    square.move(3, 2);
    std::cout << "  ";
    printShapeInfo(square);
    std::cout << "\n";

<<<<<<< HEAD
    std::cout << "Scale x1.5:\n";
=======
    std::cout << "Масштабирование x1.5:\n";
>>>>>>> main
    square.scale(1.5);
    std::cout << "  ";
    printShapeInfo(square);
    std::cout << "\n";
}

void testCompositeOperations() {
<<<<<<< HEAD
    std::cout << "\nCOMPOSITE OPERATIONS TESTING\n";

    CompositeShape composite;
=======
    std::cout << "\nТЕСТИРОВАНИЕ ОПЕРАЦИЙ COMPOSITE\n";

    CompositeShape composite;

>>>>>>> main
    composite.addShape(std::make_unique<Square>(Point(1, 1), 2));
    composite.addShape(std::make_unique<Ring>(Point(4, 4), 2, 1));
    composite.addShape(std::make_unique<Rectangle>(Point(2, 2), Point(5, 4)));

<<<<<<< HEAD
    std::cout << "Composite shape created with 3 elements:\n";
    std::cout << "  Number of shapes: " << composite.getSize() << "\n";
    std::cout << "  Total area: " << composite.getArea() << "\n";

    Point center = composite.getCenter();
    std::cout << "  Composite center: (" << center.x << ", " << center.y << ")\n\n";

    std::cout << "Component shapes:\n";
    for (size_t i = 0; i < composite.getSize(); ++i) {
        Shape* shape = composite.getShape(i);
        Point c = shape->getCenter();
        std::cout << "  Shape " << i + 1 << ": " << shape->getName()
            << ", center (" << c.x << ", " << c.y << "), area="
            << shape->getArea() << "\n";
    }

    std::cout << "\nMove composite by (1, -1):\n";
    composite.move(1, -1);
    std::cout << "New shape centers:\n";
    for (size_t i = 0; i < composite.getSize(); ++i) {
        Shape* shape = composite.getShape(i);
        Point c = shape->getCenter();
        std::cout << "  Shape " << i + 1 << ": (" << c.x << ", " << c.y << ")\n";
    }

    std::cout << "\nScale composite x2:\n";
    composite.scale(2.0);
    std::cout << "After scaling:\n";
    for (size_t i = 0; i < composite.getSize(); ++i) {
        Shape* shape = composite.getShape(i);
        Point c = shape->getCenter();
        std::cout << "  Shape " << i + 1 << ": " << shape->getName()
            << ", center (" << c.x << ", " << c.y << "), area="
=======
    std::cout << "Создана составная фигура из 3 элементов:\n";
    std::cout << "  Количество фигур: " << composite.getSize() << "\n";
    std::cout << "  Общая площадь: " << composite.getArea() << "\n";
    Point center = composite.getCenter();
    std::cout << "  Центр композита: (" << center.x << ", " << center.y << ")\n\n";

    std::cout << "Составляющие фигуры:\n";
    for (size_t i = 0; i < composite.getSize(); ++i) {
        Shape* shape = composite.getShape(i);
        Point c = shape->getCenter();
        std::cout << "  Фигура " << i + 1 << ": " << shape->getName()
            << ", центр (" << c.x << ", " << c.y << "), площадь="
            << shape->getArea() << "\n";
    }

    std::cout << "\nПеремещение композита на (1, -1):\n";
    composite.move(1, -1);

    std::cout << "Новые центры фигур:\n";
    for (size_t i = 0; i < composite.getSize(); ++i) {
        Shape* shape = composite.getShape(i);
        Point c = shape->getCenter();
        std::cout << "  Фигура " << i + 1 << ": (" << c.x << ", " << c.y << ")\n";
    }

    std::cout << "\nМасштабирование композита x2:\n";
    composite.scale(2.0);

    std::cout << "После масштабирования:\n";
    for (size_t i = 0; i < composite.getSize(); ++i) {
        Shape* shape = composite.getShape(i);
        Point c = shape->getCenter();
        std::cout << "  Фигура " << i + 1 << ": " << shape->getName()
            << ", центр (" << c.x << ", " << c.y << "), площадь="
>>>>>>> main
            << shape->getArea() << "\n";
    }
}

void testCompositeScaleExample() {
<<<<<<< HEAD
    std::cout << "\nSCALE EXAMPLE TESTING\n";
    std::cout << "Example: Circle (2,2) and Rectangle (8,2)\n\n";

    CompositeShape composite;

    // Circle (using Ring with innerR=0)
    composite.addShape(std::make_unique<Ring>(Point(2, 2), 1, 0));

    // Rectangle with center at (8,2)
    composite.addShape(std::make_unique<Rectangle>(Point(7, 1), Point(9, 3)));

    std::cout << "BEFORE scaling (factor=2):\n";
    std::cout << "  Composite center: ("
=======
    std::cout << "\nТЕСТИРОВАНИЕ МАСШТАБИРОВАНИЯ ИЗ ПРИМЕРА\n";
    std::cout << "Пример: Circle (2,2) и Rectangle (8,2)\n\n";

    CompositeShape composite;

    //круг (используем Ring с innerR=0)
    composite.addShape(std::make_unique<Ring>(Point(2, 2), 1, 0));

    //прямоугольник с центром в (8,2)
    composite.addShape(std::make_unique<Rectangle>(Point(7, 1), Point(9, 3)));

    std::cout << "ДО маштабирования (factor=2):\n";
    std::cout << "  Центр композита: ("
>>>>>>> main
        << composite.getCenter().x << ", "
        << composite.getCenter().y << ")\n";

    for (size_t i = 0; i < composite.getSize(); ++i) {
        Shape* shape = composite.getShape(i);
        Point c = shape->getCenter();
<<<<<<< HEAD
        std::cout << "  Shape " << i + 1 << ": " << shape->getName()
            << ", center (" << c.x << ", " << c.y << ")\n";
    }

    std::cout << "\nExecuting scale(2)...\n";
    composite.scale(2.0);

    std::cout << "\nAFTER scaling:\n";
    std::cout << "  Composite center: ("
=======
        std::cout << "  Фигура " << i + 1 << ": " << shape->getName()
            << ", центр (" << c.x << ", " << c.y << ")\n";
    }

    std::cout << "\nВыполняем scale(2)...\n";
    composite.scale(2.0);

    std::cout << "\nПОСЛЕ маштабирования:\n";
    std::cout << "Центр композита: ("
>>>>>>> main
        << composite.getCenter().x << ", "
        << composite.getCenter().y << ")\n";

    for (size_t i = 0; i < composite.getSize(); ++i) {
        Shape* shape = composite.getShape(i);
        Point c = shape->getCenter();
<<<<<<< HEAD
        std::cout << "  Shape " << i + 1 << ": " << shape->getName()
            << ", center (" << c.x << ", " << c.y << "), area="
            << shape->getArea() << "\n";
    }

    std::cout << "\nExpected result from example:\n";
    std::cout << "Circle should move to (-1,2)\n";
    std::cout << "Rectangle should move to (11,2)\n";
}

void testBoundingBox() {
    std::cout << "\nBOUNDING BOX TESTING\n";

    CompositeShape composite;

    // Add shapes at corners
=======
        std::cout << "Фигура " << i + 1 << ": " << shape->getName()
            << ", центр (" << c.x << ", " << c.y << "), площадь="
            << shape->getArea() << "\n";
    }

    std::cout << "\nОжидаемый результат из примера:\n";
    std::cout << "Круг должен переместиться в (-1,2)\n";
    std::cout << "Прямоугольник должен переместиться в (11,2)\n";
}

void testBoundingBox() {
    std::cout << "\nТЕСТИРОВАНИЕ BOUNDING BOX\n";

    CompositeShape composite;

    // Добавляем фигуры по углам
>>>>>>> main
    composite.addShape(std::make_unique<Square>(Point(0, 0), 1));
    composite.addShape(std::make_unique<Square>(Point(8, 0), 1));
    composite.addShape(std::make_unique<Square>(Point(0, 6), 1));
    composite.addShape(std::make_unique<Square>(Point(8, 6), 1));

<<<<<<< HEAD
    std::cout << "Shapes placed at corners:\n";
    std::cout << "(0,0), (8,0), (0,6), (8,6)\n";

    Point center = composite.getCenter();
    std::cout << "Composite center (based on bounding box of centers): ("
        << center.x << ", " << center.y << ")\n";
    std::cout << "Expected center: (4, 3)\n";
}

void testEdgeCases() {
    std::cout << "\nEDGE CASES TESTING\n";

    std::cout << "Empty CompositeShape:\n";
    CompositeShape empty;
    std::cout << "Size: " << empty.getSize() << "\n";
    std::cout << "Is empty? " << (empty.isEmpty() ? "yes" : "no") << "\n";
    std::cout << "Area: " << empty.getArea() << "\n";

    Point center = empty.getCenter();
    std::cout << "Center: (" << center.x << ", " << center.y << ")\n";

    std::cout << "\nTrying to get element by index:\n";
    try {
        empty.getShape(0);
        std::cout << "ERROR: should throw exception\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    std::cout << "\nComposite with single shape:\n";
    CompositeShape single;
    single.addShape(std::make_unique<Square>(Point(2, 2), 2));

    std::cout << "Size: " << single.getSize() << "\n";
    std::cout << "Area: " << single.getArea() << "\n";

    center = single.getCenter();
    std::cout << "Center: (" << center.x << ", " << center.y << ")\n";

    Shape* shape = single.getShape(0);
    Point c = shape->getCenter();
    std::cout << "Shape center: (" << c.x << ", " << c.y << ")\n";

    std::cout << "\nScale x3:\n";
    single.scale(3.0);

    std::cout << "New area: " << single.getArea() << "\n";
    center = single.getCenter();
    std::cout << "New center: (" << center.x << ", " << center.y << ")\n";

    shape = single.getShape(0);
    c = shape->getCenter();
    std::cout << "New shape center: (" << c.x << ", " << c.y << ")\n";
=======
    std::cout << "Фигуры расположены по углам:\n";
    std::cout << "(0,0), (8,0), (0,6), (8,6)\n";

    Point center = composite.getCenter();
    std::cout << "Центр композита (по bounding box центров): ("
        << center.x << ", " << center.y << ")\n";
    std::cout << "Ожидаемый центр: (4, 3)\n";
>>>>>>> main
}

void testMainTask() {
    std::cout << "\n";
<<<<<<< HEAD
    std::cout << "MAIN TASK (REQUIRED OUTPUT)\n";

    std::vector<std::unique_ptr<Shape>> shapes;

    // Create 5+ shapes
    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3))); // rectangle 4x3
    shapes.push_back(std::make_unique<Ring>(Point(5, 5), 5, 2)); // ring
    shapes.push_back(std::make_unique<Square>(Point(2, 2), 3)); // square 3x3
    shapes.push_back(std::make_unique<Rectangle>(Point(-3, -2), Point(1, 2))); // rectangle 4x4
    shapes.push_back(std::make_unique<Ring>(Point(-2, 4), 3, 1)); // small ring

    // Create composite shape (at least one)
    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Square>(Point(1, 1), 2)); // square 2x2
    composite->addShape(std::make_unique<Ring>(Point(3, 3), 2, 1)); // ring
    composite->addShape(std::make_unique<Rectangle>(Point(2, 0), Point(4, 2))); // rectangle 2x2
    shapes.push_back(std::move(composite));

    std::cout << "BEFORE scaling (x1):\n";
    std::cout << "------------------------\n";

=======
    std::cout << "ОСНОВНОЕ ЗАДАНИЕ (ТРЕБУЕМЫЙ ВЫВОД)\n";

    std::vector<std::unique_ptr<Shape>> shapes;

    //создаем 5+ фигур
    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));//прямоугольник 4x3
    shapes.push_back(std::make_unique<Ring>(Point(5, 5), 5, 2));//кольцо
    shapes.push_back(std::make_unique<Square>(Point(2, 2), 3));//квадрат 3x3
    shapes.push_back(std::make_unique<Rectangle>(Point(-3, -2), Point(1, 2)));//прямоугольник 4x4
    shapes.push_back(std::make_unique<Ring>(Point(-2, 4), 3, 1));//маленькое кольцо

    //создаем составную фигуру (минимум одна)
    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Square>(Point(1, 1), 2));//квадрат 2x2
    composite->addShape(std::make_unique<Ring>(Point(3, 3), 2, 1));//кольцо
    composite->addShape(std::make_unique<Rectangle>(Point(2, 0), Point(4, 2)));//прямоугольник 2x2
    shapes.push_back(std::move(composite));

    std::cout << "ДО маштабирования (x1):\n";
    std::cout << "------------------------\n";
>>>>>>> main
    for (const auto& shape : shapes) {
        if (shape->getName() == "COMPOSITE") {
            printComposite(static_cast<const CompositeShape&>(*shape));
        }
        else {
            std::cout << "  ";
            printShapeInfo(*shape);
        }
        std::cout << "\n";
    }

<<<<<<< HEAD
    std::cout << "\nScaling x2...\n\n";

    // Scale all shapes by factor 2
=======
    std::cout << "\nМасштабирование x2...\n\n";

    //масштабируем все фигуры в 2 раза
>>>>>>> main
    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

<<<<<<< HEAD
    std::cout << "AFTER scaling (x2):\n";
    std::cout << "---------------------------\n";

=======
    std::cout << "ПОСЛЕ маштабирования (x2):\n";
    std::cout << "---------------------------\n";
>>>>>>> main
    for (const auto& shape : shapes) {
        if (shape->getName() == "COMPOSITE") {
            printComposite(static_cast<const CompositeShape&>(*shape));
        }
        else {
            std::cout << "  ";
            printShapeInfo(*shape);
        }
        std::cout << "\n";
    }
}

<<<<<<< HEAD
int main() {
    setlocale(LC_ALL, "C");

    std::cout << "\n";
    std::cout << "SHAPES PROGRAM TESTING\n";

    // Test individual shapes
=======
void testEdgeCases() {
    std::cout << "\nТЕСТИРОВАНИЕ ГРАНИЧНЫХ СЛУЧАЕВ\n";

    std::cout << "Пустой CompositeShape:\n";
    CompositeShape empty;
    std::cout << "Размер: " << empty.getSize() << "\n";
    std::cout << "Пустой? " << (empty.isEmpty() ? "да" : "нет") << "\n";
    std::cout << "Площадь: " << empty.getArea() << "\n";
    Point center = empty.getCenter();
    std::cout << "Центр: (" << center.x << ", " << center.y << ")\n";

    std::cout << "\nПопытка получить элемент по индексу:\n";
    try {
        empty.getShape(0);
        std::cout << "ОШИБКА: должно быть исключение\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Исключение: " << e.what() << "\n";
    }

    std::cout << "\nComposite с одной фигурой:\n";
    CompositeShape single;
    single.addShape(std::make_unique<Square>(Point(2, 2), 2));
    std::cout << "Размер: " << single.getSize() << "\n";
    std::cout << "Площадь: " << single.getArea() << "\n";
    center = single.getCenter();
    std::cout << "Центр: (" << center.x << ", " << center.y << ")\n";

    Shape* shape = single.getShape(0);
    Point c = shape->getCenter();
    std::cout << "Центр фигуры: (" << c.x << ", " << c.y << ")\n";

    std::cout << "\nМасштабирование x3:\n";
    single.scale(3.0);
    std::cout << "Новая площадь: " << single.getArea() << "\n";
    center = single.getCenter();
    std::cout << "Новый центр: (" << center.x << ", " << center.y << ")\n";
    shape = single.getShape(0);
    c = shape->getCenter();
    std::cout << "Новый центр фигуры: (" << c.x << ", " << c.y << ")\n";
}

int main() {
    setlocale(LC_ALL, "RUS");

    std::cout << "\n";
    std::cout << "ТЕСТИРОВАНИЕ ПРОГРАММЫ 'ФИГУРЫ'\n";

    //тестирование отдельных фигур
>>>>>>> main
    testRectangle();
    testRing();
    testSquare();

<<<<<<< HEAD
    // Test CompositeShape
=======
    //тестирование CompositeShape
>>>>>>> main
    testCompositeOperations();
    testCompositeScaleExample();
    testBoundingBox();
    testEdgeCases();

<<<<<<< HEAD
    // Main task
    testMainTask();

    return 0;
}
=======
    //основное задание
    testMainTask();
    return 0;
}
>>>>>>> main
