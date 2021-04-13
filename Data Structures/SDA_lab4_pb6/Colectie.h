#pragma once;
#include "IteratorColectie.h"

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

	friend class IteratorColectie;

private:
	int cp;
	int prim, ultim, primLiber;
	TElem* e;
	int* urm, * prec;
	int dimensiune;

	void redimensioneaza();

	//se returneaza pozitia unui spatiu liber in lista
	int aloca();

	//dealoca spatiul de indice i
	void dealoca(int i);

	//functie privata care creeaza un nod in lista inlantuita
	int creeazaNod(TElem e);

public:
	//constructorul implicit
	Colectie();


	//adauga un element in colectie
	void adauga(TElem e);


	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);


	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;


	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;


	//verifica daca colectia e vida;
	bool vida() const;

	// elimina nr aparitii ale lui elem 
	// returneaza nr de aparitii ale elementului
	// arunca exceptie daca nr este negativ
	int eliminaAparitii(int nr, TElem elem);


	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;


	// destructorul colectiei
	~Colectie();
};