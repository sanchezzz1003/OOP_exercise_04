/*
Написать программу по вычислению центра и площади квадрата, прямоугольника или треугольника, которые
задает пользователь, и по выводу их координат. Использовать вместо наследования шаблоны.
Сделать функции, которые принимают на вход кортежи.

Комков Александр
М8О-201Б-18
*/
// Hex double class 0 0 1 0 1.5 0.866025
#include "Figure.h"

#define M_PI            3.14159265358979323846

template <class T>
void Triangle_read_cords(std::pair<T, T> &A, std::pair<T, T> &B, std::pair<T, T> &C){
    std::cout << "cords point A: ";
    std::cin >> A;
    std::cout << "cords point B: ";
    std::cin >> B;
    std::cout << "cords point C: ";
    std::cin >> C;
}

template <class T>
void Square_read_cords(std::pair<T, T> &A, std::pair<T, T> &C){
    std::cout << "cords lower left point A: ";
    std::cin >> A;
    std::cout << "cords top right point C: ";
    std::cin >> C;
}

template <class T>
void Hexagon_read_cords(std::pair<T, T> &A, std::pair<T, T> &B, std::pair<T, T> &C, std::pair<T, T> &D, std::pair<T, T> &E, std::pair<T, T> &F){
    std::cout << "cords point A: ";
    std::cin >> A;
    std::cout << "cords point B: ";
    std::cin >> B;
    std::cout << "cords point C: ";
    std::cin >> C;
    std::pair<T, T> focus;
    focus.first = B.first;
    focus.second = A.second;
    D.first = C.first + dist(A, B)*cos(0.666666*M_PI+acos(dist(A, focus)/dist(A, B)));
    D.second = C.second + dist(A, B)*sin(0.666666*M_PI+acos(dist(A, focus)/dist(A, B)));
    E.first = D.first + dist(A, B)*cos(M_PI+acos(dist(A, focus)/dist(A, B)));
    E.second = D.second + dist(A, B)*sin(M_PI+acos(dist(A, focus)/dist(A, B)));
    F.first = A.first + dist(A, B)*cos(0.666666*M_PI+acos(dist(A, focus)/dist(A, B)));
    F.second = A.second + dist(A, B)*sin(0.666666*M_PI+acos(dist(A, focus)/dist(A, B)));
}

template <class T>
void actions(const T &figure) {
            Coord_print(figure);
            std::cout << "Figure area:" << calc_area(figure) << std::endl;
            std::cout << "The coordinates of the center of the figure: "
            << calc_center(figure) << std::endl;
}

