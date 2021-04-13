#include <iostream>
#include "TestScurt.h"
#include "TestExtins.h"
#include <cassert>
#include "MDO.h"


bool r(TCheie c1, TCheie c2) {
    if (c1 >= c2) {
        return true;
    }
    else {
        return false;
    }
}

void testCheieMaxima() {
    auto d = MDO{ r };
    assert(d.cheieMaxima() == NULL_TCHEIE);
    d.adauga(10, 100);
    assert(d.cheieMaxima() == 10);
    for (int i = 5; i < 20; i++) {
        d.adauga(i, 1);
    }
    TCheie maxima = d.cheieMaxima();
    assert(maxima == 5);
}


void testFunctionalitate() {
    auto d = MDO{ r };
    auto v = d.stergeValoriPentruCheie(10);
    assert(v.size() == 0);
    for (int i = 0; i < 50; i++){
        d.adauga(100, i);
    }
    v = d.stergeValoriPentruCheie(100);
    assert(v.size() == 50);
    assert(d.dim() == 0);
    for (int i = 0; i <= 10; i++) {
        d.adauga(i, i + 1);
        d.adauga(i, i + 2);
    }
    int dimensiune = d.dim();
    for (int i = 0; i <= 10; i++) {
        vector<TValoare> vector = d.stergeValoriPentruCheie(i);
        assert(vector.size() == 2);
        dimensiune = dimensiune - 2;
        assert(d.dim() == dimensiune);
    }
    vector<TValoare> vector = d.stergeValoriPentruCheie(0);
    assert(vector.size() == 0);
}


int main() {
       testCheieMaxima();
       testFunctionalitate();
       testAll();
       testAllExtins();
    std::cout << "Finished Tests!" << std::endl;
}
