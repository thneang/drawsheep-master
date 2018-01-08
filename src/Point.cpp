//
// Created by kev on 17/02/17.
//

#include <Point.hpp>
#include <include/Line.hpp>

Point::Point(float a, float b):x(a),y(b)
{
}

float Point::get_x() const {
    return x;
}

float Point::get_y() const {
    return y;
}


bool Point::operator== (const Point & p) const{
    return p.x == x && p.y == y;
}

Point& Point::operator+= (const Point & p) {
    x+=p.x;
    y+=p.y;
    return *this;
}

Point& Point::operator*= (float s) {
    x*=s;
    y*=s;
    return *this;
}

Point Point::operator+ (const Point& b) const{
    return Point(x+b.x,y+b.y);
}


Point Point::operator* (float t) const{
    return Point(t*x,t*y);
}


Point& Point::central_sym(Point c_sym){
    x = 2 * c_sym.x - x;
    y = 2 * c_sym.y - y;
    return *this;
}

Point& Point::axial_sym(Point p_origin_axis, Point p_extremity_axis){
    Line l(p_origin_axis,p_extremity_axis);
    Point transpose = l.projete_orthog(*this);
    return central_sym(transpose);
}

std::ostream & operator<< (std::ostream & os, const Point & p)
{
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

float distance(Point p1, Point p2){
    float dist_x = 0;
    float dist_y = 0;
    if(p1.x < p2.x){
        if(p1.y < p2.y){
            dist_x = p2.x - p1.x;
            dist_y = p2.y - p1.y;
        }
        else{
            dist_x = p2.x - p1.x;
            dist_y = p1.y - p2.y;
        }
    }
    else{
        if(p1.y < p2.y){
            dist_x = p1.x - p2.x;
            dist_y = p2.y - p1.y;
        }
        else{
            dist_x = p1.x - p2.x;
            dist_y = p1.y - p2.y;
        }
    }
    return sqrtf(dist_x*dist_x + dist_y * dist_y);
}