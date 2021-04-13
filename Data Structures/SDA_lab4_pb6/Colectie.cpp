#include "Colectie.h"
#include <exception>

bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

/*
  theta(2 * cp)
*/
void Colectie::redimensioneaza()
{
	// realocare vectori (redimensionare + copiere elemente)
	TElem* nouE = new TElem[cp * 2];
	int* nouUrm = new int[cp * 2];
	int* nouPrec = new int[cp * 2];
	for (int i = 0; i < cp; i++) {
		nouE[i] = e[i];
		nouUrm[i] = urm[i];
		nouPrec[i] = prec[i];
	}
	delete[] urm;
	delete[] prec;
	delete[] e;
	e = nouE;
	urm = nouUrm;
	prec = nouPrec;
	// redimensionarea spatiului liber
	for (int i = cp; i <= 2 * cp - 2; i++)
		urm[i] = i + 1;
	urm[2 * cp - 1] = -1;
	primLiber = cp;
	cp = cp * 2;
}

/*
  theta(1)
*/
int Colectie::aloca()
{
	//se sterge primul element din lista spatiului liber
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

/*
  theta(1)
*/
void Colectie::dealoca(int i)
{
	// se trece pozitia i in lista spatiului liber pe prima pozitie
	urm[i] = primLiber;
	primLiber = i;
}


/*
  theta(2 * cp)
*/
int Colectie::creeazaNod(TElem elem)
{
	if (primLiber == -1 && dimensiune != 0)
		redimensioneaza();
	int i = aloca();
	e[i] = elem;
	urm[i] = -1;
	prec[i] = -1;
	return i;
}

/*
  theta(1)
*/
Colectie::Colectie()
{
	cp = 100;
	dimensiune = 0;
	e = new TElem[cp];
	urm = new int[cp];
	prec = new int[cp];
	prim = -1;
	ultim = -1;
	//se initializeaza lista spatiului liber - toate pozitiile din vector sunt marcate ca fiind libere
	for (int i = 0; i < cp - 1; i++) {
		urm[i] = i + 1;
	}
	for (int i = cp - 2; i >= 0; i--) {
		prec[i + 1] = i;
	}
	urm[cp - 1] = -1;
	//referinta spre prima pozitie libera din lista
	primLiber = 0;
}

/*
  CF : theta(1) -> adaugarea primului element / inaintea primului element
  CD : theta(n) -> adaugarea dupa ultim   (n - dimensiunea colectiei)
  CM : O(n)
*/
void Colectie::adauga(TElem elem)
{
	// adaugarea primului element
	if (prim == -1) {
		int i = creeazaNod(elem);
		prim = i;
		urm[i] = -1;
		prec[i] = -1;
		ultim = prim;
		dimensiune++;
		return;
	}
	// adaugare inaintea primului element
	if (rel(elem, e[prim])) {
		int i = creeazaNod(elem);
		urm[i] = prim;
		prec[prim] = i;
		prim = i;
	}
	else {
		int curent = prim;
		while (rel(e[curent], elem) && curent != ultim)
			curent = urm[curent];

		// adaugare inainte de curent
		if (!rel(e[curent], elem)) {
			int i = creeazaNod(elem);
			prec[i] = prec[curent];
			urm[prec[curent]] = i;
			urm[i] = curent;
			prec[curent] = i;
		}

		// adaugare dupa ultim
		else {
			int i = creeazaNod(elem);
			prec[i] = curent;
			urm[curent] = i;
			ultim = i;
			urm[ultim] = -1;
		}
	}
	dimensiune++;
}

/*
  CF : theta(1) -> se sterge primul element
  CD : theta(n) -> se sterge ultimul element / elementul cautat nu exista
  CM : O(n)
*/
bool Colectie::sterge(TElem elem)
{
	int curent = prim;
	while (curent != urm[ultim] && e[curent] != elem) {
		//if (!rel(e[curent], elem))
			//return false;
		curent = urm[curent];
		
	}
	if (curent == urm[ultim])
		return false;
	int precedent = prec[curent];
	int urmator = urm[curent];
	if (curent == ultim) {
		ultim = precedent;
		if (ultim == -1)   // se sterge unicul element
			prim = -1;
	}
	else {
		if (curent == prim) {
			prim = urmator;
		}
		if (precedent != -1)
			urm[precedent] = urmator;
		if (urmator != -1)
			prec[urmator] = precedent;
		dealoca(curent);
	}
	dimensiune--;
	return true;
}

/*
  CF : theta(1) -> se cauta primul element / elementul cautat nu exista si rel(elem, prim)
  CD : theta(n) -> se cauta ultimul element / elementul cautat nu exista si rel(ultim, elem)
  CM : O(n)
*/
bool Colectie::cauta(TElem elem) const
{
	int p = prim;
	while (p != urm[ultim] && rel(e[p], elem)) {
		if (elem == e[p])
			return true;
		p = urm[p];
	}
	return false;
}

/*
  CF : theta(1) -> elem = prim si apare o singura data / elementul cautat nu exista si rel(elem, prim)
  CD : theta(n) -> elem = ultim si apare de mai multe ori
  CM : O(n)
*/
int Colectie::nrAparitii(TElem elem) const
{
	int aparitii = 0;
	int p = prim;
		while (p != urm[ultim]) {
			if (elem == e[p])
				aparitii++;
			if (!rel(e[p], elem))
				return aparitii;
			p = urm[p];
		}
	return aparitii;
}

/*
  theta(1)
*/
int Colectie::dim() const
{
	return dimensiune;
}

/*
  theta(1)
*/
bool Colectie::vida() const
{
	return dimensiune == 0;
}


/*
	CF : elem este primul element din lista si apare o singura data => theta(1)
	CD : elem este ultimul element din lista si apare de mai multe ori => theta(n)
*/
int Colectie::eliminaAparitii(int nr, TElem elem)
{
	if (nr < 0)
		throw std::exception("nr este invalid!");
	int curent = prim;
	while (curent != urm[ultim] && e[curent] != elem) {
		if (!rel(e[curent], elem))
			return 0;
		curent = urm[curent];
	}
	if (curent == urm[ultim])  // elementul nu exista in vectorul e
		return 0;
	// e[curent] este acum primul element din vectorul e egal cu elem
	int primEgal = curent;
	if (primEgal == ultim) {
		urm[prec[ultim]] = -1;
		ultim = urm[prec[ultim]];
		dealoca(primEgal);
		dimensiune--;
		return 1;
	}
	while (e[curent] == elem && curent != urm[ultim] && nr > 0) {
		curent = urm[curent];
		nr--;
	}	
	for (int i = primEgal; i < curent; i++) {
		if (prec[i] != -1)
			urm[prec[i]] = urm[i];
		if (urm[i] != -1)
			prec[urm[i]] = prec[i];
		dealoca(i);
		dimensiune--;
	}
	if (primEgal == prim) {
		prim = curent;
	}
	if (curent == urm[ultim]) { // toate elementele incepand cu primEgal sunt egale cu elem
		ultim = prec[primEgal];
		urm[prec[primEgal]] = ultim;
	}
	return curent - primEgal;
}

/*
  theta(1)
*/
IteratorColectie Colectie::iterator() const
{
	return IteratorColectie(*this);
}

/*
  theta(1)
*/
Colectie::~Colectie()
{
	delete[] urm;
	delete[] prec;
	delete[] e;
}
