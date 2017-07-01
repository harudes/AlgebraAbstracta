#include <iostream>
#include <fstream>
#include <NTL/ZZ.h>
#include "AriMod.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sstream>
#include <math.h>
#include <windows.h>

using namespace std;
using namespace NTL;

class protocolo{
private:
    ZZ p1;
    ZZ p2;
    ZZ d;
    string firma;
    string alfabeto;
    void generar_claves(int bits){
        q=ga(bits/10,bits,30,5);
        while(ProbPrime(q,10)!=1)
            q=ga(bits/10,bits,30,5);
        g=find_root(q);
        p1=DES(bits/2);
        p2=DES(bits/2);
        N=p1*p2;
        ZZ phiN=(p1-1)*(p2-1);
        e=ga(bits/10,bits,30,4);
        while(e>phiN||euclides(e,phiN)!=1)
            e=ga(bits/10,bits,30,4);
        d=inversoMult(e,phiN);
    }

public:
    ZZ N;
    ZZ N2;
    ZZ q;
    ZZ g;
    ZZ e;
    ZZ e2;
    protocolo(int bits){
        generar_claves(bits);
        alfabeto="0123456789 abcdefghijklmnopqrstuvwxyz.,ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    protocolo(int bits,ZZ n, ZZ Q, ZZ G, ZZ E){
        generar_claves(bits);
        alfabeto="0123456789 abcdefghijklmnopqrstuvwxyz.,ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for(int i=0;i<50;i++){
            for(int j=0;j<10;j++)
                firma+=ZZtoString(to_ZZ(j));
        }
        firma+='0';
        N2=n;
        q=Q;
        g=G;
        e2=E;
    }
    string cifrar(string mensaje){
        ZZ a=ga(100,1024,30,4)%q;
        ZZ k=potenciaMod(g,a,q);
        ZZ Ca=potenciaMod(a,e,N);
        string message;
        string temp;
        string aux;
        int tamN=ZZtoString(N).length();
        int tamN2=ZZtoString(N2).length();
        int tamq=ZZtoString(q).length();
        if(firma.length()>(tamN)!=0)
            firma=string(firma.length()%(tamN-1),'0')+firma;
        for(int i=0;i<(firma.length()/(tamN-1));i++){
            temp=firma.substr(i*(tamN-1),tamN-1);
            temp=ZZtoString(potenciaMod(StringtoZZ(temp),d,N));
            temp=string(tamN-temp.length(),'0')+temp;
            message+=temp;
        }
        aux=message;
        message="";
        for(int i=0;i<(aux.length()/(tamN2-1));i++){
            temp=aux.substr(i*(tamN2-1),tamN2-1);
            temp=ZZtoString(potenciaMod(StringtoZZ(temp),e2,N2));
            temp=string(tamN2-temp.length(),'0')+temp;
            message+=temp;
        }
        aux=message;
        message="";
        for(int i=0;i<aux.length()/(tamq-1);i++){
            temp=aux.substr(i*(tamq-1),tamq-1);
            temp=ZZtoString(modulo(StringtoZZ(temp)*k,q));
            temp=string(tamq-temp.length(),'0')+temp;
            message+=temp;
        }
        aux=string(tamq-ZZtoString(Ca).length(),'0')+ZZtoString(Ca);
        message+=aux;
        return message;
    }
    string descifrar(string mensaje,ZZ e2, ZZ N2){
        int tamN=ZZtoString(N).length();
        int tamN2=ZZtoString(N2).length();
        int tamq=ZZtoString(q).length();
        string message;
        string firma;
        string temp;
        string aux;
        ZZ Ca=StringtoZZ(mensaje.substr(mensaje.length()-tamq,tamq));
        ZZ a=potenciaMod(Ca,d,N);
        ZZ k=potenciaMod(g,a,q);
        k=inversoMult(k,q);
        firma=mensaje.substr(0,mensaje.length()-tamq);
        aux=firma;
        firma="";
        for(int i=0;i<aux.length()/(tamq);i++){
            temp=aux.substr(i*(tamq),tamq);
            temp=ZZtoString(modulo(StringtoZZ(temp)*k,q));
            temp=string(tamq-temp.length(),'0')+temp;
            firma+=temp;
        }
        aux=firma;
        firma="";
        for(int i=0;i<(aux.length()/(tamN));i++){
            temp=aux.substr(i*(tamN),tamN);
            temp=ZZtoString(potenciaMod(StringtoZZ(temp),d,N));
            temp=string(tamN-temp.length(),'0')+temp;
            firma+=temp;
        }
        aux=firma;
        firma="";
        for(int i=0;i<(aux.length()/(tamN2));i++){
            temp=aux.substr(i*tamN2,tamN2);
            temp=ZZtoString(potenciaMod(StringtoZZ(temp),e2,N2));
            firma+=temp;
        }
        return firma;
    }
};

int main()
{
    srand(time(NULL));
    protocolo receptor(1024);
    protocolo emisor(1024,receptor.N,receptor.q,receptor.g,receptor.e);
    string b=emisor.cifrar("hola");
    cout<<receptor.descifrar(b,emisor.e,emisor.N);
    return 0;
}
