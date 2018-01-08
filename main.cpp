#include <iostream>
#include <My_Shape.hpp>
#include <Ellipse.hpp>
#include <Polygon.hpp>
#include <Line.hpp>
#include <Window.hpp>

// TODO Faire des tests unitaires, rapporte des points dans le rapport

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Window *window = new Window();
    window->show();

    Point p(3,3);

    Line l(Point(0,2),Point(2,0));

    float rx = 2;
    float ry = 2;
    Ellipse e(p,rx,ry);

    std::vector<Point> polyPoint;
    polyPoint.push_back(Point(12,3));
    polyPoint.push_back(Point(5,8));
    polyPoint.push_back(Point(0,2));
    polyPoint.push_back(Point(2,0));
    Polygon pol(polyPoint);

//    pol.rotate(5);
//    Point o;
//    p.central_sym(o);
//    pol.central_sym(o);
//    l.central_sym(o);
//    e.central_sym(o);

    Point o1(10,10);
    Point o2(11,9);
    p.axial_sym(o1,o2);
//    std::cout << pol.gravity_center() << std::endl;
    pol.axial_sym(o1,o2);
    l.axial_sym(o1,o2);
    e.axial_sym(o1,o2);
//    std::cout << p << std::endl;
//    std::cout << pol.gravity_center() << std::endl;
//    std::cout << l.milieu_segment() << std::endl;

    return app.exec();
//    return 0;
}