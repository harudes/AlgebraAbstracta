#include <iostream>
#include <fstream>
#include <NTL/ZZ.h>
#include "AriMod.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string>
#include <sstream>
#include <math.h>
#include <windows.h>

using namespace std;
using namespace NTL;
#define DIV 1024
class RSA{
    ZZ d;
    ZZ p;
    ZZ q;
    string alfabeto;
    string firma;
    ZZ resto_chino(ZZ m){
        ZZ Dp=potenciaMod(modulo(m,p),modulo(d,p-1),p);
        ZZ Dq=potenciaMod(modulo(m,q),modulo(d,q-1),q);
        ZZ P=N;
        ZZ P1=q;
        ZZ P2=p;
        ZZ q1=inversoMult(P1,p);
        ZZ q2=inversoMult(P2,q);
        ZZ D=modulo(modulo(Dp*P1*q1,P)+modulo(Dq*P2*q2,P),P);
        return D;
    }
public:
    ZZ e;
    ZZ e2;
    ZZ N;
    ZZ N2;
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
        p=P;
        q=Q;
        N = P * Q;
        ZZ phi_N = (P - 1) * (Q - 1);
        e = ga(30,bits,12,7);
        while(e > phi_N || euclides(e, phi_N) != 1)
        {
            e = ga(30,bits,12,7);
        }
        d = inversoMult(e, phi_N);
        }

    RSA(int bitTam){
        Generar_claves(bitTam);
        alfabeto="0123456789 abcdefghijklmnopqrstuvwxyz.,ABCDEFGHIJKLMNOPQRSTUVWXYZ";}

    RSA(ZZ publica, ZZ n, int bitTam){
        alfabeto="0123456789 abcdefghijklmnopqrstuvwxyz.,ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        Generar_claves(bitTam);
        e2=publica;
        N2=n;
        firma="Luis Francisco Rendon Zuniga";
        }

    string encriptar(string mensaje){
        string message;
        string temp="";
        string letra;
        string aux;
        string message_2;
        ZZ num;
        int tam = ZZtoString(to_ZZ(alfabeto.length()-1)).length();
        int tamN= ZZtoString(N).length();
        int tamN2= ZZtoString(N2).length();
        //cifra el mensaje
        for(int i=0;i<mensaje.length();i++){
                letra=ZZtoString(to_ZZ(alfabeto.find(mensaje[i])));
                aux=letra;
                letra=string (tam-letra.length(),'0');
                letra+=aux;
                temp+=letra;
        }
        while(temp.length()%(tamN2-1)!=0){
                temp+=ZZtoString(to_ZZ(alfabeto.find("w")));
        }
        for(int i=0;i<temp.length();i+=tamN2-1){
            letra="";
            for(int j=0;j<tamN2-1;j++){
                letra+=temp[j+i];
            }
            num=potenciaMod(StringtoZZ(letra),e2,N2);
            letra=ZZtoString(num);
            aux=letra;
            letra=string (tamN2-letra.length(),'0');
            letra+=aux;
            message+=letra;
        }
        //empieza a cifrar la firma
        temp="";
        for(int i=0;i<firma.length();i++){
                letra=ZZtoString(to_ZZ(alfabeto.find(firma[i])));
                aux=letra;
                letra=string (tam-letra.length(),'0');
                letra+=aux;
                temp+=letra;
        }
        cout<<"Temp: "<<temp<<endl<<endl;
        while(temp.length()%(tamN-1)!=0){
                temp+=ZZtoString(to_ZZ(alfabeto.find("w")));
        }
        for(int i=0;i<temp.length();i+=tamN-1){
            letra="";
            for(int j=0;j<tamN-1;j++){
                letra+=temp[j+i];
            }
            cout<<"numero: "<<letra<<endl<<endl;
            num=potenciaMod(StringtoZZ(letra),d,N);
            letra=ZZtoString(num);
            aux=letra;
            letra=string (tamN-letra.length(),'0');
            letra+=aux;
            message_2+=letra;
        }
        cout<<"Primera parte: "<<message_2<<endl<<endl;
        //segundo cifrado firma
        temp = "";
        for(int i=0;i<message_2.length();i+=tamN2-1){
            letra = "";
            for(int j=0; j<tamN2-1;j++){
                letra+=message_2[i+j];
            }
            num=potenciaMod(StringtoZZ(letra),e2,N2);
            letra=ZZtoString(num);
            aux=letra;
            letra=string (tamN2-letra.length(),'0');
            letra+=aux;
            temp+=letra;
        }
        message_2=temp;
        //concatenacion
        cout<<"Mensaje: "<<message<<endl<<endl;
        cout<<"Firma: "<<message_2<<endl<<endl;
        message+=message_2;
        return message;
    }
    string desencriptar(string mensaje, ZZ e_e, ZZ N_e){
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
        while(message[message.length()-1]=='w'){
            aux="";
            for(int i=0;i<message.length()-1;i++)
                aux+=message[i];
            message=aux;
        }
        return message;
    }
};

int main(){
    srand(time(NULL));
    string bits="0001001100110100010101110111100110011011101111001101111111110001";
    cout<<bits[56]<<bits[48]<<bits[40]<<bits[32]<<bits[24]<<bits[16]<<bits[8]<<endl;
    cout<<bits[0]<<bits[57]<<bits[49]<<bits[41]<<bits[33]<<bits[25]<<bits[17]<<endl;
    /*
    RSA receptor(1024);
    RSA emisor(receptor.e,receptor.N,1024);
    cout<<"Se crearon las claves"<<endl;
    string mensaje=emisor.encriptar("Hola");
    cout<<receptor.desencriptar(mensaje,emisor.e,emisor.N);*/
    /*
    int bits=1024;
    cout<<"Cifrador RSA"<<endl;
    RSA receptor(bits);
    ofstream claves;
    claves.open("claves.txt");
    claves<<"e:"<<receptor.e<<endl<<endl<<"N:"<<receptor.N;
    claves.close();
    int o=1;
    while(o!=0){
        cout<<endl<<"0: Cerrar el programa"<<endl<<"1:Cifrar un mensaje"<<endl<<"2:Descifrar un mensaje"<<endl;
        cin>>o;
        switch(o){
        case 1:{
            string a, b;
            ifstream clave_e, clave_N;
            clave_e.open("clave e.txt");
            getline(clave_e,a);
            clave_N.open("clave N.txt");
            getline(clave_N,b);
            RSA emisor(StringtoZZ(a),StringtoZZ(b),bits);
            string mensaje;
            cout<<"Escriba el mensaje"<<endl;
            cin>>mensaje;
            ofstream ficheroSalida;
            ficheroSalida.open("mensaje.txt");
            ficheroSalida<<emisor.encriptar(mensaje);
            ficheroSalida.close();
            }
        case 2:{
            ifstream entrada;
            string mess;
            entrada.open ("recibido.txt");
            getline(entrada,mess);
            cout<< receptor.desencriptar(mess,StringtoZZ("12312"),StringtoZZ("12321"));
        }
        }
        }*/
}
