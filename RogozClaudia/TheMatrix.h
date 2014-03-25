#ifndef _THE_MATRIX_H
#define _THE_MATRIX_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>


#define MODULO 40009


class TheMatrix{
	

	public:
		
		int N, M, k, sum;
		
        /*matricea de construire a solutiei (k+1)*(k+1)*/
		int** matrix;

		TheMatrix(int N, int M, int k);
		~TheMatrix();
        
        /*citeste datele din fisier*/
		void readFile();

        /*algoritmul de programare dinamica
         * pentru construirea matricei*/
		void dynamicProgrammingSum();

        /*metoda recursiva care ridica un numar a la puterea n*/
		int expBySquaring(int a, int n);

        /*metoda recursiva care ridica o matrice a la puterea n*/
		int** expBySquarigMatrix(int** a, int n);

        /*inmultirea a 2 matrici a*b*/
		int** multiply(int** a, int** b);

        /*scrie datele in fisier*/
		void writeFile();

		int** expBySquaringMatrix(int** m, int n);

};
#endif
