//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"
#include "vector"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class Matrix1x1 : public ::testing::Test {

protected:
    Matrix m{};
};


TEST(GeneralTests, MatrixConstructor) {

    EXPECT_ANY_THROW(Matrix(0, 4));
    EXPECT_ANY_THROW(Matrix(4, 0));
    EXPECT_ANY_THROW(Matrix(0, 0));

    Matrix m1{};
    EXPECT_EQ(m1.get(0, 0), 0);

    Matrix m2{32, 234};
    EXPECT_EQ(m2.get(12, 143), 0);

    EXPECT_NO_THROW((Matrix{5432, 3245}));

}

TEST(GeneralTests, SetValue) {

    Matrix m1 = Matrix(3, 3);
    m1.set(std::vector<std::vector<double>> {
            {1, 2, 1},
            {2, 1, 2},
            {1, 2, 1}
    });

    EXPECT_FALSE(m1.set(4, 2, 0));
    EXPECT_FALSE(m1.set(2, 6, 0));
    EXPECT_FALSE(m1.set(9, 7, 0));

    EXPECT_TRUE(m1.set(2, 2, 0));
    EXPECT_TRUE(m1.set(2, 2, -10));
    EXPECT_TRUE(m1.set(2, 2, 10));
    EXPECT_TRUE(m1.set(2, 2, 0.32));
    EXPECT_TRUE(m1.set(2, 2, -0.52));
    EXPECT_TRUE(m1.set(2, 2, 324450));

    Matrix m2 = Matrix(5, 5);

    m2.set(std::vector<std::vector<double>> {
            {1, 2, 1, 1, 2},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1}
    });

    EXPECT_FALSE(m1.set(7, 2, 0));
    EXPECT_FALSE(m1.set(2, 76, 0));
    EXPECT_FALSE(m1.set(9, 7, 0));

    EXPECT_TRUE(m1.set(2, 2, 0));
    EXPECT_TRUE(m1.set(2, 2, -10));
    EXPECT_TRUE(m1.set(2, 2, 10));
    EXPECT_TRUE(m1.set(2, 2, 0.32));
    EXPECT_TRUE(m1.set(2, 2, -0.52));
    EXPECT_TRUE(m1.set(2, 2, 324450));

}

TEST(GeneralTests, SetVector) {

    Matrix m1{};
    EXPECT_TRUE(m1.set(std::vector<std::vector<double>> {{0}}));
    EXPECT_TRUE(m1.set(std::vector<std::vector<double>> {{-10}}));
    EXPECT_TRUE(m1.set(std::vector<std::vector<double>> {{325340}}));

    std::vector<double> v1 (0, 0);
    EXPECT_FALSE(m1.set(std::vector<std::vector<double>> {(0, v1)}));

    Matrix m2 = Matrix(3, 3);
    m2.set(std::vector<std::vector<double>> {
            {1, 2, 1},
            {2, 1, 2},
            {1, 2, 1}
    });

    EXPECT_FALSE(m2.set(std::vector<std::vector<double>> {
            {1, 2, 3},
            {3, 2, 1}
    }));

    EXPECT_TRUE(m2.set(std::vector<std::vector<double>> {
            {1, 2, 3},
            {3, 1, 2},
            {2, 3, 1}
    }));
}

