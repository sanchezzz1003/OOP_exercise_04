#ifndef __FIGURES_H__
#define __FIGURES_H__
#include <type_traits> // for enable_if
#include <string>
#include <tuple>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>

template <class T>
std::pair<T, T> operator-(const std::pair<T, T> &p1, const std::pair<T, T> &p2){
    return {p1.first-p2.first, p1.second-p2.second};
}

template <class T>
std::ostream& operator<<(std::ostream &o, const std::pair<T, T> &p){
    if (p.first - floor(p.first) <= 0.00001 && p.first - floor(p.first) > 0)
        o << std::fixed << std::setprecision(3) << "<" << p.first << ", ";
    else
        o << std::defaultfloat << "<" << p.first << ", ";
    if (p.second - floor(p.second) <= 0.00001 && p.second - floor(p.second) > 0)
        o << std::fixed << std::setprecision(3) << p.second << "> " << std::defaultfloat;
    else
        o << std::defaultfloat << p.second << "> ";
    return o;
}


template <class T>
bool operator==(const std::pair<T, T> &a, const std::pair<T, T> &b){
    return (a.first == b.first) && (a.second == b.second);
}


bool isNumber(const std::string& s){
    return !s.empty() && s.find_first_not_of("-.0123456789") == std::string::npos; }

template <class T>
std::istream& operator>>(std::istream &is, std::pair<T, T> &p){
    std::string checker;

    is >> checker;
    if(isNumber(checker) == false){
        throw std::overflow_error("Is not a number");
    }
    p.first = static_cast<T>(std::stod(checker));

    is >> checker;
    if(isNumber(checker) == false){
        throw std::overflow_error("Is not a number");
    }
    p.second = static_cast<T>(std::stod(checker));

    return is;
}

template <class T>
bool collinear(const std::pair<T, T> &a, const std::pair<T, T> &b, const std::pair<T, T> &c, const std::pair<T, T> &d){
    return (b.second-a.second)*(d.first-c.first) - (d.second-c.second)*(b.first-a.first) <= 1e-9;
}

template <int>
bool collinear(std::pair<int, int> &a, std::pair<int, int> &b, std::pair<int, int> &c, const std::pair<int, int> &d){
    return (b.second-a.second)*(d.first-c.first) == (d.second-c.second)*(b.first-a.first);
}

template <class T>
bool perpendic(const std::pair<T, T> &a, const std::pair<T, T> &b, const std::pair<T, T> &d){
    using vect = std::pair<T, T>;
    vect AB = b-a;
    vect AD = d-a;
    T dotProduct = AB.first*AD.first + AB.second*AD.second;
    if(dotProduct <= 1e-9 && dotProduct >= -1e-9) return true;
    else return false;
}

template <class T>
double dist(const std::pair<T,T> &a, const std::pair<T,T> &b){
    return sqrt( ((b.first - a.first) * (b.first - a.first)) + ((b.second - a.second) * (b.second - a.second)));
}


template <class T>
class Triangle{
public:
    using type = T;
    using point = std::pair<T, T>;
    point A, B, C;

    Triangle() = default;
    Triangle(point &a, point &b, point &c){
        /*double AB = dist(a, b); //1
        double AC = dist(a, c); //3
        double BC = dist(b, c); //2
        (AB + AC) > BC ) && ((AB + BC) > AC) && ((BC + AC) > AB);*/
         //(a.first-c.first)*(b.second-c.second) == (a.second-c.second)*(b.first-c.first)
        if ( ((a.first-c.first)*(b.second-c.second)) != ((a.second-c.second)*(b.first-c.first)) ){
            A = a;
            B = b;
            C = c;
        }else{
            throw std::overflow_error("The given coordinates of the triangle lie on one straight line");
        }
    }
};


//Шаблон, который возвращает истинное значение value, если контейнер хранит фигуру hexagon
template <class T>
struct is_Triangle{
    static const bool value = false;
};

template <class T>
struct is_Triangle<Triangle<T>>{
    static const bool value = true;
};


template <class T>
using Triangle_center = typename std::enable_if<is_Triangle<T>::value, std::pair<typename T::type, typename T::type> >::type;


