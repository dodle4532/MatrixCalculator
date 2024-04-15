#include "matrix.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>

Matrix::Matrix(std::vector<std::vector<float>> vec) {
    table = vec;
    if (vec.size() > 1) {
        for (int i = 1; i < table.size(); ++i) {
            if (table[i].size() != table[0].size()) {
                throw std::invalid_argument("Invalid vector(different number of columns)"); 
            }
        }
    }
}

Matrix::Matrix(std::vector<std::string> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        table.resize(table.size() + 1);
        std::string str;
        for (auto& ch : vec[i]) {
            if (ch == ' ') {
                try {
                    table[i].push_back(std::stoi(str));
                }
                catch (...) {
                    throw std::invalid_argument("Incorrect data");
                }
                str = "";
            }
            str += ch;
        }
        try {
            table[i].push_back(std::stoi(str));
        }
        catch (...) {
            throw std::invalid_argument("Incorrect data");
        }
    }
    if (table.size() > 1) {
        for (int i = 1; i < table.size(); ++i) {
            if (table[i].size() != table[0].size()) {
                throw std::invalid_argument("Invalid vector(different number of columns)"); 
            }
        }
    }
}

Matrix::Matrix(std::string filename) {
    std::fstream fd(filename);
    if (!(fd.is_open())) {
        throw std::invalid_argument("File isn't open");
    }
    std::vector<std::string> v;
    std::string str;
    while (!(fd.eof())) {
        std::getline(fd, str);
        v.push_back(str);
    }
    Matrix m(v);
    table = m.table;
    if (table.size() > 1) {
        for (int i = 1; i < table.size(); ++i) {
            if (table[i].size() != table[0].size()) {
                throw std::invalid_argument("Invalid vector(different number of columns)"); 
            }
        }
    }
}

std::pair<float, float> Matrix::size() {
    return std::make_pair<float, float> (table.size(), table[0].size());
}

void Matrix::deleteRow(float n) {
    table.erase(table.begin() + n);
}
void Matrix::deleteColumn(float n) {
    for (int i = 0; i < table.size(); ++i) {
        table[i].erase(table[i].begin() + n);
    }
}

Matrix& Matrix::toNull(float n) {
    std::vector<std::vector<float>> v;
    for (int i = 0; i < n; ++i) {
        v.resize(v.size() + 1);
        for (int j = 0; j < n; ++j) {
            v[i].push_back(0);
        }
    }
    table = v;
    return *this;
}

Matrix& Matrix::toE(float n) {
    std::vector<std::vector<float>> v;
    for (int i = 0; i < n; ++i) {
        v.resize(v.size() + 1);
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                v[i].push_back(1);
            }
            else {
                v[i].push_back(0);
            }
        }
    }
    table = v;
    return *this;
}

Matrix& Matrix::transpose() {
    if (!isQuadratic()) {
        throw std::invalid_argument("Matrix isn't quadratic");
    }
    for (int i = 0; i < size().first; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            float tmp = table[i][j];
            table[i][j] = table[j][i];
            table[j][i] = tmp;
        }
    }
    return *this;
}

void Matrix::copy(Matrix& m) {
    table = m.table;
}

float Matrix::determinant(std::vector<std::vector<float>> m) {
    if (!isQuadratic()) {
        throw std::invalid_argument("Matrix isn't quadratic");
    }
    float det = 0;
    if (m.size() == 1) {
        return m[0][0];
    }
    for (int j = 0; j < m.size(); ++j) {
        Matrix minor(m);
        minor.deleteRow(0);
        minor.deleteColumn(j);
        det += m[0][j] * std::pow(-1,j) * determinant(minor.table);
    }
    return det;
}

