#include <iostream>
#include "matrix.h"
#include <numeric>
#include <gtest/gtest.h>

#define epsilon 100 * numeric_limits<float>::epsilon()

using namespace std;

TEST(creation, invalidVec) {
    std::vector<std::vector<float>> v = {{1, 2},
                                         {1, 2, 3}};
    ASSERT_THROW(Matrix m(v), std::invalid_argument);
}

TEST(creation, creationFromString) {
    std::vector<std::string> v = {"1 2 3",
                                  "4 5 6",
                                  "7 8 9"};
    Matrix m(v);
    std::vector<std::vector<float>> v1 = {{1, 2, 3},
                                   {4, 5, 6},
                                   {7, 8, 9}};
    Matrix right(v1);
    ASSERT_TRUE(right == m);
}

TEST(creation, invalidArgumentsFromString) {
    std::vector<std::string> v = {"1 2 a",
                                  "4 5 6",
                                  "7 8 9"};
    ASSERT_THROW(Matrix m(v), std::invalid_argument);
}

TEST(creation, invalidSizeOfString) {
    std::vector<std::string> v = {"1 2 3 4",
                                  "4 5 6",
                                  "7 8 9"};
    ASSERT_THROW(Matrix m(v), std::invalid_argument);
}

TEST(equalityOperator, eqTrue) {
    vector<vector<float>> v1 = {{1, 2, 3, 4, 5},
                                {6, 7, 8 , 9, 10}};
    vector<vector<float>> v2 = {{1, 2, 3, 4, 5},
                                {6, 7, 8 , 9, 10.0}};
    Matrix m1(v1);
    Matrix m2(v2);
    ASSERT_TRUE((m1 == m2) == true);
}

TEST(equalityOperator, eqFalse) {
    vector<vector<float>> v1 = {{1, 2, 3, 4, 5},
                                {6, 7, 8 , 9, 10}};
    vector<vector<float>> v2 = {{1, 2, 3, 4, 5},
                                {6, 7, 8 , 9, 10.1}};
    Matrix m1(v1);
    Matrix m2(v2);
    ASSERT_TRUE((m1 == m2) == false);
}

TEST(staticMatrices, NULL_Matrix) {
    Matrix m;
    vector<vector<float>> n = {{0, 0, 0, 0}, 
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0}};
    Matrix nu(n);
    ASSERT_TRUE(m.toNull(4) == nu);
}

TEST(staticMatrices, E_Matrix) {
    Matrix m;
    vector<vector<float>> v = {{1, 0, 0, 0}, 
                               {0, 1, 0, 0},
                               {0, 0, 1, 0},
                               {0, 0, 0, 1}};
    Matrix e(v);
    ASSERT_TRUE(m.toE(4) == e);
}

TEST(SummationTest, simpleSummation) {
    vector<vector<float>> v1 = {{1, 0},
                                {0, 1}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{1, 0},
                                {0, 1}};
    Matrix m2(v2);
    vector<vector<float>> res = {{2, 0},
                                 {0, 2}};
    Matrix mRes(res);
    ASSERT_TRUE(m1 + m2 == mRes);
}

TEST(SummationTest, regularSummation) {
    vector<vector<float>> v1 = {{1, 2},
                                {3, 4}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{5, 6},
                                {7, 8}};
    Matrix m2(v2);
    vector<vector<float>> res = {{6, 8},
                                 {10, 12}};
    Matrix mRes(res);
    ASSERT_TRUE(m1 + m2 == mRes);
}

TEST(SummationTest, regularSummationFloat) {
    vector<vector<float>> v1 = {{1.4, 2.2},
                                {3.1, 4.9}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{5, 6.6},
                                {7.9, 8.0}};
    Matrix m2(v2);

    vector<vector<float>> res = {{6.4, 8.8},
                                 {11, 12.9}};
    Matrix mRes(res);
    ASSERT_TRUE(m1 + m2 == mRes);
}

TEST(SummationTest, multipleMatrixAdding) {
    vector<vector<float>> v1 = {{1, 2},
                                {3, 4}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{5, 6},
                                {7, 8}};
    Matrix m2(v2);
    vector<vector<float>> v3 = {{6, 8},
                                {10, 12}};
    Matrix m3(v3);
    vector<vector<float>> res = {{12, 16},
                                 {20, 24}};
    Matrix mRes(res);
    ASSERT_TRUE(m1 + m2 + m3 == mRes);
}

TEST(SummationTest, summatingDiffSize) {
    vector<vector<float>> v1 = {{1, 0, 2},
                                {0, 1, 3}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{1, 0},
                                {0, 1}};
    Matrix m2(v2);
    ASSERT_THROW(m1 + m2, invalid_argument);
}


TEST(MultiplyTest, multiToE) {
    vector<vector<float>> v1 = {{1, 2},
                                {3, 4}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{1, 0},
                                {0, 1}};
    Matrix m2(v2);
    ASSERT_TRUE(m1 * m2 == m1);
}

TEST(MultiplyTest, basicMulti) {
    vector<vector<float>> v1 = {{1, 2},
                                {3, 4}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{4, 2},
                                {3, 1}};
    Matrix m2(v2);
    vector<vector<float>> res = {{10, 4},
                                 {24, 10}};
    Matrix mRes(res);
    ASSERT_TRUE(m1 * m2 == mRes);
}

TEST(MultiplyTest, floatMulti) {
    vector<vector<float>> v1 = {{1.5, 3.2},
                                {5, 7.8}};
    vector<vector<float>> v2 = {{2.7, 5.2},
                                {0, 0.1}};
    Matrix m1(v1);
    Matrix m2(v2);
    vector<vector<float>> res = {{4.05, 8.12},
                                {13.5, 26.78}};
    Matrix mRes(res);
    ASSERT_TRUE(m1 * m2 == mRes);
}

