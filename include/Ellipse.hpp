//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_ELLIPSE_HPP
#define DRAWSHEEP_ELLIPSE_HPP
#include<Point.hpp>
#include <My_Shape.hpp>
#include <cmath>


class Ellipse : public My_Shape{
private:
    Point c;
    float rayA;
    float rayB;
    float angle = 0.0f;
public:
    Ellipse(const Point & cent,float rayA, float rayB,float angle=0,QColor c = Qt::transparent,QPen p = QPen());
    virtual ~Ellipse();
    virtual int type() const;
    virtual void setBrush(QColor c);
    virtual void setPen(QPen p);
    virtual QGraphicsItem* getItem() const;
    virtual float area() const;
    virtual float perimeter() const;
    virtual float dist_origin() const;
    virtual void translate(float x, float y);
    virtual void rotate(float angle);
    virtual void scale(float s);
    virtual float ref_scale() const;
    virtual Point center() const;
    virtual void central_sym(Point c_sym);
    virtual void axial_sym(Point p_origin_axis, Point p_extremity_axis);

    virtual void save_to_file(const char *filename);
};

#endif //DRAWSHEEP_ELLIPSE_HPP
