#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <ostream>

class Matrix
{
public:
    Matrix() = default;
    Matrix(std::vector<std::vector<int>> vec);
    Matrix(std::vector<std::string> vec);

    std::pair<int, int> size();
    void reset();
    void resetToE();
    void transpose();
    Matrix pow(int degree);
    void copy(Matrix& m);

    friend std::ostream& operator<<(std::ostream& out, Matrix m);
    Matrix& operator+(Matrix& m);
    Matrix& operator*(Matrix& m);

    std::vector<int>& operator[](int index);


private:
    std::vector<std::vector<int>> table;

};

#endif // MATRIX_H
