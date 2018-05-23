/*
 * File:   main.cpp
 * Author: André Savioli
 *
 * Created on 17 de Outubro de 2014, 13:28
 */

#include <cstdlib>
#include <iostream>

#include "LUDecomposition.h"

using namespace std;

int main( int argc, char** argv ) {

    // LU Decomposition

    cout << endl << "LU Decomposition" << endl << endl << endl;

    LUDecomposition * lu = new LUDecomposition( 3, 4 );

    /**
    *   Example System 1:
    *
    *   5,0 x1 + 1,0 x2 – 2,0 x3 = 10
    *   3,0 x1 – 9,4 x2 + 1,8 x3 = 22
    *   1,0 x1 + 2,2 x2 + 4,6 x3 = 10
    *
    *   Solution:
    *
    *   x1 =  3
    *   x2 = -1
    *   x3 =  2
    *
    */

    lu->setCell( 0, 0, 5 );
    lu->setCell( 0, 1, 1 );
    lu->setCell( 0, 2, -2 );
    lu->setCell( 0, 3, 10 );

    lu->setCell( 1, 0, 3 );
    lu->setCell( 1, 1, -9.4 );
    lu->setCell( 1, 2, 1.8 );
    lu->setCell( 1, 3, 22 );

    lu->setCell( 2, 0, 1 );
    lu->setCell( 2, 1, 2.2 );
    lu->setCell( 2, 2, 4.6 );
    lu->setCell( 2, 3, 10 );

    cout << "Matrix System" << endl << endl;

    lu->printMatrix();

    cout << endl << endl;

    lu->factor();

    cout << "Solution of Ly = b" << endl << endl;

    lu->printSolutionLy();

    cout << endl << endl;

    cout << "Solution of Ux = b" << endl << endl;

    lu->printSolutionUx();

    cout << endl << endl;

    delete lu;

    return 0;

}
