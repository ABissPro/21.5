#include <iostream>
#include <cmath>

struct Vector {
    double x;
    double y;
};

Vector read_vector() {
    Vector v;
    std::cin >> v.x >> v.y;
    return v;
}

void add() {
    Vector a = read_vector();
    Vector b = read_vector();
    Vector result = { a.x + b.x, a.y + b.y };
    std::cout << result.x << " " << result.y;
}

void subtract() {
    Vector a = read_vector();
    Vector b = read_vector();
    Vector result = { a.x - b.x, a.y - b.y };
    std::cout << result.x << " " << result.y;
}

void scale() {
    Vector v = read_vector();
    double scalar;
    std::cin >> scalar;
    Vector result = { v.x * scalar, v.y * scalar };
    std::cout << result.x << " " << result.y;
}

void length() {
    Vector v = read_vector();
    double len = sqrt(v.x * v.x + v.y * v.y);
    std::cout << len;
}

void normalize() {
    Vector v = read_vector();
    double len = sqrt(v.x * v.x + v.y * v.y);
    Vector result = { v.x / len, v.y / len };
    std::cout << result.x << " " << result.y;
}

int main() {
    std::string command;
    std::cout << "Введите команду (add/subtract/scale/length/normalize)\n";
    std::cin >> command;

    if (command == "add") {
        add();
    }
    else if (command == "subtract") {
        subtract();
    }
    else if (command == "scale") {
        scale();
    }
    else if (command == "length") {
        length();
    }
    else if (command == "normalize") {
        normalize();
    }

    return 0;
}