int Matrix::rank() {
    int r = 0;
    if (!(isQuadratic())) {
        throw std::invalid_argument("Matrix is not quadratic");
    }
    if (determinant() != 0) {
        return size().first;
    }
    if (*this == Matrix().toNull(size().first)) {
        return 0;
    }
    r = size().first - 1;
    std::vector<Matrix> storage;
    std::vector<Matrix> storageCopy;
    storage.push_back(*this);
    while (1) {
        for (int i = 0; i < size().first; ++i) {
            for (int j = 0; j < size().first; ++j) {
                for (int k = 0; k < storage.size(); ++k) {
                    Matrix minor(storage[k]);
                    minor.deleteRow(i);
                    minor.deleteColumn(j);
                    if (minor.determinant() != 0) {
                        return r;
                    }
                    storageCopy.push_back(minor);
                }
            }
        }
        r--;
        storage.clear();
        storage = storageCopy;
        storageCopy.clear();
    }
}

float Matrix::determinant() {
    return determinant(table);
}


Matrix Matrix::pow(int degree) {
    if (!isQuadratic()) {
        throw std::invalid_argument("Matrix isn't quadratic");
    }
    if (degree == 0) {
        Matrix copy(*this);
        return copy.toE(copy.size().first);
    }
    Matrix m(*this);
    float det = determinant();
    if (det == 0) {
        throw std::invalid_argument("Matrix det is 0, no reverse Matrix");
    }
    if (degree == -1) {
        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table.size(); ++j) {
                Matrix copy(*this);
                copy.deleteRow(i);
                copy.deleteColumn(j);
                m[i][j] = std::pow(-1, i + j) * determinant(copy.table) / (det);
            }
        }
        m.transpose();
        return m;
    }
    m.toE(size().first);
    for (int i = 0; i < degree; ++i) {
        m = m * *this;
    }
    return m;
}

std::vector<float>& Matrix::operator[](int index) {
    if (index < 0 || index > size().first - 1) {
        throw std::out_of_range("Incorrect index");
    }
    return table[index];
}

Matrix Matrix::operator+(Matrix& m) {
    if (m.size() != size()) {
        throw std::invalid_argument("Different size of matrices");
    }
    Matrix result(*this);
    for (int i = 0; i < size().first; ++i) {
        for (int j = 0; j < size().second; ++j) {
            result.table[i][j] += m[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(Matrix& m) {
    if (m.size() != size()) {
        throw std::invalid_argument("Different size of matrices");
    }
    Matrix result(*this);
    for (int i = 0; i < size().first; ++i) {
        for (int j = 0; j < size().second; ++j) {
            result.table[i][j] -= m[i][j];
        }
    }
    return result;
}


Matrix Matrix::operator*(Matrix& m) {
    if (m.size().second != size().first) {
        throw std::invalid_argument("Incorrect size of matrices");
    }
    std::vector<std::vector<float>> v;
    std::vector<float> string;
    for (int i = 0; i < size().first; ++i) {
        string.clear();
        string.resize(m.size().second, 0);
        v.push_back(string);
    }
    Matrix matrix(v);
    float a;
    for (int i = 0; i < size().first; ++i) {
        for (int j = 0; j < m.size().second; ++j) {
            for (int k = 0; k < size().second; ++k) {
                a = table[i][k] * m[k][j];
                matrix[i][j] += a;
            }
        }
    }
    return matrix;
}

Matrix Matrix::operator/(Matrix& m) {
    Matrix reverse = m.pow(-1);
    return *this * reverse;
}

bool Matrix::operator==(Matrix& m) {
    if (table == m.table) {
        return true;
    }
    return false;
}

bool Matrix::isQuadratic() {
    if (table.size() == 0) {
        return true;
    }
    if (table.size() == table[0].size()) {
        return true;
    }
    return false;
}


std::ostream& operator<<(std::ostream& out, Matrix m) {
    for (int i = 0; i < m.size().first; ++i) {
        for (int j = 0; j < m.size().second; ++j) {
            out << std::setw(3) << std::round(m[i][j] * 10) / 10 << " ";
        }
        if (i == m.size().first - 1) break;
        out << std::endl;
    }
    return out;
}