TEST(GeneralTests, GetValue) {

    Matrix m1{};
    EXPECT_EQ(0, m1.get(0, 0));
    EXPECT_ANY_THROW(m1.get(1, 1));

    Matrix m2 = Matrix(3, 3);
    m2.set(std::vector<std::vector<double>> {
            {1, 2, 1},
            {2, 1, 2},
            {1, 2, 1}
    });

    EXPECT_EQ(1, m2.get(1, 1));
    EXPECT_FALSE(m2.get(1, 1) == 2);
    EXPECT_ANY_THROW(m2.get(64, 1));
    EXPECT_ANY_THROW(m2.get(1, -5));

    Matrix m3 = Matrix(5, 5);
    m3.set(std::vector<std::vector<double>> {
            {1, 2, 1, 1, 2},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1}
    });

    EXPECT_EQ(2, m3.get(2, 1));
    EXPECT_FALSE(m3.get(1, 1) == 2);
    EXPECT_ANY_THROW(m3.get(4, 54));
    EXPECT_ANY_THROW(m3.get(-1, 4));

    Matrix m4 = Matrix(2, 4);
    m4.set(std::vector<std::vector<double>> {
            {1, 2, 1, 1},
            {1, 2, 1, 2}
    });

    EXPECT_EQ(2, m3.get(1, 2));
    EXPECT_FALSE(m3.get(2, 1) == 1);
    EXPECT_ANY_THROW(m3.get(2, 5));
    EXPECT_ANY_THROW(m3.get(5, -3));
}

TEST(OperatorTests, Equal) {
    Matrix m1{};

    Matrix m2 = Matrix(3, 3);
    m2.set(std::vector<std::vector<double>> {
            {1, 2, 1},
            {2, 1, 2},
            {1, 2, 1}
    });

    Matrix m3 = Matrix(5, 5);
    m3.set(std::vector<std::vector<double>> {
            {1, 2, 1, 1, 2},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1}
    });

    //m1
    EXPECT_TRUE(m1==m1);
    Matrix mat1{};
    EXPECT_TRUE(m1==mat1);
    mat1.set(0, 0, 3);
    EXPECT_FALSE(m1==mat1);
    EXPECT_ANY_THROW(m1==m2);

    //m2
    EXPECT_TRUE(m2==m2);
    Matrix mat2 = Matrix(3, 3);
    mat2.set(std::vector<std::vector<double>> {
            {1, 2, 1},
            {2, 1, 2},
            {1, 2, 1}
    });
    EXPECT_TRUE(m2==mat2);
    mat2.set(1, 1, 33);
    EXPECT_FALSE(m2==mat2);
    EXPECT_ANY_THROW(m2==m3);

    //m3
    EXPECT_TRUE(m3==m3);
    Matrix mat3 = Matrix(5, 5);
    mat3.set(std::vector<std::vector<double>> {
            {1, 2, 1, 1, 2},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1}
    });
    EXPECT_TRUE(m3==mat3);
    mat3.set(2, 4, 6612);
    EXPECT_FALSE(m3==mat3);
    EXPECT_ANY_THROW(m1==m3);
}

TEST(OperatorTests, Addition) {
    Matrix m1{};

    Matrix m2 = Matrix(3, 3);
    m2.set(std::vector<std::vector<double>> {
            {1, 2, 1},
            {2, 1, 2},
            {1, 2, 1}
    });

    Matrix m3 = Matrix(5, 5);
    m3.set(std::vector<std::vector<double>> {
            {1, 2, 1, 2, 1},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1},
            {2, 1, 2, 1, 2},
            {1, 2, 1, 2, 1}
    });

    Matrix m4 = Matrix(2, 4);
    m4.set(std::vector<std::vector<double>> {
            {1, 2, 3, 4},
            {4, 3, 2, 1}
    });

    EXPECT_ANY_THROW(m1+m2);
    EXPECT_ANY_THROW(m3+m2);
    EXPECT_ANY_THROW(m1+m4);
    EXPECT_ANY_THROW(m4+m2);

    EXPECT_TRUE(m1+m1 == m1);
    Matrix mat1{};
    mat1.set(0, 0, 1);
    EXPECT_TRUE(m1 + mat1 == mat1);
    EXPECT_FALSE(m1 + mat1 == m1);
    EXPECT_FALSE((m1 + m1) + m1 == mat1);

    Matrix mat2 = Matrix(3, 3);
    mat2.set(std::vector<std::vector<double>> {
            {2, 4, 2},
            {4, 2, 4},
            {2, 4, 2}
    });
    EXPECT_TRUE(m2 + m2 == mat2);
    EXPECT_FALSE(m2 + m2 == m2);

    Matrix mat3 = Matrix(5, 5);
    mat3.set(std::vector<std::vector<double>> {
            {2, 4, 2, 4, 2},
            {4, 2, 4, 2, 4},
            {2, 4, 2, 4, 2},
            {4, 2, 4, 2, 4},
            {2, 4, 2, 4, 2}
    });
    EXPECT_TRUE(m3 + m3 == mat3);
    EXPECT_FALSE(m3 + m3 == m3);

    Matrix mat4 = Matrix(2, 4);
    mat4.set(std::vector<std::vector<double>> {
            {2, 4, 6, 8},
            {8, 6, 4, 2}
    });
    EXPECT_TRUE(m4 + m4 == mat4);
    EXPECT_FALSE(mat4 + mat4 == m4);
}

