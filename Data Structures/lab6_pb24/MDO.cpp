#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
using namespace std;


/*
  theta(1) -> complexitate constanta
  dispersie folosind metoda inmultirii
*/
int MDO::hashFunction(TCheie cheie) const
{
	double f = cheie * 0.6180339887 - std::floor(cheie * 0.6180339887);
	return std::floor(m * f);
}


/*
  theta(1) -> complexitate constanta
*/
MDO::MDO(Relatie rel) {
	this->r = rel;
	m = 20;
	n = 0;
	tabela = new Lista * [m];
	for (int i = 0; i < m; i++) {
		tabela[i] = new Lista;
		tabela[i]->prim = nullptr;
		tabela[i]->urm = nullptr;
	}	
}


void MDO::redimensioneaza() {
	std::cout << "redimensionare\n";
	int cap_veche = m;
	m *= 2;
	Lista** T = new Lista * [m];
	for (int i = 0; i < m; i++) {
		T[i] = new Lista;
		T[i]->prim = nullptr;
		T[i]->urm = nullptr;
	}
	for (int i = 0; i < cap_veche; i++) {
		Lista* curenta = new Lista;
		curenta = tabela[i];  // prima lista de la locatia i
		while (curenta != nullptr && curenta->prim != nullptr) {
			Nod* curent = new Nod;
			curent = curenta->prim;  // primul nod din lista curenta
			int poz = hashFunction(curent->elem.first);  // locatia la care se va dispersa in T
			if (T[poz] == nullptr) {  // este prima lista dispersata la acea locatie
				T[poz] = curenta;
				curenta->urm = nullptr;
			}
			else {  // nu este prima lista dispersata la acea locatie; se cauta pozitia corespunzatoare in coliziune
				Lista* aux = new Lista;
				Lista* precAux = new Lista;
				aux = T[poz];
				while (aux->prim != nullptr && r(aux->prim->elem.first, curenta->prim->elem.first)) {
					precAux = aux;
					aux = aux->urm;
				}
				if (aux->prim == nullptr) { // adaugare pe ultima pozitie din coliziune
					aux = curenta;
					curenta->urm = nullptr;
				}
				else {  // adaugare inainte de aux
					precAux->urm = curenta;
					curenta->urm = aux;
				}
			}
		curenta = curenta->urm;
		}
	}
	delete[] tabela;
	tabela = T;
}


/*
  CF : theta(1) -> adaugarea primei liste de la locatia indicata de hashFunction
  CD : theta(n) ->  toate listele se disperseaza la locatia aceeasi locatie + 
					adaugarea se face in ultima lista din coliziunea de la acea locatie
  CM : theta(1)
*/
void MDO::adauga(TCheie c, TValoare v) {
	if (n / m > 5) {
		redimensioneaza();
	}
	n++;
	Lista* poz = new Lista;
	poz = tabela[hashFunction(c)];
	if (poz == nullptr || poz->prim == nullptr) {	// creez prima lista de la adresa respectiva
		Lista* l = new Lista;
		Nod* nou = new Nod;
		nou->urm = nullptr;
		nou->elem = { c,v };
		l->prim = nou;
		l->urm = nullptr;
		tabela[hashFunction(c)] = l;
		return;
	}
	else {
		while(poz!= nullptr && poz->prim->elem.first != c && r(poz->prim->elem.first, c)) 	// parcurg lista de coliziuni pana cand dau de cheie 
			poz = poz->urm;

		if (poz == nullptr) { // nu exista lista pt cheia respectiva; creez si adaug lista noua pe pozitia corespunzatoare
			Lista* l = new Lista;
			Nod* nou = new Nod;
			nou->elem = { c,v };
			nou->urm = nullptr;
			l->prim = nou;
			l->urm = tabela[hashFunction(c)];
			tabela[hashFunction(c)] = l;
		}
		else {  // s-a ajuns la cheie
			Nod* nou = new Nod;
			nou->elem = { c,v };
			nou->urm = poz->prim;
			poz->prim = nou;
		}
	}
}


/*
  CF : theta(1) -> lista cheii cautate este prima de la locatia indicata de hashFunction
  CD : theta(n) ->  toate listele se disperseaza la aceeasi locatie + lista cheii cautate este ultima de la acea locatie
  CM : theta(1)
*/
vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> deReturnat{};
	Lista* poz = tabela[hashFunction(c)];
	while (poz->urm != nullptr && r(poz->prim->elem.first, c))
		poz = poz->urm;
	if (poz == nullptr || poz->prim == nullptr)
		return deReturnat;
	if (poz->prim->elem.first == c) {
		auto aux = poz->prim;
		while (aux != nullptr) {
			deReturnat.push_back(aux->elem.second);
			aux = aux->urm;
		}
	}
	return deReturnat;
}


