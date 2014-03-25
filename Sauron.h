#ifndef _SAURION_H
#define _SAURION_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <string.h>
#include <cstdlib>

class Sauron{
	public:
		/*numarul de perechi 2*N*/
		int N2;
		
		/*array cu numarul de victime
		masterKill pentru stapani
		slaveKKill pentru sclavi*/
		int* masterKill;
		int* slaveKill;
		
		/*indecsii noilor perechi sclav-stapan*/
		int* idxMasterSol;
		int* idxSlaveSol;
		
		Sauron(int n);
		~Sauron();
		
		/*construieste salariul minim*/
		void computeWage(int i, int s);
		
		/*citeste datele din fisier*/
		void readFile();
		
		/*algoritmul propiu-zis de 
		construire ale noilor perechi*/
		void computeGreedySolution();
};

#endif
