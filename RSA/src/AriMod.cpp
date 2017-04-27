#include "AriMod.h"
#include <vector>
#include <iostream>
#include <NTL/ZZ.h>
#include <stdlib.h>

using namespace std;
using namespace NTL;

ZZ modulo(ZZ a, ZZ b){
	ZZ q,r;
	q=a/b;
	r=a-(q*b);
	if(r<0){
		q--;
		r+=b;
	}
	return r;
}

ZZ euclides(ZZ a, ZZ b){
	ZZ r=modulo(a,b);
	while(r>0){
		a=b;
		b=r;
		r=modulo(a,b);
	}
	return b;
}

ZZ inversoMult(ZZ a, ZZ m){
	ZZ s1=to_ZZ(1), t1=to_ZZ(0), s2=to_ZZ(0), t2=to_ZZ(1),q ,r ,s ,t;
	while(m>0){
		q=a/m;
		r=modulo(a,m);
		a=m;
		m=r;
		s=s1-q*s2;
		s1=s2;
		s2=s;
		t=t1-q*t2;
		t1=t2;
		t2=t;
	}
	return s1;
}

ZZ potenciaMod(ZZ n, ZZ m, ZZ mod){
	ZZ resultado=to_ZZ(1);
	while(m>0){
		if(modulo(m,to_ZZ(2))==1)
			resultado=modulo(n*resultado,mod);
		m=m/2;
		n=modulo(n*n,mod);
	}
	return resultado;
}

ZZ convertir_decimal(vector <bool> a, int bits_num)
{
    ZZ num;
    num = 0;
    int e = 0;
    for(int i = bits_num - 1; i >= 0; i--)
    {
        if(a[i]==1)
        {
            num += power2_ZZ(e);
        }
        else
            num += to_ZZ(0);
        e += 1;
    }
    return num;
}
void rotar_derecha(vector <bool> &vec, int indice, int elementos, int vueltas)
{
    for(int j = vueltas; j > 0; j--)
    {
        for(int i = elementos + indice - 1; i > indice; i--)
        {
            int temp = vec[i];
            vec[i] = vec[i - 1];
            vec[i - 1] = temp;
        }
    }
}
void rotar_izquierda(vector <bool> &vec, int indice, int elementos, int vueltas)
{
    for(int j = vueltas; j > 0; j--)
    {
        for(int i = indice; i < indice + elementos - 1; i++)
        {
            int temp = vec[i];
            vec[i] = vec[i + 1];
            vec[i + 1] = temp;
        }
    }
}
ZZ ga(int bits_seed, int bits_num, int particiones, int vueltas)
{
    vector <bool> a;
    for(int i = 0; i < bits_num; i++)
    {
        a.push_back(0);
    }
    for(int i = 0; i < bits_seed; i++)
    {
        a[i] = rand()%2;
    }
    int s = 0;
    for(int i = bits_seed; i < bits_num; i++)
    {
        a[i] = a[s] ^ a[s+1];
        s++;
    }
    int elementos_pedazo = bits_num/particiones;
    int residuo_elementos = bits_num%particiones;
    if(residuo_elementos!=0)
    {
        elementos_pedazo += 1;
    }
    int indice = 0;
    while(indice < bits_num)
    {
        if((indice + elementos_pedazo) > bits_num)
        {
            if(particiones%2!=0)
            {
                rotar_izquierda(a, indice, residuo_elementos, vueltas);
                indice += elementos_pedazo;
            }
            else
                rotar_derecha(a, indice, residuo_elementos, vueltas);
                indice += elementos_pedazo;
        }
        rotar_izquierda(a, indice, elementos_pedazo, vueltas);
        indice += elementos_pedazo;
        rotar_derecha(a, indice, elementos_pedazo, vueltas);
        indice += elementos_pedazo;
    }
    ZZ num;
    num = convertir_decimal(a, bits_num);
    return num;
}
