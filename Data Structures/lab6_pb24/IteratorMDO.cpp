#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d), perechiOrdonate{ nullptr }, nodCurent{nullptr} {
	perechiOrdonate = new Lista;
	perechiOrdonate->prim = nullptr;
	for (int i = 0; i < d.m; i++) {
		if (d.tabela[i] != nullptr) {
			auto currentList = d.tabela[i];	// lista curenta de la locatia i
			auto currentNode = d.tabela[i]->prim;  // nodul curent din lista curenta
			while (currentList != nullptr) {
				while (currentNode != nullptr) {
					Nod* nou = new Nod;
					nou->elem = { currentNode->elem.first, currentNode->elem.second };
					nou->urm = nullptr;
					adauga(perechiOrdonate, nou);
					currentNode = currentNode->urm;
				}
				currentList = currentList->urm;
			}
		}
	}
	nodCurent = perechiOrdonate->prim;
}

void IteratorMDO::adauga(Lista* lista, Nod* nod)
{
	if (lista->prim == nullptr) {
		lista->prim = nod;
		return;
	}
	Nod* curent1 = new Nod;
	Nod* curent2 = new Nod;
	curent1 = lista->prim;
	if (dict.r(nod->elem.first, curent1->elem.first)) {	// inaintea lui curent1
		nod->urm = curent1;
		return;
	}
	curent2 = curent1->urm;
	if (curent2 == nullptr) {	// dupa curent1
		curent1->urm = nod;
		return;
	}
	else {
		while (curent2 != nullptr && dict.r(curent2->elem.first, nod->elem.first))
			curent2 = curent2->urm;
		nod->urm = curent2;  // adaugarea inaintea curent2
		curent1->urm = nod;
	}
}

void IteratorMDO::prim() {
	nodCurent = perechiOrdonate->prim;
}

void IteratorMDO::urmator() {
	nodCurent = nodCurent->urm;
}

bool IteratorMDO::valid() const {
	return nodCurent != nullptr && dict.dim() != 0;
}

TElem IteratorMDO::element() const {
	return nodCurent->elem;
}