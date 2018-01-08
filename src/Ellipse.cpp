//
// Created by kev on 17/02/17.
//

#include <Ellipse.hpp>
#include <fstream>
using namespace std;

Ellipse::Ellipse(const Point & cent,float rA,float rB,float angle,QColor c, QPen p):c(cent),rayA(rA),rayB(rB),angle(angle)
{
    this->color = c;
    this->pen = p;
}

Ellipse::~Ellipse(){}

//approximation du perimetre
float Ellipse::perimeter() const{
    return (float)M_PI*sqrtf(2*(rayA*rayA+rayB*rayB));
}

float Ellipse::area() const{
    return (float)M_PI*rayA*rayB;
}

float Ellipse::dist_origin() const{
    Point origin;
    float x0 = c.get_x();
    float y0 = c.get_y();
    float Ac = rayA*rayA;
    float Bc = rayB*rayB;
    //si l'origine est contenu dans l'ellipse
    if((x0*cos(angle)+y0*sin(angle))*(x0*cos(angle)+y0*sin(angle)) / Ac + (-x0*sin(angle)+y0*cos(angle))*(-x0*sin(angle)+y0*cos(angle)) / Bc <= 1){
        return 0;
    }
    //coef directeur de la droite origin-centre
    float a = x0==0 ? 0 : y0 / x0;
    //b = 0 pour la droite ax+b
    //eq ellipse : (x-x0)² / rayA² + (y-y0)² / rayB² = 1
    //eq line : y = a x
    //systeme a deux solution ( les deux intersections de lellipse avec la droite)
    // delta = 8B²x0A²ay0 - 4B²A²y0² - 4A²B⁴ - 4 A²a²B²x0² + 4A⁴a²B²
    // x1 = (2B²x0+2A²ay0 - sqrt(delta) ) / 2B² + 2A²a²  et y1 = ax1
    // x2 = (2B²x0+2A²ay0 + sqrt(delta) ) / 2B² + 2A²a²  et y2 = ax2
    float delta = 8 * Bc * x0 * Ac * a * y0 - 4 * Bc * Ac * y0*y0 + 4 * Ac * Bc*Bc - 4 * Ac * a*a * Bc * x0*x0 + 4 * Ac*Ac * a*a * Bc;
    if(delta < 0){
        std::cerr << "delta < 0 distance origin" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(delta == 0){
        float x = 2*Bc*x0+2*Ac*a*y0 / (2*Bc + 2*Ac*a*a);
        float y = a*x;
        float x_inc = x * cosf(angle) + y * sinf(angle);
        float y_inc = -x * sinf(angle) + y * cosf(angle);
        return distance(Point(x_inc,y_inc),origin);
    }
    float x1_cart = (2*Bc*x0+2*Ac*a*y0 - sqrtf(delta)) / (2*Bc + 2*Ac*a*a);
    float y1_cart = a*x1_cart;
    float x2_cart = (2*Bc*x0+2*Ac*a*y0 + sqrtf(delta)) / (2*Bc + 2*Ac*a*a);
    float y2_cart = a*x2_cart;

    //prise en compte de l'angle
    float x1_inc = x1_cart * cosf(angle) + y1_cart * sinf(angle);
    float y1_inc = -x1_cart * sinf(angle) + y1_cart * cosf(angle);
    float x2_inc = x2_cart * cosf(angle) + y2_cart * sinf(angle);
    float y2_inc = -x2_cart * sinf(angle) + y2_cart * cosf(angle);

    Point intersect1(x1_inc,y1_inc);
    Point intersect2(x2_inc,y2_inc);
    float dist_1 = distance(intersect1,origin);
    float dist_2 = distance(intersect2,origin);

    return dist_1 < dist_2 ? dist_1 : dist_2;

}

void Ellipse::translate(float x, float y){
    c += Point(x,y);
}


void Ellipse::scale(float s){
    rayA *= s;
    rayB *= s;
}

float Ellipse::ref_scale() const {
    return rayA>rayB?rayA:rayB;
}

void Ellipse::rotate(float ang){
    angle += ang;
}

Point Ellipse::center() const {
    return c;
}

void Ellipse::central_sym(Point c_sym){
    c.central_sym(c_sym);
}

void Ellipse::axial_sym(Point p_origin_axis, Point p_extremity_axis){
    c.axial_sym(p_origin_axis,p_extremity_axis);
}

int Ellipse::type() const{
    return 4;
}

void Ellipse::setBrush(QColor c) {
    color = c;
}

void Ellipse::setPen(QPen p) {
    pen = p;
}

QGraphicsItem* Ellipse::getItem() const{
    QGraphicsEllipseItem *e = new QGraphicsEllipseItem(c.get_x()-rayA,c.get_y()-rayB,rayA*2,rayB*2);
    e->setBrush(QBrush(color));
    e->setPen(pen);
    e->setTransformOriginPoint(c.get_x(),c.get_y());
    e->setRotation((angle*180)/M_PI);
    return e;
}

void Ellipse::save_to_file(const char *filename) {
    fstream file;

    file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


    // If file does not exist, Create new file
    if (!file ) {
        cout << "Cannot open file, file does not exist. Creating new file..";

        file.open(filename,  fstream::in | fstream::out | fstream::trunc);
    }
    file << type() << "\n";
    file << c.get_x() << " " << c.get_y() << "\n";
    file << rayA << " " << rayB << "\n";
    file << angle << "\n";
    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    file << r << " " << g << " "<< b << " " << a << "\n";
    file.close();

}