TEST(OperatorTests, Multiplication) {

    Matrix m1{};
    Matrix mat1{};
    mat1.set(0, 0, 1);
    EXPECT_TRUE(m1*m1 == m1);
    EXPECT_TRUE(mat1 * mat1 == mat1);
    EXPECT_FALSE(mat1 * m1 == mat1);



    Matrix m2 = Matrix(3, 3);
    m2.set(std::vector<std::vector<double>> {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
    });

    Matrix mat2 = Matrix(3, 3);
    mat2.set(std::vector<std::vector<double>> {
            {2, 2, 2},
            {2, 2, 2},
            {2, 2, 2}
    });

    Matrix expected = Matrix(3, 3);
    expected.set(std::vector<std::vector<double>> {
            {3, 3, 3},
            {3, 3, 3},
            {3, 3, 3}
    });

    EXPECT_TRUE(m2*m2 == expected);
    EXPECT_FALSE(mat2 * mat2 == expected);
    EXPECT_FALSE(mat2 * mat2 == mat2);



    Matrix m3 = Matrix(3, 4);
    m3.set(std::vector<std::vector<double>> {
            {1, 1, 1, 1},
            {1, 1, 1, 1},
            {1, 1, 1, 1}
    });

    Matrix mat3 = Matrix(4, 3);
    mat3.set(std::vector<std::vector<double>> {
            {2, 2, 2},
            {2, 2, 2},
            {2, 2, 2},
            {2, 2, 2}
    });

    Matrix expected1 = Matrix(4, 4);
    expected1.set(std::vector<std::vector<double>> {
            {6, 6, 6, 6},
            {6, 6, 6, 6},
            {6, 6, 6, 6},
            {6, 6, 6, 6}
    });

    Matrix expected2 = Matrix(3, 3);
    expected2.set(std::vector<std::vector<double>> {
            {8, 8, 8},
            {8, 8, 8},
            {8, 8, 8}
    });

    EXPECT_TRUE(mat3 * m3 == expected1);
    EXPECT_TRUE(m3 * mat3 == expected2);
    EXPECT_FALSE(m3 * mat3 == expected);

    EXPECT_ANY_THROW(m1 * m2);
    EXPECT_ANY_THROW(m3 * mat2);
    EXPECT_ANY_THROW(mat1 * mat3);

    //nasobeni konstantou
    EXPECT_TRUE(m2 * 3 == expected);
    EXPECT_TRUE(m2 * 8 == expected2);
    EXPECT_TRUE(expected2 * 0.125 == m2);
    EXPECT_FALSE(mat2 * 3 == mat2);
    EXPECT_FALSE(m2 * 0.6 == m2);


}

