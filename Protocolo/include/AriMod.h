#ifndef ARIMOD_H
#define ARIMOD_H
#include <vector>
#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ modulo(ZZ a,ZZ b);

ZZ euclides(ZZ a,ZZ b);

ZZ phi(ZZ n);

ZZ inversoMult(ZZ a,ZZ m);

vector<bool> ZZtoBinary(ZZ num);

ZZ potenciaMod(ZZ n,ZZ m,ZZ mod);

bool test_primalidad(ZZ x);

ZZ convertir_decimal(std::vector <bool> a);

void rotar_derecha(vector <bool> &vec, int indice, int elementos, int vueltas);

void rotar_izquierda(vector <bool> &vec, int indice, int elementos, int vueltas);

ZZ DES(int bits);

vector<bool> PC_1(vector<bool> num);

vector<bool> PC_2(vector<bool> num);

ZZ ga(int bits_seed, int bits_num, int particiones, int vueltas);

string ZZtoString(ZZ z);

ZZ StringtoZZ(string str);

ZZ find_root(ZZ p);

#endif // ARIMOD_H

