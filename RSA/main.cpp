#include <iostream>
#include <NTL/ZZ.h>
#include "AriMod.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string>
#include <sstream>
#include <math.h>

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

class RSA{
    ZZ d;
    ZZ p;
    ZZ q;
    ZZ resto_chino(ZZ m){
        ZZ Dp=potenciaMod(modulo(m,p),modulo(d,p-1),p);
        ZZ Dq=potenciaMod(modulo(m,q),modulo(d,q-1),q);
        ZZ P=p*q;
        ZZ P1=q;
        ZZ P2=p;
        ZZ q1=inversoMult(P1,p);
        ZZ q2=inversoMult(P2,q);
        ZZ D=modulo(modulo(Dp*P1*q1,P)+modulo(Dq*P2*q2,P),P);
        return D;
    }
public:
    string alfabeto;
    ZZ e;
    ZZ N;
    void Generar_claves(int bits){
        ZZ P = ga(40,(bits/2),15,10);
        ZZ Q = ga(40,(bits/2),13,12);
        while(ProbPrime(P,10)!=1)
        {
            P = ga(40,(bits/2),15,10);
        }
        while(ProbPrime(Q,10)!=1||Q==P)
        {
            Q = ga(40,(bits/2),13,12);
        }
        cout<<"P: "<<P<<endl<<endl<<"Q: "<<Q<<endl<<endl;
        p=P;
        q=Q;
        N = P * Q;
        ZZ phi_N = (P - 1) * (Q - 1);
        e = ga(30,bits,12,7);
        while(e > phi_N || euclides(e, phi_N) != 1)
        {
            e = ga(30,bits,12,7);
        }
        cout <<"Clave publica: "<< e << endl<<endl;
        d = modulo(inversoMult(e, phi_N),phi_N);
        cout << "Clave privada: " << d << endl;
        cout <<"N: " <<N<<endl<<endl;
        }

    RSA(int bitTam){
        Generar_claves(bitTam);
        alfabeto="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;#";}

    RSA(ZZ publica, ZZ n){alfabeto="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;#";e=publica;N=n;}

    string encriptar(string mensaje){
        string message;
        string temp="";
        string letra;
        string aux;
        ZZ num;
        int tam = ZZtoString(to_ZZ(alfabeto.length()-1)).length();
        int tamN= ZZtoString(N).length();
        for(int i=0;i<mensaje.length();i++){
                letra=ZZtoString(to_ZZ(alfabeto.find(mensaje[i])));
                while(letra.length()<tam){
                    aux=letra;
                    letra="0";
                    letra+=aux;
                }
                temp+=letra;
        }
        while(temp.length()%(tamN-1)!=0){
                temp+=ZZtoString(to_ZZ(alfabeto.find("#")));
        }
        for(int i=0;i<temp.length();i+=tamN-1){
            letra="";
            for(int j=0;j<tamN-1;j++){
                letra+=temp[j+i];
            }
            num=potenciaMod(StringtoZZ(letra),e,N);
            letra=ZZtoString(num);
            while(letra.length()<tamN){
                aux=letra;
                letra="0";
                letra+=aux;
            }
            message+=letra;
        }
        return message;
    }
    string desencriptar(string mensaje){
        string message;
        string letra;
        string temp;
        string aux;
        ZZ num;
        int tam = ZZtoString(to_ZZ(alfabeto.length()-1)).length();
        int tamN= ZZtoString(N).length();
        for(int i=0;i<mensaje.length();i+=tamN){
            letra="";
            for(int j=0;j<tamN;j++){
                letra+=mensaje[j+i];
            }
            num=StringtoZZ(letra);
            letra=ZZtoString(resto_chino(num));
            while(letra.length()<tamN-1){
                aux=letra;
                letra="0";
                letra+=aux;
            }
            temp+=letra;
        }
        for(int i=0;i<temp.length();i+=tam){
            letra="";
            for(int j=0;j<tam;j++){
                letra+=temp[j+i];
            }
            message+=alfabeto[to_int(StringtoZZ(letra))];
        }
        while(message[message.length()-1]=='#'){
            aux="";
            for(int i=0;i<message.length()-1;i++)
                aux+=message[i];
            message=aux;
        }
        return message;
    }

    void set_d(ZZ){}
};

int main(){
    srand(time(NULL));
    RSA receptor(1024);
    RSA emisor(receptor.e,receptor.N);
    string mensaje=emisor.encriptar("Arroz con mango");
    cout<<mensaje<<endl;
    cout<<receptor.desencriptar(mensaje)<<endl;

}
