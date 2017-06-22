#include "AriMod.h"
#include <vector>
#include <iostream>
#include <NTL/ZZ.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <bitset>

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



ZZ phi(ZZ n){
    if(test_primalidad(n))
        return n-1;
    ZZ result = n;
    for (ZZ p=to_ZZ(2); p*p<=n; ++p)
    {
        if (modulo(n,p) == to_ZZ(0))
        {
            while (modulo(n,p) == to_ZZ(0))
                n /= p;
            result -= result / p;
        }
    }
    if (n > to_ZZ(1))
        result -= result / n;
    return result;
};

ZZ inversoMult(ZZ a, ZZ n){
	ZZ n0 = n, temp, q;
    ZZ E0 = to_ZZ(0);
    ZZ E1 = to_ZZ(1);
    while (a > 1){
        q = a / n;
        temp = n;
        n = modulo(a,n);
        a = temp;
        temp = E0;
        E0 = E1 - q * E0;
        E1 = temp;
    }
    if (E1 < 0)
        E1 += n0;
    return E1;
}

vector<bool> ZZtoBinary(ZZ num){
    vector<bool> binario;
    while(num>0){
        binario.push_back(to_int(modulo(num,to_ZZ(2))));
        num=num>>1;
    }
    return binario;
}

ZZ potenciaMod(ZZ n, ZZ m, ZZ mod){
    if(m==0)
        return to_ZZ(1);
    if(n>mod)
        n=modulo(n,mod);
    vector<bool> b=ZZtoBinary(m);
    ZZ d=to_ZZ(1);
	for(int i=b.size();i>0;i--){
        d=modulo(d*d,mod);
        if(b[i-1]==1)
            d=modulo(d*n,mod);
	}
	return d;
}

bool test_primalidad(ZZ x){
    ZZ a = modulo(ga(10,1014,4,8),x-2)+1;
    if(potenciaMod(a,x-1,x)== 1)
        return 1;
    else
        return 0;
}

ZZ convertir_decimal(vector <bool> a)
{
    ZZ num;
    num = 0;
    int e = 0;
    for(int i = a.size() - 1; i >= 0; i--)
    {
        if(a[i]==1)
        {
            num += power2_ZZ(e);
        }
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
vector<bool> PC_1(vector<bool> num){
    vector<bool> num2;
    for(int i=0;i<num.size();i+=64){
        num2.push_back(num[i+56]);
        num2.push_back(num[i+48]);
        num2.push_back(num[i+40]);
        num2.push_back(num[i+32]);
        num2.push_back(num[i+24]);
        num2.push_back(num[i+16]);
        num2.push_back(num[i+8]);
        num2.push_back(num[i+0]);
        num2.push_back(num[i+57]);
        num2.push_back(num[i+49]);
        num2.push_back(num[i+41]);
        num2.push_back(num[i+33]);
        num2.push_back(num[i+25]);
        num2.push_back(num[i+17]);
        num2.push_back(num[i+9]);
        num2.push_back(num[i+1]);
        num2.push_back(num[i+58]);
        num2.push_back(num[i+50]);
        num2.push_back(num[i+42]);
        num2.push_back(num[i+34]);
        num2.push_back(num[i+26]);
        num2.push_back(num[i+18]);
        num2.push_back(num[i+10]);
        num2.push_back(num[i+2]);
        num2.push_back(num[i+]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
        num2.push_back(num[i+56]);
    }
}
ZZ DES(int bits){
    vector<bool> num,num2,num3;
    for(int i=0; i<bits;i++)
        num.push_back(1);
    for(int i=0; i<bits; i++)
        num[i]=rand()%2;
    num2=PC_1(num);
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
    int indice = 0;
    int cont_particiones = 0;
    while(cont_particiones < particiones - 1)
    {
        if(cont_particiones%2 == 0)
        {
            rotar_izquierda(a, indice, elementos_pedazo, vueltas);
        }
        else
            rotar_derecha(a, indice, elementos_pedazo, vueltas);
        indice += elementos_pedazo;
        cont_particiones++;
    }
    if(cont_particiones%2 == 0)
    {
        rotar_izquierda(a, indice, bits_num - ((particiones - 1) * elementos_pedazo), vueltas);
    }
    else
        rotar_derecha(a, indice, bits_num - ((particiones - 1) * elementos_pedazo), vueltas);

    ZZ num;
    a[bits_num-1]=1;
    num = convertir_decimal(a);
    return num;
}

string ZZtoString(ZZ z) {
    stringstream buffer;
    buffer << z;
    return buffer.str();
}
ZZ StringtoZZ(string str){
    ZZ number(INIT_VAL, str.c_str());
    return number;
}
