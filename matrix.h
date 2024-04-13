/*! \mainpage MatrixCalculator Documentation
    \section desc Describe
    This is a calculator that allow user to work with matrices
    It can be used for addition, miltiplicating, transposing, finding reverse matrix and determinant
    \section main_class Main Class
    \ref Matrix
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <ostream>
#include <fstream>

/*!
    \brief **Class to work with matrices**
*/
class Matrix
{
public:
    Matrix() = default;

    /*!
        \brief Constructor which convert vector to Matrix
        \param vec 2D vector of float numbers, number of rows and columns must be constant

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::vector<float>> vec = {{1, 0.5},
                                                   {4.2, 8}};
            Matrix m(vec);
            std::cout << m << std::endl;
            return 0;
        }
        \endcode
    */
    Matrix(std::vector<std::vector<float>> vec);

    /*!
        \brief Constructor which convert string to Matrices, can be used for reading from file

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::string> v = {"1 2 3",
                                          "4 5 6",
                                          "7 8 9"};
            Matrix m(v);
            std::cout << m << std::endl;
            return 0;
        }
        \endcode
    */
    Matrix(std::vector<std::string> vec);

    /*!
        \brief Constructor which create Matrix from file(numbers divided by spaces and ENTERs)

        <b>Example using</b>
        \code 
        int main() {
            Matrix m("example.txt");
            std::cout << m << std::endl;
            return 0;
        }
        \endcode
    */
    Matrix(std::string filename);

    /*!
        \brief Get's size of matrix
        \return First is number of rows, second is number of columns

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::vector<float>> vec = {{1, 0.5},
                                                   {4.2, 8}};
            Matrix m(vec);
            std::cout << "Rows - " << m.size().first << "Columns - " << m.size().second << std::endl;
            return 0;
        }
        \endcode
    */
    std::pair<float, float> size();

    /*!
        \brief Method to convert any matrix to n*n matrix with all zeros
        \param n Size of result matrix

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::vector<float>> vec = {{1, 0.5},
                                                   {4.2, 8}};
            Matrix m(vec);
            std::cout << m.toNull(3) << std::endl;
            // 0 0 0
            // 0 0 0
            // 0 0 0
            return 0;
        }
        \endcode
    */
    Matrix& toNull(float n);

    /*!
        \brief Method to convert any matrix to n*n Identity matrix
        \param n Size of result matrix

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::vector<float>> vec = {{1, 0.5},
                                                   {4.2, 8}};
            Matrix m(vec);
            std::cout << m.toE(3) << std::endl;
            // 1 0 0
            // 0 1 0
            // 0 0 1
            return 0;
        }
        \endcode
    */
    Matrix& toE(float n);

    /*!
        \brief Method to transpose matrices
        \details Changes rows and columns with each others(can be done only with quadratic matrix)
        \details It changes matrix itself and returns result

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::vector<float>> vec = {{1, 0.5},
                                                   {4.2, 8}};
            Matrix m(vec);
            //m.transpose();
            //std::cout << m << std::endl;
            std::cout << m.transpose() << std::endl;
            // 1 4.2
            // 0.5 8
            return 0;
        }
        \endcode
    */
    Matrix& transpose();

    /*!
        \brief Method to calcucate determinant
        \details Only with quadratic matrix

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::vector<float>> vec = {{1, 0.5},
                                                   {4.2, 8}};
            Matrix m(vec);
            std::cout << m.determinant() << std::endl;
            // 5.9
            return 0;
        }
        \endcode
    */
    float determinant();

    /*!
        \brief Method to raise quadratic matrix to any n degree
        \param n Can be natural, or 0, or -1
        \return Doesn't change matrix, returns powed matrix, if n = 0 then E, if n = -1 then reversed matrix

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::vector<float>> vec = {{1, 0},
                                                   {0, 8}};
            Matrix m(vec);
            std::cout << m.pow(2) << std::endl;
            // 1 0
            // 0 64
            std::cout << m.pow(0) << std::endl;
            // 1 0
            // 0 1
            std::cout << m.pow(-1) << std::endl;
            // 1 0
            // 0 0.1
            return 0;
        }
        \endcode
    */
    Matrix pow(int degree);

    /*!
        \brief Method to copy other Matrix to this
        \param m Matrix from which copy
    */
    void copy(Matrix& m);

    /*!
        \brief Checks if matrix is Quadratic or Not
    */
    bool isQuadratic();

    /*!
        \brief Outputs matrix to stream
        \details Rounds floats to the first digit after the point
    */
    friend std::ostream& operator<<(std::ostream& out, Matrix m);

    /*!
        \brief Operator to add two Matrices
    */
    Matrix& operator+(Matrix& m);

    /*!
        \brief Operator to multiply to matrices
    */
    Matrix& operator*(Matrix& m);

    /*!
        \brief Operator to check if matrices is equal or not
    */
    bool operator==(Matrix& m);

    /*!
        \brief Operator thats returns row under index number
        \param index Number of which row should method return(starts with 0)

        <b>Example using</b>
        \code 
        int main() {
            std::vector<std::vector<float>> vec = {{1, 0.5},
                                                   {4.2, 8}};
            Matrix m(vec);
            m[1]; // {4.2, 8}
            return 0;
        }
        \endcode
    */
    std::vector<float>& operator[](int index);

private:
    std::vector<std::vector<float>> table;
    void deleteRow(float n);
    void deleteColumn(float n);
    float determinant(std::vector<std::vector<float>> m);
};

#endif // MATRIX_H
