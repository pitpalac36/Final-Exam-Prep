#include "Matrice.h"
#include <exception>
using namespace std;


// theta(1)
Matrice::Matrice(int linii, int coloane) {
	dimensiune = 0;
	capacitate = 10;
	matrice = new triplet[10];
	this->linii = linii;
	this->coloane = coloane;
}


// theta(1)
int Matrice::nrLinii() const {
	return this->linii;
}


// theta(1)
int Matrice::nrColoane() const {
	return this->coloane;	
}


// O(dimensiune)
TElem Matrice::element(int i, int j) const {
	if (i < 0 || i >= this->linii || j<0 || j>this->coloane)
	{
		throw std::exception("exceptie");
	}
	for (int k = 0; k < capacitate; k++)
		if ((matrice[k].linie == i) && (matrice[k].coloana == j))
			return matrice[k].valoare;
	return NULL_TELEMENT;
}


// CF - modificarea ultimului element => theta(1)
// CD - adaugarea unui element pe prima pozitie (dupa mutarea tuturor celorlalte cu o pozitie 
// la dreapta) => theta(n)
// overall : O(dimensiune)
TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || i >= this->linii || j<0 || j>this->coloane)
		throw std::exception("exceptie");
	if (dimensiune == capacitate)
		redimensioneaza();
	int index = 0;
	for (int k = dimensiune- 1; k >= 0; k--) {
			if (matrice[k].linie == i && matrice[k].coloana == j) { // modificare
				TElem val = matrice[k].valoare;
				matrice[k].valoare = e;
				return val;
			}
			else { // adaugare
				if ((matrice[k].linie > i) || ((matrice[k].linie == i && matrice[k].coloana > j)&&(matrice[k].coloana!=-1))) {
					// a fost gasita pozitia pe care se va insera elementul
					index = k;
					matrice[k + 1] = matrice[k];
					break;
				}
				matrice[k + 1] = matrice[k];
					
				
			}
	}
	matrice[index].linie = i;
	matrice[index].coloana = j;
	matrice[index].valoare = e;
	dimensiune++;
	return NULL_TELEMENT;
}


// theta(n)
void Matrice:: redimensioneaza() {
	triplet* aux = new triplet[capacitate + 5];
	for (int i = 0; i < dimensiune; i++)
		aux[i] = matrice[i];
	delete[] matrice;
	matrice = aux;
	capacitate = capacitate + 5;
}
