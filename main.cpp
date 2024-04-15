#include <iostream>
#include "matrix.h"
#include <exception>

Matrix getMatrix() {
    std::string filename;
    while (1) {
        std::cout << "Enter name of file with Matrix:" << std::endl;
        std::cin >> filename;
        Matrix m;
        try {
            m = Matrix(filename);
        }
        catch (std::invalid_argument) {
            std::cout << "Invalid file or Matrix" << std::endl;
            continue;
        }
        return m;
    }
}

int main() {
    Matrix m1 = getMatrix();
    while (1) {
        try {
        std::cout << "Enter operation" << std::endl;
        std::cout << "+, -, *, /, ^, det, T, rank, show" << std::endl;
        std::string operation;
        std::cin >> operation;
        if (operation == "+") {
            Matrix m2 = getMatrix();
            std::cout << m1 + m2 << std::endl;
        }
        else if (operation == "-") {
            Matrix m2 = getMatrix();
            std::cout << m1 - m2 << std::endl;
        }
        else if (operation == "*") {
            Matrix m2 = getMatrix();
            std::cout << m1 * m2 << std::endl;
        }
        else if (operation == "/") {
            Matrix m2 = getMatrix();
            std::cout << m1 / m2 << std::endl;
        }
        else if (operation == "T") {
            std::cout << m1.transpose() << std::endl;
            m1.transpose();
        }
        else if (operation == "det") {
            std::cout << m1;
            std::cout << m1.determinant() << std::endl;
        }
        else if (operation == "rank") {
            std::cout << m1.rank() << std::endl;
        }
        else if (operation == "show") {
            std::cout << m1 << std::endl;
        }
        else if (operation == "^") {
            std::cout << "Enter degree" << std::endl;
            int degree;
            std::cin >> degree;
            std::cout << m1.pow(degree) << std::endl;
        }
        else {
            std::cout << "Try again" << std::endl;
            continue;
        }
        std::cout << "Press 1 to choose new first file, 2 to choose new operation, other to quit" << std::endl;
        short action;
        std::cin >> action;
        if (action == 1) {
            m1 = getMatrix();
            continue;
        }
        else if (action == 2) {
            continue;
        }
        else {
            break;
        }
        }
    catch(std::invalid_argument ex) {
        std::cout << ex.what() << std::endl;
    }
    }
    return 0;
}