int main(){
    using int_pair = std::pair<int, int>;
    using double_pair = std::pair<double, double>;

    std::tuple<int_pair, int_pair, int_pair> tuple_intTri;
    std::tuple<double_pair, double_pair, double_pair> tuple_doubleTri;
    std::tuple<int_pair, int_pair> tuple_intSqu;
    std::tuple<double_pair, double_pair> tuple_doubleSqu;
    std::tuple<int_pair, int_pair, int_pair, int_pair, int_pair, int_pair> tuple_intHex;
    std::tuple<double_pair, double_pair, double_pair, double_pair, double_pair, double_pair> tuple_doubleHex;

    int id = 0;
    std::string option = "Menu";

    while(option != "Ex") {
        if (option == "Tri") {
            id++;
            std::cout << "Choose data type: int or double" << std::endl;
            std::cin >> option;
            if (option == "int") {
                std::cout << "choose the type of shape input: through the [class] or [tuple]" << std::endl;
                std::cin >> option;
                if (option == "class") {
                    std::pair<int, int> A, B, C;
                    Triangle_read_cords(A, B, C);
                    Triangle<int> tri_int(A, B, C);
                    std::cout << id << " Figure: Triangle integer\n";
                    actions(tri_int);
                } else if (option == "tuple") {
                    std::pair<int, int> A, B, C;
                    Triangle_read_cords(A, B, C);
                    std::get<0>(tuple_intTri) = A;
                    std::get<1>(tuple_intTri) = B;
                    std::get<2>(tuple_intTri) = C;
                    std::cout << id << " Figure: Triangle integer\n";
                    Coord_print(tuple_intTri);
                    std::cout << "Area:" << calc_area(tuple_intTri) << std::endl;
                    std::cout << "Center:" << calc_center(tuple_intTri) << std::endl;
                }
            } else if (option == "double") {
                std::cout << "choose the type of shape input: through the [class] or [tuple]" << std::endl;
                std::cin >> option;
                if (option == "class") {
                    std::pair<double, double> A, B, C;
                    Triangle_read_cords(A, B, C);
                    Triangle<double> tri_double(A, B, C);
                    std::cout << id << " Figure: Triangle double\n";
                    actions(tri_double);
                } else if (option == "tuple") {
                    std::pair<double, double> A, B, C;
                    Triangle_read_cords(A, B, C);
                    std::get<0>(tuple_doubleTri) = A;
                    std::get<1>(tuple_doubleTri) = B;
                    std::get<2>(tuple_doubleTri) = C;
                    std::cout << id << " Figure: Triangle double\n";
                    Coord_print(tuple_doubleTri);
                    std::cout << "Area:" << calc_area(tuple_doubleTri) << std::endl;
                    std::cout << "Center:" << calc_center(tuple_doubleTri) << std::endl;
                }
            }
        } else if (option == "Squ") {
            id++;
            std::cout << "Choose data type: int or double" << std::endl;
            std::cin >> option;
            if (option == "int") {
                std::cout << "choose the type of shape input: through the [class] or [tuple]" << std::endl;
                std::cin >> option;
                if (option == "class") {
                    std::pair<int, int> A, C;
                    Square_read_cords(A, C);
                    Square<int> squ_int(A, C);
                    std::cout << id << " Figure: Square integer\n";
                    actions(squ_int);
                } else if (option == "tuple") {
                    std::pair<int, int> A, C;
                    Square_read_cords(A, C);
                    std::get<0>(tuple_intSqu) = A;
                    std::get<1>(tuple_intSqu) = C;
                    std::cout << id << " Figure: Square integer\n";
                    Coord_print(tuple_intSqu);
                    std::cout << "Area:" << calc_area(tuple_intSqu) << std::endl;
                    std::cout << "Center:" << calc_center(tuple_intSqu) << std::endl;
                }
            } else if (option == "double") {
                std::cout << "choose the type of shape input: through the [class] or [tuple]" << std::endl;
                std::cin >> option;
                if (option == "class") {
                    std::pair<double, double> A, C;
                    Square_read_cords(A, C);
                    Square<double> squ_double(A, C);
                    std::cout << id << " Figure: Square double\n";
                    actions(squ_double);
                } else if (option == "tuple") {
                    std::pair<double, double> A, C;
                    Square_read_cords(A, C);
                    std::get<0>(tuple_doubleSqu) = A;
                    std::get<1>(tuple_doubleSqu) = C;
                    std::cout << id << " Figure: Square double\n";
                    Coord_print(tuple_doubleSqu);
                    std::cout << "Area:" << calc_area(tuple_doubleSqu) << std::endl;
                    std::cout << "Center:" <<calc_center(tuple_doubleSqu) << std::endl;
                }
            }
        } else if (option == "Hex") {
            id++;
            std::cout << "Choose data type: int or double" << std::endl;
            std::cin >> option;
            if (option == "int") {
                std::cout << "choose the type of shape input: through the [class] or [tuple]" << std::endl;
                std::cin >> option;
                if (option == "class") {
                    std::pair<int, int> A, B, C, D, E, F;
                    Hexagon_read_cords(A, B, C, D, E, F);
                    Hexagon<int> hex_int(A, B, C, D, E, F);
                    std::cout << id << " Figure: Hexagon integer\n";
                    actions(hex_int);
                } else if (option == "tuple") {
                    std::pair<int, int> A, B, C, D, E, F;
                    Hexagon_read_cords(A, B, C, D, E, F);
                    std::get<0>(tuple_intHex) = A;
                    std::get<1>(tuple_intHex) = B;
                    std::get<2>(tuple_intHex) = C;
                    std::get<3>(tuple_intHex) = D;
                    std::get<4>(tuple_intHex) = E;
                    std::get<5>(tuple_intHex) = F;
                    std::cout << id << " Figure: Hexagon integer\n";
                    Coord_print(tuple_intHex);
                    std::cout << "Area:" << calc_area(tuple_intHex) << std::endl;
                    std::cout << "Center:" <<calc_center(tuple_intHex) << std::endl;
                }
            } else if (option == "double") {
                std::cout << "choose the type of shape input: through the [class] or [tuple]" << std::endl;
                std::cin >> option;
                if (option == "class") {
                    std::pair<double, double> A, B, C, D, E, F;
                    Hexagon_read_cords(A, B, C, D, E, F);
                    Hexagon<double> hex_double(A, B, C, D, E, F);
                    std::cout << id << " Figure: Hexagon double\n";
                    actions(hex_double);
                } else if (option == "tuple") {
                    std::pair<double, double> A, B, C, D, E, F;
                    Hexagon_read_cords(A, B, C, D, E, F);
                    std::get<0>(tuple_doubleHex) = A;
                    std::get<1>(tuple_doubleHex) = B;
                    std::get<2>(tuple_doubleHex) = C;
                    std::get<3>(tuple_doubleHex) = D;
                    std::get<4>(tuple_doubleHex) = E;
                    std::get<5>(tuple_doubleHex) = F;
                    std::cout << id << " Figure: Hexagon double\n";
                    Coord_print(tuple_doubleSqu);
                    std::cout << "Area:" << calc_area(tuple_doubleHex) << std::endl;
                    std::cout << "Center:" << calc_center(tuple_doubleHex) << std::endl;
                }
            }
        } else if (option == "Menu") {
            std::cout << "Enter a word for action:" << std::endl;
            std::cout << "1) Create Triangle[Tri]" <<
                      std::endl << "2) Create Square [Squ]" <<
                      std::endl << "3) Create Hexagon [Hex]" <<
                      std::endl << "4) And then enter word to select data type: [int] or [double]" <<
                      std::endl << "5) Next choose where to write a figure: [tuple] or [class] object" <<
                      std::endl << "6) Demonstration of a tuple with figures[tuple_work]" <<
                      std::endl << "7) Print Menu[Menu]" <<
                      std::endl << "8) Exit[Ex]" << std::endl;
        } else if(option == "tuple_work") {
            std::cout << "\nExample with tuple usage:\n\n";
            std::tuple<double_pair, double_pair> exm_tup_squ({1.1, 1.1}, {3.3,3.3});
            Coord_print(exm_tup_squ);
            std::cout << "Area: "<< calc_area(exm_tup_squ) << std::endl;
            std::cout << "<<Center of the figure:" << calc_center(exm_tup_squ) << std::endl;
        }else {
            std::cout << "You did not select an action or you were mistaken in entering the name of the action" << std::endl;
        }
        std::cin >> option;
    }
    return 0;
}