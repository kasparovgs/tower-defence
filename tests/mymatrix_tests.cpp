#include <gtest/gtest.h>
#include "mymatrix.h"

TEST(MyMatrixTests, rezise) {
    MyMatrix<int> matrix{};
    EXPECT_NO_THROW(matrix.resize(1, 3));
    EXPECT_EQ(matrix.rows(), 1);
    EXPECT_EQ(matrix.columns(), 3);
    EXPECT_NO_THROW(matrix.resize(1, 2));
}


TEST(MyMatrixTests, clear) {
    MyMatrix<int> matrix{};
    matrix.resize(1, 3);
    EXPECT_NO_THROW(matrix.clear());
    EXPECT_EQ(matrix.rows(), 0);
    EXPECT_EQ(matrix.columns(), 0);
}


TEST(MyMatrixTests, iterators) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        EXPECT_EQ(*i, 1);
    }
}


TEST(MyMatrixTests, copyConstractor) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    auto copiedMatrix = matrix;
    for (auto i = copiedMatrix.begin(); i < copiedMatrix.end(); i++) {
        EXPECT_EQ(*i, 1);
    }
    EXPECT_EQ(copiedMatrix.rows(), matrix.rows());
    EXPECT_EQ(copiedMatrix.columns(), matrix.columns()); 
}


TEST(MyMatrixTests, copyEq) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    MyMatrix<int> copiedMatrix{};
    copiedMatrix = matrix;
    for (auto i = copiedMatrix.begin(); i < copiedMatrix.end(); i++) {
        EXPECT_EQ(*i, 1);
    }
    EXPECT_EQ(copiedMatrix.rows(), matrix.rows());
    EXPECT_EQ(copiedMatrix.columns(), matrix.columns());
}


TEST(MyMatrixTests, moveConstractor) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }

    MyMatrix<int> movedMatrix = std::move(matrix);
    for (auto i = movedMatrix.begin(); i < movedMatrix.end(); i++) {
        EXPECT_EQ(*i, 1);
    }
    EXPECT_EQ(movedMatrix.rows(), 3);
    EXPECT_EQ(movedMatrix.columns(), 3);
    EXPECT_EQ(matrix.rows(), 0);
    EXPECT_EQ(matrix.columns(), 0);
}


TEST(MyMatrixTests, moveEq) {
    MyMatrix<int> matrix(3, 3);
    EXPECT_NO_THROW(matrix = MyMatrix<int>(5, 6));
    EXPECT_EQ(matrix.rows(), 5);
    EXPECT_EQ(matrix.columns(), 6);
}


TEST(MyMatrixTests, iterMinusMinus) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    for (auto i = matrix.end(); i >= matrix.begin(); i--) {
        *i = 0;
    }
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        EXPECT_EQ(*i, 0);
    }
}


TEST(MyMatrixTests, iterPlusN) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    auto it = matrix.begin();
    *(it + 2) = 10;
    EXPECT_EQ(matrix[0][2], 10);
}


TEST(MyMatrixTests, NPlusIter) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    auto it = matrix.begin();
    *(2 + it) = 10;
    EXPECT_EQ(matrix[0][2], 10);
}


TEST(MyMatrixTests, iterPlusEqN) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    auto it = matrix.begin();
    it += 2;
    *it = 10;
    EXPECT_EQ(matrix[0][2], 10);    
}


TEST(MyMatrixTests, ThrowByIndexError) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    EXPECT_THROW(matrix[10][10], std::out_of_range);
    EXPECT_THROW(matrix[0][10], std::out_of_range);
    const MyMatrix<int> constMatrix = matrix;
    EXPECT_THROW(constMatrix[10][10], std::out_of_range);
    EXPECT_THROW(constMatrix[0][10], std::out_of_range);
}


TEST(MyMatrixTests, IterMinusN) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    auto it = matrix.end();
    *(it - 3) = 10;
    EXPECT_EQ(matrix[2][0], 10);
}


TEST(MyMatrixTests, IterMinusEqN) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    auto it = matrix.end();
    it -= 3;
    *it = 10;
    EXPECT_EQ(matrix[2][0], 10);
}


TEST(MyMatrixTests, IterEq) {
    MyMatrix<int> matrix(3, 3);
    for (auto i = matrix.begin(); i < matrix.end(); i++) {
        *i = 1;
    }
    auto it1 = matrix.end();
    it1 -= 3;
    auto it2 = it1;
    EXPECT_EQ(it1, it2);
}


TEST(MyMatrixTests, diffBetweenIters) {
    const MyMatrix<int> matrix(3, 3);
    auto it1 = matrix.cbegin();
    auto it2 = matrix.cend();
    EXPECT_EQ(it2 - it1, 9);
}


TEST(MyMatrixTests, spaceshipOperator) {
    const MyMatrix<int> matrix(3, 3);
    auto it1 = matrix.cbegin();
    auto it2 = matrix.cend();
    EXPECT_EQ(it2 <=> it1, std::strong_ordering::greater);
}


TEST(MyMatrixTests, IterByIndex) {
    const MyMatrix<int> matrix(3, 3);
    auto it1 = matrix.cbegin();
    auto it2 = matrix.cend();
    EXPECT_EQ(it1[8], *it2);
}