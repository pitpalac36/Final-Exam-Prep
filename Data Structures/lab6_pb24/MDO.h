#pragma once
#include <utility>
#include <vector>
#define NULL_TCHEIE 0
#define NEDEFINITA -1
typedef int TCheie;
typedef int TValoare;
typedef std::pair<TCheie, TValoare> TElem;
typedef bool(*Relatie)(TCheie, TCheie);
using namespace std;
class IteratorMDO;

typedef struct Nod {
	TElem elem;
	Nod* urm;
}Nod;


typedef struct Lista {
	Nod* prim;
	Lista* urm;
}Lista;


class MDO {
	friend class IteratorMDO;
private:
	Lista** tabela;
	int m;	// capacitate
	int n;	// dimensiunea efectiva
	Relatie r;
	int hashFunction(TCheie cheie) const;
	void redimensioneaza();

public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;


	// elimină o cheie împreună cu toate valorile sale
	// returneaza un vector cu valorile care au fost anterior asociate acestei chei (și au fost eliminate)
	vector<TValoare> stergeValoriPentruCheie(TCheie cheie);

	// găsește și returnează cheia maximă a multidicționarului
	// Dacă  multidicționarul este vid, se returnează NULL_TCHEIE
	TCheie cheieMaxima() const;


	// destructorul
	~MDO();

};