TEST(OperationsTests, EquationFaults) {

    //spatny pocet prvku

    Matrix m1{};

    EXPECT_ANY_THROW(m1.solveEquation(std::vector<double>{}));
    EXPECT_ANY_THROW(m1.solveEquation(std::vector<double>(3, 3)));

    //matice neni ctvercova

    Matrix m2 = Matrix(2, 3);
    m2.set(std::vector<std::vector<double>>{
            {2, 3, 4},
            {3, 2, 1}
    });

    Matrix m3 = Matrix(3, 2);
    m2.set(std::vector<std::vector<double>>{
            {2, 3},
            {3, 1},
            {2, 1}
    });

    EXPECT_ANY_THROW(m2.solveEquation(std::vector<double>{3, 3, 3}));
    EXPECT_ANY_THROW(m3.solveEquation(std::vector<double>{3, 3}));

    //matice je singularni

    Matrix m4 = Matrix(2, 2);
    m4.set(std::vector<std::vector<double>>{
            {2, 3},
            {4, 6}
    });

    EXPECT_ANY_THROW(m4.solveEquation(std::vector<double>{3, 3}));
    EXPECT_ANY_THROW(m4.solveEquation(std::vector<double>(2, 2)));
}

TEST(OperationsTests, Equation) {

    Matrix m1{};
    m1.set(0, 0, 2);

    EXPECT_TRUE(m1.solveEquation(std::vector<double> {2}) == (std::vector<double> {1}));

    Matrix m2 = Matrix(2, 2);
    m2.set(std::vector<std::vector<double>> {
            {2, 2},
            {4, 6}
    });

    EXPECT_TRUE(m2.solveEquation(std::vector<double> {4, 10}) == (std::vector<double> {1, 1}));

    Matrix m3 = Matrix(3, 3);
    m3.set(std::vector<std::vector<double>> {
            {2, 3, 4},
            {3, 1, 3},
            {2, 1, 2}
    });

    EXPECT_TRUE(m3.solveEquation(std::vector<double> {9, 7, 5}) == (std::vector<double> {1, 1, 1}));

    Matrix m4 = Matrix(4, 4);
    m4.set(std::vector<std::vector<double>> {
            {2, 3, 4, 0},
            {3, 1, 3, 0},
            {2, 1, 2, 0},
            {0, 0, 0, 1}
    });
    EXPECT_TRUE(m4.solveEquation(std::vector<double> {9, 7, 5, 1}) == (std::vector<double> {1, 1, 1, 1}));

    Matrix m5 = Matrix(5, 5);
    m5.set(std::vector<std::vector<double>> {
            {2, 3, 4, 0, 0},
            {3, 1, 3, 0, 0},
            {2, 1, 2, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1}
    });

    EXPECT_TRUE(m5.solveEquation(std::vector<double> {9, 7, 5, 1, 1}) == (std::vector<double> {1, 1, 1, 1, 1}));

    Matrix m6 = Matrix(6, 6);
    m6.set(std::vector<std::vector<double>> {
            {2, 0, 0, 0, 0, 0},
            {3, 1, 0, 0, 0, 0},
            {2, 1, 2, 0, 0, 0},
            {1, 2, 3, 1, 0, 0},
            {5, 4, 3, 6, 1, 0},
            {2, 3, 1, 5, 3, 2}
    });

    EXPECT_TRUE(m6.solveEquation(std::vector<double> {2, 4, 5, 7, 19, 16}) == (std::vector<double> {1, 1, 1, 1, 1, 1}));
}

TEST(OperationsTests, Transpose) {

    Matrix m1{};
    EXPECT_TRUE(m1.transpose() == m1);

    Matrix m2 = Matrix(2, 2);
    m2.set(std::vector<std::vector<double>>{
            {2, 4},
            {3, 2}
    });

    Matrix mat2 = Matrix(2, 2);
    mat2.set(std::vector<std::vector<double>>{
            {2, 3},
            {4, 2}
    });

    EXPECT_TRUE(m2.transpose() == mat2);

    Matrix m3 = Matrix(3, 3);
    m3.set(std::vector<std::vector<double>> {
            {2, 3, 4},
            {3, 1, 3},
            {2, 1, 2}
    });

    Matrix mat3 = Matrix(3, 3);
    mat3.set(std::vector<std::vector<double>> {
            {2, 3, 2},
            {3, 1, 1},
            {4, 3, 2}
    });

    EXPECT_TRUE(m3.transpose() == mat3);

    Matrix m4 = Matrix(2, 3);
    m4.set(std::vector<std::vector<double>>{
            {2, 3, 4},
            {3, 2, 1}
    });

    Matrix mat4 = Matrix(3, 2);
    mat4.set(std::vector<std::vector<double>>{
            {2, 3},
            {3, 2},
            {4, 1}
    });

    EXPECT_TRUE(m4.transpose() == mat4);

}

