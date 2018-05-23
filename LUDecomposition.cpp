/*
 * File:   LUDecomposition.cpp
 * Author: André Savioli
 *
 * Created on 17 de Outubro de 2014, 13:37
 */

#include "LUDecomposition.h"

// Public

LUDecomposition::LUDecomposition() {}

LUDecomposition::LUDecomposition( int m, int n ) {

    this->m = m;

    this->n = n;

    this->solved = false;

    this->initializeMatrix();

}

void LUDecomposition::setMatrixM( int m ) {

    this->m = m;

}

void LUDecomposition::setMatrixN( int n ) {

    this->n = n;

}

void LUDecomposition::setCell( int m, int n, float p ) {

    this->matrix[ m ][ n ] = p;

}

float LUDecomposition::getCellValue( int m, int n ) {

    return this->matrix[ m ][ n ];

}

void LUDecomposition::printMatrix() {

    for( int l = 0; l < this->m; l++ ) {

        for( int c = 0; c < this->n; c++ )
            cout << matrix[ l ][ c ] << " ";

        cout << endl;

    }

}

void LUDecomposition::factor() {

    this->upperTriangularMatrix();

    this->solveLy();

    this->solveUx();

    this->solved = true;

}

void LUDecomposition::printSolutionLy() {

    if( this->solved ) {

        for( int i = 0; i < this->m; i++ )
            cout << "y" << i << " = "  <<  this->multipliers[ i ][ this->n - 1 ] << endl;

    } else {

        cout << "Not processed yet.";

    }

}

void LUDecomposition::printSolutionUx() {

    if( this->solved ) {

        for( int i = 0; i < this->m; i++ )
            cout << "x" << i << " = "  <<  this->matrix[ i ][ this->n - 1 ] << endl;

    } else {

        cout << "Not processed yet.";

    }

}

LUDecomposition::~LUDecomposition() {

    for( int i = 0; i < this->m; i++ )
        delete [] this->matrix[ i ];

    delete [] this->matrix;

    for( int i = 0; i < this->m; i++ )
        delete [] this->multipliers[ i ];

    delete [] this->multipliers;

}

// Private

void LUDecomposition::initializeMatrix() {

    this->matrix = new float * [ this->m ];

    for( int i = 0; i < this->m; i++ ) {

        this->matrix[ i ] = new float[ this->n ];

    }

    // Multipliers

    this->multipliers = new float * [ this->m ];

    for( int i = 0; i < this->m; i++ ) {

        this->multipliers[ i ] = new float[ this->n ];

    }

}

void LUDecomposition::solveLy() {

    for( int i = 0; i < this->m; i++ )
        this->multipliers[ i ][ this->n - 1 ] = this->matrix[ i ][ this->n - 1 ];

    float r;

    for( int x = 0; x < this->m; x++ ) {

        r = multipliers[ x ][ this->n - 1 ];

        for( int c = 0; c < this->n - 2; c++ ) {

            if( x == c ) {

                r = r / multipliers[ x ][ c ];

                multipliers[ x ][ this->n - 1 ] = r;

                for( int l = 0; l <  this->n - 1; l++) {

                    multipliers[ l ][ c ] = multipliers[ l ][ c ] * r;

                }

                multipliers[ x ][ c ] = 1;

                break;

            } else {

                r = r - multipliers[ x ][ c ];

                multipliers[ x ][ c ] = 0;

            }

        }

        this->multipliers[ x ][ this->n - 1 ] = r;

    }

}

void LUDecomposition::solveUx() {

    for( int i = 0; i < this->m; i++ )
        this->matrix[ i ][ this->n - 1 ] = this->multipliers[ i ][ this->n - 1 ];

    float r;

    for( int x = this->m - 1; x >= 0; x-- ) {

        r = matrix[ x ][ this->n - 1 ];

        for( int c = this->n - 2; c >= 0; c-- ) {

            if( x == c ) {

                r = r / matrix[ x ][ c ];

                matrix[ x ][ this->n - 1] = r;

                for( int l = x - 1; l >= 0; l-- ) {

                    matrix[ l ][ c ] = matrix[ l ][ c ] * r;

                }

                matrix[ x ][ c ] = 1;

                break;


            } else {

                r = r - matrix[ x ][ c ];

                matrix[ x ][ c ] = 0;

            }

        }

        this->matrix[ x ][ this->n - 1 ] = r;

    }

}

void LUDecomposition::upperTriangularMatrix() {

    this->operationLine = 0;

    this->operationColumn = 0;

    float m = 0;

    for( int x = this->operationLine + 1; x < this->m; x++ ) {

        this->pivoting();

        m = 0;

        for( int l = this->operationLine + 1; l < this->m; l++ ) {

            m = this->matrix [ l ] [ this->operationColumn ] / this->matrix[ this->operationLine ] [ this->operationColumn ];

            this->multipliers[ l ][ this->operationColumn ] = m;

            for( int c = this->operationColumn; c < this->n-1; c++ )
                this->matrix[ l ] [ c ] = this->matrix[ l ] [ c ] - ( m * this->matrix[ this->operationLine ] [ c ] );

        }

        this->operationLine++;

        this->operationColumn++;

    }

    for( int i = 0; i < this->m; i++ )
        this->multipliers[ i ][ i ] = 1;

    this->operationLine = 0;

    this->operationColumn = 0;

}

void LUDecomposition::pivoting() {

    float value = abs( this->matrix[ this->operationLine ][ this->operationColumn ] );

    int swapLine = this->operationLine;

    for( int x = this->operationLine + 1; x < this->m ; x++ ) {

        if( abs( this->matrix[ x ][ this->operationColumn ] ) > value ){

            swapLine = x;

            value = abs( this->matrix[ x ][ this->operationColumn ] );

        }

    }

    if( this->operationLine != swapLine )
        this->exchangeLine( this->operationLine, swapLine );

}

void LUDecomposition::exchangeLine( int a, int b ) {

    float aux;

    for( int x = this->operationColumn; x < this->n; x++ ) {

        aux = this->matrix[ a ][ x ];

        this->matrix[ a ][ x ] = this->matrix[ b ][ x ];

        this->matrix[ b ][ x ] = aux;

    }

}