template <class T>
using Triangle_cords = typename std::enable_if<is_Triangle<T>::value, void >::type;


template <class T>
using Triangle_area = typename std::enable_if<is_Triangle<T>::value, typename T::type >::type;



template <class T>
Triangle_center<T> calc_center(const T &tri){
    typename T::type x_center, y_center;
    x_center = tri.A.first + tri.B.first + tri.C.first;
    y_center = tri.A.second + tri.B.second + tri.C.second;
    return {x_center, y_center};
}


template <class T>
std::pair<T, T> calc_center(const std::tuple< std::pair<T, T>, std::pair<T, T>, std::pair<T, T> > &tp){
    std::pair<T,T> a, b, c;
    a = std::get<0>(tp);
    b = std::get<1>(tp);
    c = std::get<2>(tp);
    Triangle<T> tri(a, b, c);
    return calc_center(tri);
}

template <class T>
Triangle_cords<T> Coord_print(const T &tri){
    std::cout << std::fixed << std::setprecision(3) << "Cords of Triangle: " << tri.A << ", " << tri.B << ", " << tri.C << std::endl;
}

template <class T>
void Coord_print(const std::tuple< std::pair<T, T>, std::pair<T, T>, std::pair<T, T> > &tp){
    std::pair<T,T> a, b, c;
    a = std::get<0>(tp);
    b = std::get<1>(tp);
    c = std::get<2>(tp);
    Triangle<T> tri(a, b, c);
    std::cout << "Tuple. ";
    Coord_print(tri);
}

template <class T>
Triangle_area<T> calc_area(const T &tri) {
    auto AB = dist(tri.A, tri.B);
    auto AC = dist(tri.A, tri.C);
    auto BC = dist(tri.B, tri.C);
    auto p = (AB + AC + BC) / 2;
    auto S = sqrt(p * (p - AB) * (p - AC) * (p - BC));
    return S;
}

template <class T>
T calc_area(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &tp){
    std::pair<T,T> a, b, c;
    a = std::get<0>(tp);
    b = std::get<1>(tp);
    c = std::get<2>(tp);
    Triangle<T> tri(a, b, c);
    return calc_area(tri);
}

//for square
template <class T>
class Square{
public:
    using type = T; // вот это нужно когда мы проверяем в enable if, если тот тип фигуры то даем тип данной фигуры что то такое
    using point = std::pair<T, T>;
    point A, B, C, D;

    Square() = default;
    Square(point &a, point &c){ // по ссылке обращение
        point d(a.first, c.second);
        point b(c.first, a.second);
        auto AB = dist(a,b);
        auto AD = dist(a,d);
        if(a == c || AB != AD){
            throw std::overflow_error("Entered the coordinates of the vertices do not belong to the square.");
        }else{
            if(a.first > b.first){
                C = a; A = c;
                B = d; D = b;
            }else{
                A = a; C = c;
                D = d; B = b;
            }
        }
    }
};

template <class T>
struct is_Square{
    static const bool value = false;
};

template <class T>
struct is_Square<Square<T>>{
    static const bool value = true;
};


template <class T>
using Square_center = typename std::enable_if<is_Square<T>::value, std::pair<typename T::type, typename T::type> >::type;


template <class T>
using Square_cords = typename std::enable_if<is_Square<T>::value, void >::type;


template <class T>
using Square_area = typename std::enable_if<is_Square<T>::value, typename T::type >::type;

template <class T>
Square_center<T> calc_center(const T &squ){
    typename T::type x_center, y_center;
    x_center = (squ.A.first + squ.C.first)/2;
    y_center = (squ.A.second + squ.C.second)/2;
    return {x_center, y_center};
}


template <class T>
std::pair<T, T> calc_center(const std::tuple< std::pair<T, T>, std::pair<T, T> > &tp){
    std::pair<T,T> a, c;
    a = std::get<0>(tp);
    c = std::get<1>(tp);
    Square<T> squ(a, c);
    return calc_center(squ);
}

template <class T>
Square_cords<T> Coord_print(const T &squ){
    std::cout << "Cords of Square: " << squ.A << ", " << squ.B << ", " << squ.C << ", " << squ.D << std::endl;
}


