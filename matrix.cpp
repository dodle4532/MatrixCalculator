#include "matrix.h"
#include <cmath>
#include <iostream>

Matrix::Matrix(std::vector<std::vector<int>> vec) {
    table = vec;
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
    int size = table[0].size();
    for (int i = 1; i < table.size(); ++i) {
        if (size != table[i].size()) {
            throw std::invalid_argument("Incorrect data - different size of lines");
        }
    }
}

std::pair<int, int> Matrix::size() {
    return std::make_pair<int, int> (table.size(), table[0].size());
}

void Matrix::deleteRow(int n) {
    table.erase(table.begin() + n);
}
void Matrix::deleteColumn(int n) {
    for (int i = 0; i < table.size(); ++i) {
        table[i].erase(table[i].begin() + n);
    }
}

Matrix& Matrix::toNull(int n) {
    std::vector<std::vector<int>> v;
    for (int i = 0; i < n; ++i) {
        v.resize(v.size() + 1);
        for (int j = 0; j < n; ++j) {
            v[i].push_back(0);
        }
    }
    table = v;
    return *this;
}

Matrix& Matrix::toE(int n) {
    std::vector<std::vector<int>> v;
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

void Matrix::transpose() {
    for (int i = 0; i < size().first; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            int tmp = table[i][j];
            table[i][j] = table[j][i];
            table[j][i] = tmp;
        }
    }
}

void Matrix::copy(Matrix& m) {
    table = m.table;
}

int Matrix::determinant(std::vector<std::vector<int>> m) {
    int det = 0;
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

int Matrix::determinant() {
    return determinant(table);
}


Matrix Matrix::pow(int degree) {
    Matrix m(*this);
    int det = determinant();
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

std::vector<int>& Matrix::operator[](int index) {
    if (index < 0 || index > size().first - 1) {
        throw std::out_of_range("Incorrect index");
    }
    return table[index];
}

Matrix& Matrix::operator+(Matrix& m) {
    if (m.size() != size()) {
        throw std::out_of_range("Different size of matrices");
    }
    for (int i = 0; i < size().first; ++i) {
        for (int j = 0; j < size().second; ++j) {
            table[i][j] += m[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*(Matrix& m) {
    if (m.size().second != size().first) {
        throw std::out_of_range("Different size of matrices");
    }
    std::vector<std::vector<int>> v;
    std::vector<int> string;
    for (int i = 0; i < size().first; ++i) {
        string.clear();
        string.resize(m.size().second, 0);
        v.push_back(string);
    }
    Matrix matrix(v);
    int a;
    for (int i = 0; i < size().first; ++i) {
        for (int j = 0; j < m.size().second; ++j) {
            for (int k = 0; k < size().second; ++k) {
                a = table[i][k] * m[k][j];
                matrix[i][j] += a;
            }
        }
    }
    copy(matrix);
    return *this;
}


std::ostream& operator<<(std::ostream& out, Matrix m) {
    for (int i = 0; i < m.size().first; ++i) {
        for (int j = 0; j < m.size().second; ++j) {
            out << m[i][j] << " ";
        }
        if (i == m.size().first - 1) break;
        out << std::endl;
    }
    return out;
}
