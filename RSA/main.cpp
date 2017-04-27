#include <iostream>
#include <NTL/ZZ.h>
#include "AriMod.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace NTL;

class bbs{

       ZZ p, q, M, seed, actual;
       public:
       bbs(ZZ p, ZZ q, ZZ s){
            this->p = p;
            this->q = q;
            this->seed = s;
            M = p * q;
            actual = s;
       }
       ZZ getrandom(){
            ZZ r = to_ZZ(fmod(to_int(actual*actual),to_int(M)));
            actual = r;
            return r;
       }
       ZZ getirandom(int i){
            ZZ g = modulo(p, q);
            ZZ lcm = p * q / g;
            ZZ exp = to_ZZ(1);
            for(int j = 1; j <= i; ++j){
                exp = to_ZZ(fmod(to_long(exp+exp),to_long(lcm)));
            }
            ZZ x0 = seed * seed;
            ZZ r = x0;
            for(int j = 2; j <= to_int(exp); ++j){
                r = to_ZZ(fmod(to_long(r*x0),to_long(M)));
        }
        }
   };

class Cesar{
    ZZ clave;
public:
    string alfabeto;
    Cesar(ZZ key, string alfabet){clave=key;}
    Cesar(int key){clave=to_ZZ(key);}
    string encriptar(string mensaje){
        int tam = alfabeto.size();
        for(int i = 0; i <= mensaje.size(); i++)
            mensaje[i]=alfabeto[to_int(modulo(to_ZZ(alfabeto.find(mensaje[i]))+modulo(clave,to_ZZ(tam)),to_ZZ(tam)))];
        return mensaje;
    }
    string desencriptar(string mensaje){
        int tam = alfabeto.size();
        for(int i = 0; i <= mensaje.size(); i++){
            mensaje[i]=alfabeto[to_int(modulo(to_ZZ(alfabeto.find(mensaje[i]))-modulo(clave,to_ZZ(tam)),to_ZZ(tam)))];
        }
        return mensaje;
    }
};

class Afin{
    ZZ A;
public:
    ZZ B;
    string alfabeto;
    Afin(){
        alfabeto="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
        A=ga(5,9,3,2);
        while(euclides(A,to_ZZ(alfabeto.size()))!=to_ZZ(1))
            A=ga(5,9,3,2);
        B=ga(6,9,2,5);
        cout<<A<<endl;
    }
    Afin(int key_A, int key_B){
        alfabeto="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
        A=inversoMult(to_ZZ(key_A),to_ZZ(alfabeto.size()));
        B=to_ZZ(key_B);
        cout<<A<<endl;
        }
    string encriptar(string mensaje){
        int tam = alfabeto.size();
        ZZ pos;
        ZZ A_temp=modulo(A,to_ZZ(tam));
        ZZ B_temp=modulo(B,to_ZZ(tam));
        for(int i = 0; i <= mensaje.size(); i++){
            pos=alfabeto.find(mensaje[i]);
            pos=modulo(to_ZZ(pos)*A_temp,to_ZZ(tam));
            pos=modulo(to_ZZ(pos)+B_temp,to_ZZ(tam));
            mensaje[to_int(pos)]=alfabeto[to_int(pos)];
        }
        return mensaje;
    }
    string desencriptar(string mensaje){
        int tam = alfabeto.size();
        int pos;
        ZZ A_temp=modulo(A,to_ZZ(tam));
        ZZ B_temp=modulo(B,to_ZZ(tam));
        for(int i = 0; i <= mensaje.size(); i++){
            pos=alfabeto.find(mensaje[i]);
            pos=to_int(modulo(to_ZZ(pos)-B_temp,to_ZZ(tam)));
            pos=to_int(modulo(to_ZZ(pos)*A_temp,to_ZZ(tam)));
            mensaje[i]=alfabeto[pos];
        }
        return mensaje;
    }
    ZZ get_A(){return A;}
};

class RSA{
    ZZ d;
public:
    string alfabeto;
    ZZ e;
    ZZ N;
    void Generar_claves(){
        ZZ p = ga(5,8,3,3);
        ZZ q = ga(5,8,2,4);
        while(ProbPrime(p,10)!=1)
        {
            p = ga(5,8,3,3);
        }
        while(ProbPrime(q,10)!=1)
        {
            q = ga(5,8,2,4);
        }
        N = p * q;
        ZZ phi_N = (p - 1) * (q - 1);
        e = ga(6,8,5,2);
        while(e > phi_N || euclides(e, phi_N) != 1)
        {
            e = ga(6,8,5,2);
        }
        cout <<"Clave publica: " << e << endl;
        d = modulo(inversoMult(e, phi_N),phi_N);
        cout << "Clave privada: " << d << endl;
        cout <<"N: " << N << endl;
        }
    RSA(){
        Generar_claves();
        cout<<e<<endl;
        alfabeto="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";}
    RSA(ZZ publica, ZZ n){alfabeto="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";e=publica;N=n;}
    vector<ZZ> encriptar(string mensaje){
        vector<ZZ> message;
        ZZ pos;
        for(int i = 0; i <= mensaje.size()-1; i++){
            pos=to_ZZ(alfabeto.find(mensaje[i]));
            pos=potenciaMod(pos,e,N);
            message.push_back(pos);
        }
        return message;
    }
    string desencriptar(vector<ZZ> mensaje){
        string message;
        ZZ pos;
        for(int i = 0; i <= mensaje.size()-1; i++){
            pos=mensaje[i];
            pos=potenciaMod(to_ZZ(pos),d,N);
            message+=alfabeto[to_int(pos)];
        }
        return message;
    }
};

int main(){
    srand(time(NULL));
    RSA receptor;
    RSA emisor(receptor.e, receptor.N);
    vector<ZZ> texto = emisor.encriptar("Hola, como estas");
    string texto2=receptor.desencriptar(texto);
    cout<<texto2<<endl;
    return 0;
}
