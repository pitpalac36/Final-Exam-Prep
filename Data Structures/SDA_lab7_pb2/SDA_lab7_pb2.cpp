#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"
#include <cassert>
using namespace std;


void testFunctionalitate() {
	Matrice m(10, 10);
	for (int i = 0; i < 10; i++)
		assert(m.suma(i) == 0);
	for (int j = 0; j < m.nrColoane(); j++)
		m.modifica(4, j, 10);
	assert(m.suma(4) == 100);
	
	m.modifica(4, 2, 5);
	assert(m.suma(4) == 95);

	m.modifica(1, 0, 75);
	m.modifica(1, 9, 10);
	assert(m.suma(1) == 85);
}


int main() {

		testFunctionalitate();
		testAll();
		testAllExtins();

	cout << "End";
}