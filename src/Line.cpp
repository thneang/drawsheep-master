//
// Created by kev on 17/02/17.
//

#include <Line.hpp>
#include <fstream>
using namespace std;
Line::Line(const Point & p1, const Point &p2, QColor c,QPen p):A(p1),B(p2)
{
    this->color = c;
    this->pen = p;
}

Line::~Line(){}

float Line::area() const{
    return 0.0f;
}

float Line::perimeter() const {
    return distance(A,B);
}

float Line::dist_origin() const{
    Point origin;
    return dist_point(origin);
}

float Line::dist_point(Point p) const {
    //calcul du projetté orthogonal
    Point h = projete_orthog(p);
    //h contenu dans le segment AB
    if((A.get_x() < B.get_x() && h.get_x() > A.get_x() && h.get_x() < B.get_x()) || A.get_x() > (B.get_x() && h.get_x() > B.get_x() && h.get_x() < A.get_x())){
        return distance(h,p);
    }
    else{
        //si h n'appartient pas au segment AB, le point le plus proche est donc soit A soit B
        float dist_a = distance(A,p);
        float dist_b = distance(B,p);
        return dist_a < dist_b ? dist_a : dist_b;
    }
}

Point Line::projete_orthog(Point p) const{
    if(A==B){
        return A;
    }
    float xa = A.get_x();
    float ya = A.get_y();
    float xb = B.get_x();
    float yb = B.get_y();
    float xp = p.get_x();
    float yp = p.get_y();
    float a;
    float b;
    if(A.get_x() == B.get_x()){
        return Point(A.get_x(),p.get_y());
    }
    calc_equation_cart(a,b);
//    //si B est sur l'ordonné
//    if(xb == 0){
//        b = yb;
//        //si A est aussi sur l'ordonné
//        if(xa == 0){
//            //renvoyer le point le plus proche entre A et B
//            return distance(p,A) > distance(p,B)?B:A;
//        }
//        else{
//            a = (ya -  b)/ xa;
//        }
//    }
//    else{
//        //si a est sur l'ordonnée
//        if(xa == 0){
//            b = ya;
//
//            //si AB va de gauche a droite
//            if(xa < xb){
//                a = (yb-ya) / xb ;
//            }
//            //si AB va de droite a gauche
//            else{
//                a = (ya-yb) / xb;
//            }
//        }
//        //a et b calculé grace au système yA = a*xA+b et yB = a*xB+b
//        else{
//            b = (yb-ya*xb/xa)/(-xb/xa+1);
//            a = (ya -  b)/ xa;
//        }
//    }
    float c = xp*xb+yp*yb-xp*xa-yp*ya;
    float xh = (-(ya-yb)*b - c) / (xa-xb+(ya-yb)*a);
    float yh = a*xh+b;
    Point h = Point(xh,yh);
    return h;
}

//TODO exception puis catch a chaque utilisation
void Line::calc_equation_cart(float &a, float &b) const{
    if(A.get_x()==B.get_x()){
        //exception
        std::cerr << "exception calc eq cart x=b" << std::endl;
        return;
    }
    a = (B.get_y()-A.get_y()) / (B.get_x()-A.get_x());
    b = A.get_y() - a * A.get_x();
}

void Line::translate(float x, float y){
    Point p(x,y);
    A+=p;
    B+=p;
}

void Line::scale(float s){
    if(s < 0){
        s=-s;
    }
    float a,b;
    if(A.get_x() == B.get_x()){
        B = Point(B.get_x(),A.get_y() + (B.get_y()-A.get_y())*s);
        return;
    }
    calc_equation_cart(a,b);
    float xb1,xb2,yb1,yb2;
    float dist = distance(A,B);
    float new_dist = s * dist;
//    sqrt((xb-xa)² + (yb-ya)²) = newdist;
//    new_dist*new_dist = (xb - A.get_x())*(xb - A.get_x()) + (yb - A.get_y())*(yb - A.get_y());
//    axb + b = yb;
    float apol = a*a+1;
    float bpol = -2*A.get_x() + a*a + 2*a*b - 2*a*A.get_y();
    float cpol = -new_dist*new_dist + A.get_x()*A.get_x() + b*b -2*b*A.get_y() -A.get_y()*A.get_y();
    float delta = bpol * bpol - 4 * apol * cpol;
    if(delta<0){
        return;
    }
    xb1 = fabsf((bpol - sqrtf(delta))/(2*apol));
    yb1 = a*xb1+b;
    xb2 = fabsf((bpol + sqrtf(delta))/(2*apol));
    yb2 = a*xb2+b;
    if(xb1 > A.get_x())
    {
        B = Point(xb1,yb1);
    }
    else{
        B = Point(xb2,yb2);
    }
}


float Line::ref_scale() const {
    return distance(A,B);
}


//TODO version temporaire du scale
void Line::scale_line(float xb,float yb){
    float a,b;
    if(A.get_x() == xb){
        return;
    }
    if(A.get_x() == B.get_x()){
        B = Point(B.get_x(),yb);
    }
    else{
        calc_equation_cart(a,b);
        //si la courbe part trop vers le bas, le scale se fais avec le y de la souris, sinon avec x.
        if(fabsf(a)>2){
            B = Point((yb-b)/a,yb);
        }
        else{
            B = Point(xb,a*xb+b);
        }
    }
}

void Line::rotate(float angle){
    Point mid_point = milieu_segment();
    //rotation depuis l'origine plus facile

    translate(-mid_point.get_x(),-mid_point.get_y());
    //{
    //rotation dans le meme sens peut importe A et B
    B = Point(B.get_x()*cosf(angle)-B.get_y()*sinf(angle),B.get_y()*cosf(angle)+B.get_x()*sinf(angle));
    A = Point(A.get_x()*cosf(angle)-A.get_y()*sinf(angle),A.get_y()*cosf(angle)+A.get_x()*sinf(angle));
    //}
    translate(mid_point.get_x(),mid_point.get_y());
}

Point Line::center() const {
    return milieu_segment();
}

void Line::central_sym(Point c_sym){
    A.central_sym(c_sym);
    B.central_sym(c_sym);
}
void Line::axial_sym(Point p_origin_axis, Point p_extremity_axis){
    A.axial_sym(p_origin_axis,p_extremity_axis);
    B.axial_sym(p_origin_axis,p_extremity_axis);
}

Point Line::milieu_segment() const{
    return Point((A.get_x()+B.get_x())/2,(A.get_y()+B.get_y())/2);
}

int Line::type() const{
    return 6;
}

void Line::setBrush(QColor c) {
    //pas de couleur de fond pour une ligne
}

void Line::setPen(QPen p) {
    pen = p;
}

QGraphicsItem* Line::getItem() const{
    QGraphicsLineItem *l = new QGraphicsLineItem(A.get_x(),A.get_y(),B.get_x(),B.get_y());
    l->setPen(pen);
    return l;
}

void Line::save_to_file(const char *filename) {
    fstream file;

    file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


    // If file does not exist, Create new file
    if (!file ) {
        cout << "Cannot open file, file does not exist. Creating new file..";

        file.open(filename,  fstream::in | fstream::out | fstream::trunc);
    }
    file << type() << "\n";
    file << A.get_x() << " " << A.get_y() << "\n";
    file << B.get_x() << " " << B.get_y() << "\n";

    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    file << r << " " << g << " "<< b << " " << a << "\n";
    file.close();

}