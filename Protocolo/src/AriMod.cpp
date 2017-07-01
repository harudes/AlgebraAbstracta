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
        binario.push_back(to_int(num%to_ZZ(2)));
        num=num/to_ZZ(2);
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
    for(int i = 0; i <a.size(); i++)
    {
        if(a[i]==1)
        {
            num += power2_ZZ(e);
        }
        e ++;
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

vector<bool> truncar(vector<bool> num, int elementos){
    if(elementos<num.size()){
        vector<bool> retornar;
        for(int i=0;i<elementos;i++)
            retornar.push_back(num[i]);
        return retornar;
    }
    return num;
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
        num2.push_back(num[i+59]);
        num2.push_back(num[i+51]);
        num2.push_back(num[i+43]);
        num2.push_back(num[i+35]);
        num2.push_back(num[i+63]);
        num2.push_back(num[i+54]);
        num2.push_back(num[i+46]);
        num2.push_back(num[i+38]);
        num2.push_back(num[i+30]);
        num2.push_back(num[i+22]);
        num2.push_back(num[i+14]);
        num2.push_back(num[i+6]);
        num2.push_back(num[i+61]);
        num2.push_back(num[i+53]);
        num2.push_back(num[i+45]);
        num2.push_back(num[i+37]);
        num2.push_back(num[i+29]);
        num2.push_back(num[i+21]);
        num2.push_back(num[i+13]);
        num2.push_back(num[i+5]);
        num2.push_back(num[i+60]);
        num2.push_back(num[i+52]);
        num2.push_back(num[i+44]);
        num2.push_back(num[i+36]);
        num2.push_back(num[i+28]);
        num2.push_back(num[i+20]);
        num2.push_back(num[i+12]);
        num2.push_back(num[i+4]);
        num2.push_back(num[i+27]);
        num2.push_back(num[i+19]);
        num2.push_back(num[i+1]);
        num2.push_back(num[i+3]);
    }
    return num2;
}
vector<bool> PC_2(vector<bool> num){
    vector<bool> num2;
    for(int i=0; i<num.size();i+=56){
        num2.push_back(num[i+13]);
        num2.push_back(num[i+16]);
        num2.push_back(num[i+10]);
        num2.push_back(num[i+23]);
        num2.push_back(num[i]);
        num2.push_back(num[i+4]);
        num2.push_back(num[i+2]);
        num2.push_back(num[i+27]);
        num2.push_back(num[i+14]);
        num2.push_back(num[i+5]);
        num2.push_back(num[i+20]);
        num2.push_back(num[i+9]);
        num2.push_back(num[i+22]);
        num2.push_back(num[i+18]);
        num2.push_back(num[i+11]);
        num2.push_back(num[i+3]);
        num2.push_back(num[i+25]);
        num2.push_back(num[i+7]);
        num2.push_back(num[i+15]);
        num2.push_back(num[i+6]);
        num2.push_back(num[i+26]);
        num2.push_back(num[i+19]);
        num2.push_back(num[i+12]);
        num2.push_back(num[i+1]);
        num2.push_back(num[i+40]);
        num2.push_back(num[i+51]);
        num2.push_back(num[i+30]);
        num2.push_back(num[i+36]);
        num2.push_back(num[i+36]);
        num2.push_back(num[i+54]);
        num2.push_back(num[i+29]);
        num2.push_back(num[i+39]);
        num2.push_back(num[i+50]);
        num2.push_back(num[i+44]);
        num2.push_back(num[i+32]);
        num2.push_back(num[i+47]);
        num2.push_back(num[i+43]);
        num2.push_back(num[i+48]);
        num2.push_back(num[i+38]);
        num2.push_back(num[i+55]);
        num2.push_back(num[i+33]);
        num2.push_back(num[i+52]);
        num2.push_back(num[i+45]);
        num2.push_back(num[i+41]);
        num2.push_back(num[i+49]);
        num2.push_back(num[i+35]);
        num2.push_back(num[i+28]);
        num2.push_back(num[i+31]);
    }
    return num2;
}
ZZ DES(int bits){
    vector<bool> num,num2,num3;
    int vueltas[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    int num_particiones;
    ZZ resultado;
    num=ZZtoBinary(ga(100,1024,30,5));
    while(num.size()%64!=0)
        num.push_back(0);
    num2=PC_1(num);
    num_particiones=num2.size()/56;
    if(num_particiones%2==0){
        for(int i=0;i<16;i++){
            for(int j=0;j<num2.size();j+=112){
                rotar_izquierda(num2,j,56,vueltas[i]);
                rotar_derecha(num2,j+56,56,vueltas[i]);
            }
            num3=truncar(PC_2(num2),bits);
            num3[0]=1;
            resultado=convertir_decimal(num3);
            if(ProbPrime(resultado,10)==1)
                return resultado;
        }
        DES(bits);
    }
    else{
        for(int i=0;i<16;i++){
            for(int j=0;j<num2.size();j+=112){
                rotar_izquierda(num2,j,56,vueltas[i]);
                rotar_derecha(num2,j+56,56,vueltas[i]);
            }
            rotar_izquierda(num2,num2.size()-56,56,1);
            num3=truncar(PC_2(num2),bits);
            num3[0]=1;
            resultado=convertir_decimal(num3);
            if(ProbPrime(resultado,10)==1)
                return resultado;
        }
        DES(bits);
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
    a[0]=1;
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
ZZ find_root(ZZ p){
    ZZ q=(p-to_ZZ(1))/to_ZZ(2),g=to_ZZ(2);
    for(;g<p-1;g++){
        if((potenciaMod(g,to_ZZ(2),p)!=to_ZZ(1))&&(potenciaMod(g,q,p)!=to_ZZ(1)))
            return g;
    }
    return to_ZZ(0);
}
