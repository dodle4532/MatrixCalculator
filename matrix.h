#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <ostream>

class Matrix
{
public:
    Matrix() = default;
    Matrix(std::vector<std::vector<float>> vec);
    Matrix(std::vector<std::string> vec);

    std::pair<float, float> size();
    void deleteRow(float n);
    void deleteColumn(float n);
    Matrix& toNull(float n);
    Matrix& toE(float n);
    void transpose();
    float determinant();
    Matrix pow(float degree);
    void copy(Matrix& m);

    friend std::ostream& operator<<(std::ostream& out, Matrix m);
    Matrix& operator+(Matrix& m);
    Matrix& operator*(Matrix& m);

    std::vector<float>& operator[](float index);


private:
    std::vector<std::vector<float>> table;
    
    float determinant(std::vector<std::vector<float>> m);
};

#endif // MATRIX_H