TEST(MultiplyTest, diffSizeGood) {
    vector<vector<float>> v1 = {{1, 2, 3},
                                {1, 2, 3}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{1, 2},
                                {1, 2},
                                {1, 2}};
    Matrix m2(v2);
    vector<vector<float>> res = {{6, 12},
                                 {6, 12}};
    Matrix mRes(res);
    ASSERT_TRUE(m1 * m2 == mRes);
}

TEST(MultiplyTest, diffSizeBad) {
    vector<vector<float>> v1 = {{1, 2, 3},
                                {1, 2, 3}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{1, 2},
                                {1, 2}};
    Matrix m2(v2);
    ASSERT_THROW(m2 * m1, invalid_argument);
}

TEST(detTest, test1) {
    vector<vector<float>> v1 = {{1, 2},
                                {3, 4}};
    Matrix m1(v1);
    ASSERT_TRUE(m1.determinant() == -2);
}

TEST(detTest, test2) {
    vector<vector<float>> v1 = {{1, 2},
                                {1, 2}};
    Matrix m1(v1);
    ASSERT_TRUE(m1.determinant() == 0);
}

TEST(detTest, test3) {
    vector<vector<float>> v1 = {{1, 0, 0},
                                {0, 1, 2},
                                {0, 3, 4}};
    Matrix m1(v1);
    ASSERT_TRUE(m1.determinant() == -2);
}

TEST(detTest, floatDetZero) {
    vector<vector<float>> v1 = {{1.1, 2.2, 3.3},
                                {4.4, 5.5, 6.6},
                                {7.7, 8.8, 9.9}};
    Matrix m1(v1);
    ASSERT_TRUE(abs(m1.determinant()) <= epsilon);
}

TEST(detTest, floatDet) {
    vector<vector<float>> v1 = {{1.1, 2.2, 3.2},
                                {4.4, 5.5, 6.6},
                                {7.7, 8.8, 9.8}};
    Matrix m1(v1);
    ASSERT_TRUE(m1.determinant() >= 0.726 - epsilon &&
                m1.determinant() <= 0.726 + epsilon);
}

TEST(detTest, invalidMatrix) {
    vector<vector<float>> v1 = {{1, 0, 0},
                                {0, 1, 2}};
    Matrix m1(v1);
    ASSERT_THROW(m1.determinant(), invalid_argument);
}

TEST(rankTest, rankIsSize) {
    std::vector<std::vector<float>> v1 = {{1, 2, 3},
                                        {4, 2, 1},
                                        {3, 4, 5}};
    Matrix m(v1);
    ASSERT_TRUE(m.rank() == 3);
}

TEST(rankTest, rankIsOneLess) {
    std::vector<std::vector<float>> vec = {{1, 2},
                                           {1, 2}};
    Matrix m(vec);
    ASSERT_TRUE(m.rank() == 1);
}

TEST(rankTest, rankIsTwoLess) {
    std::vector<std::vector<float>> v1 = {{1, 2, 3},
                                        {3, 6, 9},
                                        {2, 4, 6}};
    Matrix m(v1);
    ASSERT_TRUE(m.rank() == 1);
}

TEST(powTest, invalidMatrix) {
    vector<vector<float>> v1 = {{1, 0, 0},
                                {0, 1, 2}};
    Matrix m1(v1);
    ASSERT_THROW(m1.pow(2), invalid_argument);
}

TEST(powTest, test1) {
    vector<vector<float>> v1 = {{1, 0, 0},
                                {0, 1, 2},
                                {0, 3, 4}};
    Matrix m1(v1);
    Matrix m2 = m1.pow(2);
    Matrix m3 = m1 * m1;
    ASSERT_TRUE(m2 == m3);
}


TEST(powTest, reverseMatrix) {
    vector<vector<float>> v1 = {{1, 0, 0},
                                {0, 3, 2},
                                {0, 4, 3}};
    Matrix m1(v1);
    Matrix m2 = m1.pow(-1);
    vector<vector<float>> v2 = {{1, 0, 0},
                                {0, 3, -2},
                                {0, -4, 3}};
    Matrix mRes(v2);
    ASSERT_TRUE(m2 == mRes);
}

// TEST(powTest, reverseFloatMatrix) {
//     vector<vector<float>> v1 = {{1.5, 2.1, 0},
//                                 {0, 3.4, 2.8},
//                                 {3, 4.6, 3.1}};
//     Matrix m1(v1);
//     Matrix m2 = m1.pow(-1);
//     vector<vector<float>> v2 = {{1, 0, 0},
//                                 {0, 3, -2},
//                                 {0, -4, 3}};
//     Matrix mRes(v2);
//     ASSERT_TRUE(m2 == mRes);
// }

TEST(transposeTest, invalidMatrix) {
    vector<vector<float>> v1 = {{1, 0, 0},
                                {0, 1, 2}};
    Matrix m1(v1);
    ASSERT_THROW(m1.transpose(), invalid_argument);
}

TEST(transposeTest, test1) {
    vector<vector<float>> v1 = {{1, 2, 0},
                                {0, 1, 2},
                                {0, 3, 4}};
    Matrix m1(v1);
    vector<vector<float>> v2 = {{1, 0, 0},
                                {2, 1, 3},
                                {0, 2, 4}};
    Matrix m2(v2);
    ASSERT_TRUE(m1.transpose() == m2);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
  
    return RUN_ALL_TESTS();
}