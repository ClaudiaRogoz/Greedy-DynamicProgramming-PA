
#include "Sauron.h"

using namespace std;

/*constructor
initializeaza variabile declarate in header*/
Sauron::Sauron(int n){
	
	N2 = n;	
	masterKill = new int[n];
	slaveKill = new int[n];
	
	idxMasterSol = new int[n/2];
	idxSlaveSol = new int[n/2];
}

/*destructor
dezaloca vectorii folositi*/
Sauron::~Sauron(){

	delete[] masterKill;
	delete[] slaveKill;
	delete[] idxMasterSol;
	delete[] idxSlaveSol;
}

/*functie recursiva care calculeaza pe parcurs suma
dar si face afisarea in fisierul de iesire
m-am folosit de tail call optimisation*/
void Sauron::computeWage(int i, int sum){
	static ofstream file("date.out");
	
	if(i < 0){
		file<<sum<<"\n";
		return;
		}
	else{
		computeWage(i-1,sum + masterKill[idxMasterSol[i]] + slaveKill[idxSlaveSol[i]]);

		 file<<idxMasterSol[i]+1<<" "<<idxSlaveSol[i]+1<<"\n";
	}
	
}

/*algoritmul propriu-zis care presupune construirea noilor
perechi prin intermediul celor doi vectori idxSlaveSol, idxMasterSol
Algoritmul ales este Greedy, astfel ca in fiecare moment perechile
sunt construite astfel incat sa indeplineasca un minim local*/
void Sauron::computeGreedySolution(){
	
	/*initializare solutie partiala Greedy*/
	idxMasterSol[0] = 1;
	idxSlaveSol[0] = 0;
	
	/*vector de indecsi care indica pozitia pe care se afla
	MasterSlave-ul in cadrul lui idxMasterSol
	de ex: hashIndex[i] = k unde hashIndex[k] = i */
	int* hashIndex = new int[N2]; 
	
	/*variabile ajutatoare temporare*/
	int diff, tempMaster, tempSlave;
	int k,i, aux;
	
	/*se parcurg cei 2 vector masterKill, slaveKill
	luandu-se initial ca perechi 2 cate 2*/
	for (i = 2; i< N2;){
		diff = -1;
		k = 0;	
		/*se parcurge vectorul de idxmasterSol construit pana la momentul
		curent; se verifica daca exista o combinatie mai buna 
		slave curent cu masterii din idxMasterSol
		sau 
		master curent cu slave-ii corespunzatori midxMasterSol
		Acest lucru se face prin verificarea diferentei intre combinatii */
		while(idxMasterSol[k] != 0) {
			
			int sumRight = slaveKill[i] + masterKill[idxMasterSol[k]];
			int sumLeft = slaveKill[idxMasterSol[k]] + masterKill[i];
			
			/*daca combinatia cu sclavul curent nu ar fi cea mai mica*/
			if(sumRight > sumLeft)
			{
			/*se observa daca minimizarea este maxima posibil local*/
			if (diff < abs(sumLeft - sumRight))
				{
				/*se updateaza maxmizarea */
				diff = abs(sumLeft - sumRight);
				
				/*se updateaza vectorul de indecsi*/
				tempMaster = i;
				tempSlave = idxMasterSol[k];
				}

			}
			k++;
		}

		/*daca s-au facut schimbari se updateaza hashIndexx-ul*/
		if (diff != -1){
			aux = hashIndex[tempSlave];
			idxMasterSol[hashIndex[tempSlave]] = tempMaster;
			idxSlaveSol[k] = tempSlave;
			hashIndex[tempSlave] = -1;
			hashIndex[tempMaster] = aux;	
		}
		else {
			/*daca toate conditiile de minimizare sunt indeplinite
			sclavul este pus in solutia partiala idxSlaveSol*/
			idxSlaveSol[k] = i;
			
		}
		i+=2;
		
		/*continuarea algoritmul*/
		idxMasterSol[k] = i-1;
		hashIndex[i-1] = k;
	}
	delete[] hashIndex;
}

/*citire din fisierul de intrare "date.in"
datele se scriu in vectorii masterKill, slaveKill*/
void Sauron::readFile(){
	ifstream file("date.in");
	int master, slave, i;
	i = 0;
	int n;
	file>>n;
	while ( file >> master >> slave )
                {
                masterKill[i] = master;
                slaveKill[i] = slave;
                i++;
                }
	file.close();


}

/*entry point; se instantiaza clasa Sauron*/
int main(int argc, char** argv){

	ifstream file("date.in");
	string str;
	int n;

	if (file.is_open()){
		getline(file, str);
		
		n = atoi(str.c_str());
		Sauron s(n);
			
   		s.readFile(); 
		s.computeGreedySolution();
		s.computeWage(n/2-1,0);
		file.close();		
	
	}

	else cout<<"\nNu se poate deschide fisierul";
		file.close();
}