/*
  CF : theta(1) -> se sterge primul nod din prima lista de la locatia indicata de hashFunction
  CD : theta(n) -> toate listele se disperseaza la aceeasi locatie +
				   lista cheii cautate este ultima de la acea locatie si perechea este ultima din acea lista
  CM : theta(1)
*/
bool MDO::sterge(TCheie c, TValoare v) {
	Lista* poz = tabela[hashFunction(c)];
	while (poz->prim != nullptr)
		if (poz->prim->elem.first != c)
			poz = poz->urm;
		else break;
	if (poz->prim == nullptr)
		return false;
	if (poz->prim->elem.first == c) {
		auto aux1 = poz->prim;
		auto aux2 = poz->prim->urm;
		if (aux1->elem.second == v) {  // stergerea primului nod din lista
			poz->prim = aux2;
			delete aux1;
			n--;
			return true;
		}
		else {
			if (aux2 == nullptr)
				return false;
			while (aux2->elem.second != v && aux2->urm != nullptr) {
				aux1 = aux1->urm;
				aux2 = aux1->urm;
			}
			if (aux2->urm == nullptr && aux2->elem.second != v)	// nu a fost gasita valoarea v pentru cheia c
				return false;

			// aux2->valoare == v; se sterge aux2
			aux1->urm = aux2->urm;
			n--;
			return true;
		}

	}
	return false;	// nu a fost gasita lista cheii respective
}


/*
  theta(1)
*/
int MDO::dim() const {
	return n;
}


/*
  theta(1)
*/
bool MDO::vid() const {
	return n == 0;
}


/*
  theta(n)
*/
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}


/*
  CF : theta(1) -> lista cheii se afla la prima locatie din tabela si contine o singura pereche
  CD : theta(n) ->  toate listele se disperseaza la aceeasi locatie +
					lista este ultima din coliziune de la locatia respectiva
*/
vector<TValoare> MDO::stergeValoriPentruCheie(TCheie cheie)
{
	vector<TValoare> deReturnat;
	Lista* poz = new Lista;
	Lista* prec = new Lista;
	poz = tabela[hashFunction(cheie)];
	prec = poz;

	while (poz != nullptr) {
		if (poz->prim != nullptr && poz->prim->elem.first != cheie && r(poz->prim->elem.first, cheie)) {
			prec = poz;		// salvez lista anterioara
			poz = poz->urm;
		}
		else break;
	}
	if (poz == nullptr || poz->prim == nullptr || (poz->prim->elem.first != cheie) )
		return deReturnat;

	if (poz->prim->elem.first == cheie) {	// salvarea valorilor in vectorul deReturnat
		auto aux = poz->prim;
		while (aux != nullptr) {
			deReturnat.push_back(aux->elem.second);
			aux = aux->urm;
		}
	}

	if (poz == prec)	// lista de sters este prima de la locatia respectiva
		tabela[hashFunction(cheie)] = poz->urm;
	else
		prec->urm = poz->urm;

	delete poz;
	n = n - deReturnat.size();
	return deReturnat;
}


/*
  CF : theta(1)
  CD : theta(n)
*/
TCheie MDO::cheieMaxima() const
{
	if (n == 0)
		return NULL_TCHEIE;

	TCheie maxima = -1;
	Lista* curent = new Lista;

	for (int i = 0; i < m; i++) {
		curent = tabela[i];
		if (curent != nullptr) {

			while (curent->urm != nullptr)
				curent = curent->urm;
			if (curent->prim != nullptr) {

				if (maxima == NEDEFINITA)
					maxima = curent->prim->elem.first;

				if (r(maxima, curent->prim->elem.first))
					maxima = curent->prim->elem.first;
			}
		}
	}
	return maxima;
}


/*
  theta(m)
*/
MDO::~MDO() {
	for (int i = 0; i < m; i++) {
		Lista* curenta = tabela[i];
		Lista* precedenta = nullptr;
		while (curenta != nullptr) {
			precedenta = curenta;
			curenta = curenta->urm;
			delete precedenta;
		}
	}
	delete[] tabela;
}