//
// Created by kev on 17/02/17.
//

#ifndef DRAWSHEEP_POLYGON_HPP
#define DRAWSHEEP_POLYGON_HPP
#include <My_Shape.hpp>
#include <vector>


class Polygon : public My_Shape {
private:
    std::vector<Point> vertices;
public:
    Polygon(std::vector<Point> v, QColor c = Qt::transparent,QPen p = QPen());
    virtual ~Polygon();
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

    Point gravity_center() const;
    virtual void save_to_file(const char *filename);

};


#endif //DRAWSHEEP_POLYGON_HPP
