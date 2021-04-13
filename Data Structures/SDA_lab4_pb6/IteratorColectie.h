#pragma once
#include "Colectie.h"

typedef int TElem;

class Colectie;

//iterator unidirectional pe colectie
class IteratorColectie {
private:

	//pentru a construi un iterator pe o colectie este necesar ca un pointer sau referinta la aceasta sa ii fie oferit constructorului
	IteratorColectie(const Colectie& col);

	//contine o referinta catre colectia care se itereaza
	const Colectie& colectie;

	//retine pozitia curenta in interiorul colectiei - referintala nodul curent din lista asociata
	int curent;

public:

	friend class Colectie;

	//reseteaza pozitia iteratorului la inceputul colectiei
	void prim();

	//muta iteratorul pe urmatoarea pozitie in cadrul colectiei
	void urmator();

	//verifica daca iteratorul e valid (indica un element al colectiei)
	bool valid();

	//returneaza valoarea curenta a elementului din colectie
	TElem element();
};