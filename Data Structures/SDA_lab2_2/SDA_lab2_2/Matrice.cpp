#include "Matrice.h"
#include <exception>
#include <iostream>
using namespace std;

/*
 theta(1) -> complexitate constanta
 */
Matrice::Matrice(int nrLinii, int nrColoane) {
	if (nrLinii <= 0 || nrColoane <= 0)
		throw std::exception("eroare");
	this->linii = nrLinii;
	this->coloane = nrColoane;
	this->head = new nod;
	this->head->prec = NULL;
	this->head->urm = NULL;
	this->head->info = triplet{-1,-1,0};
	this->tail = new nod;
	this->tail = this->head;
}


/*
 theta(1) -> complexitate constanta
 */
int Matrice::nrLinii() const {
	return linii;
}


/*
 theta(1) -> complexitate constanta
 */
int Matrice::nrColoane() const {
	return coloane;
}


/*
   CF : theta(1) - elementul cautat este primul din lista
   CD : theta(n) - elementul cautat nu se afla in lista iar indicii pentru linie si coloana sunt maximi
   CM : O(n)
 */
TElem Matrice::element(int i, int j) const {
	if (i < 0 || i > linii || j < 0 || j > coloane)
		throw std::exception("eroare");
	nod* aux = new nod;
	aux = head;
	while (aux != NULL) {
		if (aux->info.linie == i && aux->info.coloana == j)
			return aux->info.valoare;

		// elementele fiind ordonate dupa linie si coloana, putem prevedea inexistenta unui element cautat
		if (aux->info.linie > i || (aux->info.linie == i && aux->info.coloana > j))
			return NULL_TELEMENT;
		aux = aux->urm;
	}
	return NULL_TELEMENT;
}


/*
   CF : theta(1) - adaugarea primului element; adaugarea inaintea primului; modificarea primului element
   CD : theta(n) - adaugarea/stergerea/modificarea ultimului element
   CM : O(n)
 */
TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || i > linii || j < 0 || j > coloane)
		throw std::exception("eroare");
	if (this->head->info.valoare == 0) {  // adaugarea primului element
		this->head->info.linie = i;
		this->head->info.coloana = j;
		this->head->info.valoare = e;
		return NULL_TELEMENT;
	}
	nod* aux = new nod;
	aux = head;

	// adaugare inaintea nodului head
	if (head->info.linie > i || (head->info.linie == i && head->info.coloana > j)) {
		nod* deInserat = new nod;
		deInserat->info.linie = i;
		deInserat->info.coloana = j;
		deInserat->info.valoare = e;
		deInserat->prec = NULL;
		deInserat->urm = head;
		head->prec = deInserat;
		head = deInserat;
		tail = deInserat;
		return NULL_TELEMENT;
	}
	while (aux != NULL) {
		if (aux->info.linie == i && aux->info.coloana == j) { // modificare
			if (e == 0) { // stergere
				auto deReturnat = aux->info.valoare;
				aux->prec->urm = aux->urm;
				aux->urm->prec = aux->prec;
				delete aux;
				return deReturnat;
			}
			TElem valoareVeche = aux->info.valoare;
			aux->info.valoare = e;
			return valoareVeche;
		}

		// adaugare dupa nodul curent (aux)
		if ((aux->info.linie < i || (aux->info.linie == i && aux->info.coloana < j)) && 
			(aux->urm == NULL || (aux->urm->info.linie > i || (aux->urm->info.linie == i && aux->urm->info.coloana > j))))
	       {
			nod* deInserat = new nod;
			deInserat->info.linie = i;
			deInserat->info.coloana = j;
			deInserat->info.valoare = e;
			deInserat->prec = aux;
			deInserat->urm = aux->urm;
			aux->urm = deInserat;
			if (deInserat->urm == NULL)  // deInserat este ultimul element
				tail = deInserat;
			else
				deInserat->urm->prec = deInserat;
			return NULL_TELEMENT;
		}
		aux = aux->urm;
	}
	return NULL_TELEMENT;
}
