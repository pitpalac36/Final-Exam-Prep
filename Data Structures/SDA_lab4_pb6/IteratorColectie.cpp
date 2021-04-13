#include "IteratorColectie.h"
#include "Colectie.h"



IteratorColectie::IteratorColectie(const Colectie& col) :
	colectie(col) {
	curent = col.prim;
}

void IteratorColectie::prim() {
	curent = colectie.prim;
}

void IteratorColectie::urmator() {
	curent = colectie.urm[curent];
}

bool IteratorColectie::valid() {
	return curent != -1;
}

TElem IteratorColectie::element()
{
	return colectie.e[curent];
}