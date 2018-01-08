//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_SHAPE_HPP
#define DRAWSHEEP_SHAPE_HPP
#include<iostream>
#include<Point.hpp>
#include<QGraphicsItem>
#include<QBrush>
#include<QPen>

class My_Shape {
protected:
    QColor color = Qt::transparent;
    QPen pen;
public:
    virtual int type() const = 0;
    virtual void setBrush(QColor c) = 0;
    virtual void setPen(QPen p) = 0;
    virtual QGraphicsItem* getItem() const = 0;
    virtual float area() const = 0;
    virtual float perimeter() const = 0;
    virtual float dist_origin() const = 0;
    virtual ~My_Shape(){};
    virtual void translate(float, float) = 0;
    virtual void rotate(float) = 0;
    virtual void scale(float) = 0;
    virtual float ref_scale() const = 0;
    virtual Point center() const = 0;
    virtual void central_sym(Point c_sym) = 0;
    virtual void axial_sym(Point p_origin_axis, Point p_extremity_axis) = 0;

    virtual void save_to_file(const char *filename) = 0;
};

#endif //DRAWSHEEP_SHAPE_HPP
