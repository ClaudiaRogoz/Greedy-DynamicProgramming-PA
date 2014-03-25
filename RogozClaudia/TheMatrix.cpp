#include "TheMatrix.h"

using namespace std;

/*constructor
 * initializeaza campurile cu datele citite*/
TheMatrix::TheMatrix(int n, int m, int K){
	N = n;
	M = m;
	k = K;

    /*construirea unei matrici cu 1 pe prima linie, 
     *si 1 deasupra diagonalei principale */
	matrix = new int*[k+1];
       for (int i = 0; i< k+1; i++){
                matrix[i] = new int[k+1];
                if(i != k)
			matrix[i][i+1] = 1;
                matrix[i][0] = 1;
        }
}

/*destructor se dezaloca spatiul rezervat matricei matrix*/
TheMatrix::~TheMatrix(){	
	for (int i = 0; i < k+1; i++)
    		delete[] matrix[i];
	delete[] matrix;
}

/*algoritmul de programare dinamic care construieste numarul
 * total "sum" cu ajutorul matricei "matrix"*/
void TheMatrix::dynamicProgrammingSum(){
	ofstream file("date.out");
	int** a;
	
    /*matricea matrix este ridicata la puterea N*/
    a  = expBySquaringMatrix(matrix,N);

    /*numarul total este dat de suma de pe prima linie a matricii*/
	int sum = 0;
	for (int i = 0; i< k+1 ; i++){
		 sum = sum + a[0][i];
         /*se verifica daca numarul depaseste pragul sperior MODULO*/
		if (sum >=MODULO)
			sum = sum %MODULO;
	}
	if(sum >=MODULO)
		sum = sum %MODULO;

    /*rezultatul final este reprezentat de ridicarea numarului
     * obtinut "sum" (pentru N linii si 1 coloana) la numarul de coloane
     * dorit --> M*/
	file<<expBySquaring(sum ,M);
	file.close();
}

/*inmultirea a 2 matrici complexitate: O((k+1)^3)*/
int** TheMatrix::multiply(int** a, int** b){

    /*rezultatul inmultirii a 2 matrici*/
	int** c = new int*[k+1];
	for (int i = 0; i< k+1; i++)
		c[i] = new int[k+1];

    /*construirea propriu-zisa a matricii si verificarea 
     * daca depaseste limita superioara MODULO */
	for (int i = 0; i< k+1; i++)
		for (int j = 0; j<k+1; j++){
			c[i][j] = 0;
			for (int m = 0; m< k+1; m++){
				c[i][j] = c[i][j] + (a[i][m] *b[m][j]);
				if(c[i][j] >= MODULO)
					c[i][j] = c[i][j] %MODULO;						
			}
		}
	

	return c;
}

/*ridicarea la putere a lui "a" la "n" 
 * complexitate O(log(n))
 * formula: x^n = (x^2) ^(n/2)          pentru n =par
 *              = x*(x^2)^((n-1)/2)     pentru n = impar*/
int TheMatrix::expBySquaring(int a, int n){
	
    /*coditia de iesire din recursivitate*/
	if (n == 1) return a;
	else{	
        /*daca n este par*/
        if(n%2 == 0){
		long long int x = pow(expBySquaring(a,n/2),2);
		if(x >= MODULO)
			return x%MODULO;
		else return x;
		}
		else{
        /*daca n este impar*/
		long long int y = (a * pow(expBySquaring(a,(n-1)/2),2));
		if(y >= MODULO)
			return y%MODULO;
		else return y;
		}
	}	
}

/*algoritmul de ridicare a matricei "m" la puterea "n"
 * algoritmul este similar lui "expBySquaring
 * cu diferenta ca se apeleaza metoda multiply in loc de pow"
 * complexitate: O(log(n))*/
int** TheMatrix::expBySquaringMatrix(int** m, int n){
	
	if (n == 1) return m;	
	
	int** aux = expBySquaringMatrix(m, n/2);
	if(n%2 != 0)
		{
		int** m1 = multiply(aux, aux);
		return  multiply(m1,m);
		
		}
		else{
			int** m2 = multiply(aux, aux);
			return m2;
		}
}

/*entry point */
int main(int argc, char** argv){

	/*citirea datelor din fisierul de intrare*/
    ifstream file("date.in");
	string str;
	int n, m, k;
	
		
	if(file.is_open()){
		file>>n>>m>>k;
		/*instantierea clasei si initializarea campurilor*/
        TheMatrix Matrix(n,m,k);
		Matrix.dynamicProgrammingSum();
		file.close();
	}
	
	else cout<<"Nu se poate deschide fisierul";
	file.close();
	return 0;
}
