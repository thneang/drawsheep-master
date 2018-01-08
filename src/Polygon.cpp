//
// Created by kev on 17/02/17.
//

#include <Polygon.hpp>
#include <include/Line.hpp>
#include <fstream>
using namespace std;

Polygon::Polygon(std::vector<Point> v, QColor c ,QPen p)
{
    try{
        if(v.size() < 3){
            std::cout << v.size() << std::endl;
            throw std::string("Error : polygon need 3 point");
        }
        vertices = v;
    }catch(std::string const& chaine){
        std::cerr << chaine << std::endl;
    }
    this->color = c;
    this->pen = p;
}

Polygon::~Polygon(){}

//triangulation pour l'aire
float Polygon::area() const{
    float area = 0;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        area += (vertices[j].get_x() + vertices[i].get_x()) * (vertices[j].get_y() - vertices[i].get_y());
    }
    return std::abs(area/2.0f);
}

//calcul la somme des distances entre tout les points du polygone
float Polygon::perimeter() const{
    float sum_dist = 0;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        sum_dist += distance(vertices[i],vertices[j]);
    }
    return sum_dist;
}

float Polygon::dist_origin() const{
    Point origin;
    float dist_min = 400000;
    for(unsigned long i = 0,j = vertices.size()-1 ; i < vertices.size() ; j=i++){
        Line l(vertices[i],vertices[j]);
        float dist_line = l.dist_point(origin);
        if(dist_line < dist_min){
            dist_min = dist_line;
        }
    }
    return dist_min;
}

void Polygon::translate(float x, float y){
    Point p(x,y);
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i] += p;
    }
}


//TODO scale du polygone à faire
void Polygon::scale(float s){
//    Point center = gravity_center();
//    for(unsigned long i=0 ; i < vertices.size() ; i++){
//        if(center.get_x() < vertices[i].get_x()){
//            if(center.get_y() < vertices[i].get_y()){
//                vertices[i]*=s;
//            }
//            else{
//                float yP = vertices[i].get_y() - (vertices[i].get_y()*s - vertices[i].get_y());
//                vertices[i] = Point(vertices[i].get_x()*s,yP);
//            }
//        }
//        else{
//            if(center.get_y() < vertices[i].get_y()){
//                float xP = vertices[i].get_x() - (vertices[i].get_x()*s - vertices[i].get_x());
//                vertices[i] = Point(xP,vertices[i].get_y()*s);
//            }
//            else{
//                float xP = vertices[i].get_x() - (vertices[i].get_x()*s - vertices[i].get_x());
//                float yP = vertices[i].get_y() - (vertices[i].get_y()*s - vertices[i].get_y());
//                vertices[i] = Point(xP,yP);
//            }
//        }
//    }
}


float Polygon::ref_scale() const {
    float max_distance = 0;
    Point center = gravity_center();
    for(Point p : vertices){
        float dist = distance(p,center);
        max_distance = max_distance < dist ? dist : max_distance;
    }
    return max_distance;
}


void Polygon::rotate(float angle){
    Point center = gravity_center();
    translate(-center.get_x(),-center.get_y());
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i] = Point(vertices[i].get_x()*cosf(angle)-vertices[i].get_y()*sinf(angle),vertices[i].get_y()*cosf(angle)+vertices[i].get_x()*sinf(angle));
    }
    translate(center.get_x(),center.get_y());
}

Point Polygon::center() const {
    return gravity_center();
}

void Polygon::central_sym(Point c_sym){
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i].central_sym(c_sym);
    }
}

void Polygon::axial_sym(Point p_origin_axis, Point p_extremity_axis){
    for(unsigned long i = 0 ; i < vertices.size() ; i++){
        vertices[i].axial_sym(p_origin_axis,p_extremity_axis);
    }
}

 Point Polygon::gravity_center() const{
    float s1 = 0;
    Point s2(0,0);
    for(unsigned long i = 0,j = vertices.size() - 1 ; i < vertices.size() ; j = i++){
        float t = vertices[j].get_x() * vertices[i].get_y() - vertices[j].get_y() * vertices[i].get_x();
        s1+=t;
        s2+=(vertices[j] + vertices[i])*t;
    }
    s1*=3;
    s2*= (1 / s1);
    return s2;
}

int Polygon::type() const{
    return 5;
}

void Polygon::setBrush(QColor c) {
    color = c;
}

void Polygon::setPen(QPen p) {
    pen = p;
}

QGraphicsItem* Polygon::getItem() const{
    QVector<QPointF> v;
    for(Point p : vertices){
        v.push_back(QPointF(p.get_x(),p.get_y()));
    }
    QGraphicsPolygonItem *p = new QGraphicsPolygonItem(v);
    p->setBrush(QBrush(color));
    p->setPen(pen);
    return p;
}

void Polygon::save_to_file(const char *filename) {
    fstream file;

    file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


    // If file does not exist, Create new file
    if (!file ) {
        cout << "Cannot open file, file does not exist. Creating new file..";

        file.open(filename,  fstream::in | fstream::out | fstream::trunc);
    }
    file << type() << "\n";
    file << vertices.size() << "\n";
    for (Point p : vertices) {
        file << p.get_x() << " " << p.get_y() << "\n";
    }
    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    file << r << " " << g << " "<< b << " " << a << "\n";
    file.close();

}