TEST(OperationsTests, InverseFaults) {

    //chyba singularni matice
    Matrix m1 = Matrix(3, 3);
    m1.set(std::vector<std::vector<double>>{
            {1, 2, 3},
            {2, 4, 6},
            {3, 6, 9}
    });
    EXPECT_ANY_THROW(m1.inverse());

    Matrix m2 = Matrix(2, 2);
    m2.set(std::vector<std::vector<double>>{
            {3, 6},
            {1, 2}
    });
    EXPECT_ANY_THROW(m2.inverse());

    //chyba velikost jina nez dva nebo tri
    Matrix m3{};
    EXPECT_ANY_THROW(m3.inverse());

    Matrix m4 = Matrix(4, 4);
    m4.set(std::vector<std::vector<double>> {
            {2, 3, 4, 0},
            {3, 1, 3, 0},
            {2, 1, 2, 0},
            {0, 0, 0, 1}
    });
    EXPECT_ANY_THROW(m4.inverse());

    Matrix m5 = Matrix(5, 5);
    m5.set(std::vector<std::vector<double>> {
            {2, 3, 4, 0, 0},
            {3, 1, 3, 0, 0},
            {2, 1, 2, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1}
    });
    EXPECT_ANY_THROW(m5.inverse());

    Matrix m6 = Matrix(6, 6);
    m6.set(std::vector<std::vector<double>> {
            {2, 0, 0, 0, 0, 0},
            {3, 1, 0, 0, 0, 0},
            {2, 1, 2, 0, 0, 0},
            {1, 2, 3, 1, 0, 0},
            {5, 4, 3, 6, 1, 0},
            {2, 3, 1, 5, 3, 2}
    });
    EXPECT_ANY_THROW(m6.inverse());

}

TEST(OperationsTests, Inverse) {

    Matrix m1 = Matrix(3, 3);
    m1.set(std::vector<std::vector<double>>{
            {2, 3, 4},
            {3, 1, 3},
            {2, 1, 2}
    });

    Matrix mat1 = Matrix(3, 3);
    mat1.set(std::vector<std::vector<double>>{
            {-0.5, -1, 2.5},
            {0, -2, 3},
            {0.5, 2, -3.5}
    });

    EXPECT_TRUE(m1.inverse() == mat1);

    Matrix m2 = Matrix(2, 2);
    m2.set(std::vector<std::vector<double>>{
            {3, 5},
            {1, 2}
    });

    Matrix mat2 = Matrix(2, 2);
    mat2.set(std::vector<std::vector<double>>{
            {2, -5},
            {-1, 3}
    });

    EXPECT_TRUE(m2.inverse() == mat2);

    Matrix m3 = Matrix(3, 3);
    m3.set(std::vector<std::vector<double>>{
            {2, 3, 3},
            {3, 1, 3},
            {2, 1, 2}
    });

    Matrix mat3 = Matrix(3, 3);
    mat3.set(std::vector<std::vector<double>>{
            {-1, -3, 6},
            {0, -2, 3},
            {1, 4, -7}
    });

    EXPECT_TRUE(m3.inverse() == mat3);

    Matrix m4 = Matrix(2, 2);
    m4.set(std::vector<std::vector<double>>{
            {2, 6},
            {1, 4}
    });

    Matrix mat4 = Matrix(2, 2);
    mat4.set(std::vector<std::vector<double>>{
            {2, -3},
            {-0.5, 1}
    });

    EXPECT_TRUE(m4.inverse() == mat4);

}
/*** Konec souboru white_box_tests.cpp ***/