template <class T>
void Coord_print(const std::tuple< std::pair<T, T>, std::pair<T, T> > &tp){
    std::pair<T,T> a, c;
    a = std::get<0>(tp);
    c = std::get<1>(tp);
    Square<T> squ(a, c);
    std::cout << "Tuple. ";
    Coord_print(squ);
}

template <class T>
Square_area<T> calc_area(const T &squ) {
    auto d = dist(squ.A, squ.C);
    return (d*d)/2;
}

template <class T>
T calc_area(const std::tuple<std::pair<T, T>, std::pair<T, T> > &tp){
    std::pair<T,T> a, c;
    a = std::get<0>(tp);
    c = std::get<1>(tp);
    Square<T> squ(a, c);
    return calc_area(squ);
}


template <class T>
class Hexagon{
public:
    using type = T;
    using point = std::pair<T, T>;
    point A, B, C, D, E, F;

    Hexagon() = default;
    Hexagon(point &a, point &b, point &c, point &d, point &e, point &f){
        auto AB = dist(a,b);
        auto AF = dist(a,f);
        if(a == b || a == c || b == c || a == d || a == e || a == f || b == d || b == e || b == f || c == d || c == e || c == f || d == e || d == f || e == f){
            throw std::overflow_error("The entered coordinates of the vertices do not belong to the hexagon.");
        }else{
            A = a;
            B = b;
            C = c;
            D = d;
            E = e;
            F = f;
        }
    }
};


template <class T>
struct is_Hexagon{
    static const bool value = false;
};

template <class T>
struct is_Hexagon<Hexagon<T>>{
    static const bool value = true;
};


template <class T>
using Hexagon_center = typename std::enable_if<is_Hexagon<T>::value, std::pair<typename T::type, typename T::type> >::type;


template <class T>
using Hexagon_cords = typename std::enable_if<is_Hexagon<T>::value, void >::type;


template <class T>
using Hexagon_area = typename std::enable_if<is_Hexagon<T>::value, typename T::type >::type;



template <class T>
Hexagon_center<T> calc_center(const T &hex){
    typename T::type Ox, Oy;
    Ox = (hex.A.first + hex.B.first + hex.C.first + hex.D.first + hex.E.first + hex.F.first)/6;
    Oy = (hex.A.second + hex.B.second + hex.C.second + hex.D.second + hex.E.second + hex.F.second)/6;
    return {Ox, Oy};
}


template <class T>
std::pair<T, T> calc_center(const std::tuple< std::pair<T, T>, std::pair<T, T> , std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &tp){
    std::pair<T,T> a, b, c, d, e, f;
    a = std::get<0>(tp);
    b = std::get<1>(tp);
    c = std::get<2>(tp);
    d = std::get<3>(tp);
    e = std::get<4>(tp);
    f = std::get<5>(tp);
    Hexagon<T> hex(a, b, c, d, e, f);
    return calc_center(hex);
}

template <class T>
Hexagon_cords<T> Coord_print(const T &hex){
    std::cout << "Cords of hextangle: " << hex.A << ", " << hex.B << ", " << hex.C << ", " << hex.D << ", " << hex.E << ", " << hex.F << std::endl;
}


template <class T>
void Coord_print(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T> > &tp){
    std::pair<T,T> a, b, c, d, e, f;
    a = std::get<0>(tp);
    b = std::get<1>(tp);
    c = std::get<2>(tp);
    d = std::get<3>(tp);
    e = std::get<4>(tp);
    f = std::get<5>(tp);
    Hexagon<T> hex(a, b, c, d, e, f);
    std::cout << "Tuple. ";
    Coord_print(hex);
}

template <class T>
Hexagon_area<T> calc_area(const T &hex) {
    auto AB = dist(hex.A, hex.B);
    return AB*AB*3*sqrt(3)/2;
}

template <class T>
T calc_area(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T> > &tp){
    std::pair<T,T> a, b, c, d, e, f;
    a = std::get<0>(tp);
    b = std::get<1>(tp);
    c = std::get<2>(tp);
    d = std::get<3>(tp);
    e = std::get<4>(tp);
    f = std::get<5>(tp);
    Hexagon<T> hex(a, b, c, d, e, f);
    return calc_area(hex);
}

#endif