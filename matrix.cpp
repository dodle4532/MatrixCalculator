#include "matrix.h"

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

void Matrix::reset() {
    for (int i = 0; i < size().first; ++i) {
        std::fill(table[i].begin(), table[i].end(), 0);
    }
}

void Matrix::resetToE() {
    reset();
    for (int i = 0; i < size().first; ++i) {
        for (int j = 0; j < size().second; ++j) {
            if (i == j) {
                table[i][j] = 1;
            }
        }
    }
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

Matrix Matrix::pow(int degree) {
    Matrix m(*this);
    m.resetToE();
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
