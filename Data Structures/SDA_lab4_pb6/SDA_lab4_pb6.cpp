#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
#include "Colectie.h"
#include <cassert>

using namespace std;


void testFunctionalitate() {
	Colectie c;
	for (int i = 0; i < 100; i++) {
		c.adauga(i);
	}
	assert(c.dim() == 100);
	int contor = 1;
	for (int i = 50; i < 99; i++) {
		int ap = c.eliminaAparitii(i, i);
		assert(ap == 1);
		assert(c.dim() == 100 - contor);
		contor++;
	}
	// stergerea ultimului element
	int ap = c.eliminaAparitii(10, 99);
	assert(ap == 1);
	c.adauga(0);
	c.adauga(0); // acum 0 apare de 3 ori
	try {
		c.eliminaAparitii(-2, 0);
		assert(false);
	}
	catch (exception e) {
		assert(true);
		c.eliminaAparitii(2, 0);
		assert(c.nrAparitii(0) == 1);
	}
}


int main() {
	testFunctionalitate();
	std::cout << "Test Functionalitate - succes\n";
	testAllExtins();
	testAll();
	std::cout << "Test Scurt - succes\n";
	return 0;
}
