/*
 * File:   LUDecomposition.h
 * Author: André Savioli
 *
 * Created on 17 de Outubro de 2014, 13:37
 */

#ifndef LU_DECOMPOSITION_H
#define	LU_DECOMPOSITION_H

#include <cmath>
#include <iostream>

using namespace std;

class LUDecomposition {

public:

    LUDecomposition();

    LUDecomposition( int m, int n );

    void setMatrixM( int m );

    void setMatrixN( int n );

    void setCell( int m, int n, float p );

    float getCellValue( int m, int n );

    void printMatrix();

    void factor();

    void printSolutionLy();

    void printSolutionUx();

    virtual ~LUDecomposition();

private:

    bool solved;

    int m;

    int n;

    float ** matrix;

    float ** multipliers;

    int operationLine;

    int operationColumn;

    void initializeMatrix();

    void solveLy();

    void solveUx();

    void upperTriangularMatrix();

    void pivoting();

    void exchangeLine( int a, int b );

};

#endif	/* LU_DECOMPOSITION_H */
