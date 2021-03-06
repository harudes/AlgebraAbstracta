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

using namespace std;

class Gamal{
    ZZ d;
    int bits;
    string alfabeto;
    void generar_claves_receptor(){
        p=ga(30,bits,8,10);
        while(ProbPrime(p,10)!=1)
            p=ga(30,bits,8,10);
        e1=find_root(p);
        d=modulo(ga(30,bits,9,8),p-to_ZZ(5))+to_ZZ(3);
        e2=potenciaMod(e1,d,p);
    }

public:
    ZZ e1;
    ZZ e2;
    ZZ p;
    Gamal(int Bits){
        bits = Bits;
        generar_claves_receptor();
        alfabeto="0123456789 abcdefghijklmnopqrstuvwxyz.,ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    Gamal(ZZ E1,ZZ E2,ZZ P,int Bits){
        e1=E1;
        e2=E2;
        p=P;
        bits = Bits;
        alfabeto="0123456789 abcdefghijklmnopqrstuvwxyz.,ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    string encriptar(string mensaje){
        ZZ r=modulo(ga(30,bits,9,8),p-to_ZZ(5))+to_ZZ(3);
        ZZ c1=potenciaMod(e1,r,p);
        ZZ Km=potenciaMod(e2,r,p);
        string message;
        string temp="";
        string letra;
        string aux;
        ZZ num;
        int tam = ZZtoString(to_ZZ(alfabeto.length()-1)).length();
        int tamN= ZZtoString(p).length();
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
                temp+=ZZtoString(to_ZZ(alfabeto.find("w")));
        }
        for(int i=0;i<temp.length();i+=tamN-1){
            letra="";
            for(int j=0;j<tamN-1;j++){
                letra+=temp[j+i];
            }
            num=modulo(StringtoZZ(letra)*Km,p);
            letra=ZZtoString(num);
            while(letra.length()<tamN){
                aux=letra;
                letra="0";
                letra+=aux;
            }
            message+=letra;
        }
        string c(tamN-ZZtoString(c1).length(),'0');
        c+=ZZtoString(c1);
        c+=message;
        return c;
    }
    string desencriptar(string mensaje){
        string message;
        string letra;
        string temp;
        string aux;
        int tam = ZZtoString(to_ZZ(alfabeto.length()-1)).length();
        int tamN= ZZtoString(p).length();
        ZZ num;
        ZZ c1=StringtoZZ(mensaje.substr(0,tamN));
        ZZ KM=potenciaMod(c1,d,p);
        mensaje=mensaje.substr(tamN,mensaje.length()-tamN);
        for(int i=0;i<mensaje.length();i+=tamN){
            letra="";
            for(int j=0;j<tamN;j++){
                letra+=mensaje[j+i];
            }
            num=StringtoZZ(letra);
            //cout<<letra<<endl;
            //cout<<KM<<endl<<p<<endl<<inversoMult(KM,p)<<endl;
            letra=ZZtoString(modulo(num*inversoMult(KM,p),p));
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
    int bits=1024;
    cout<<"Cifrador RSA"<<endl;
    Gamal receptor(bits);
    ofstream claves;
    claves.open("claves.txt");
    claves<<"e1:"<<receptor.e1<<endl<<endl<<"e2:"<<receptor.e2<<endl<<endl<<"p:"<<receptor.p;
    claves.close();
    int o=1;
    while(o!=0){
        cout<<endl<<"0: Cerrar el programa"<<endl<<"1:Cifrar un mensaje"<<endl<<"2:Descifrar un mensaje"<<endl;
        cin>>o;
        if(o==1){
            string a, b, c;
            ifstream clave_e1, clave_e2, clave_p;
            clave_e1.open("clave e1.txt");
            getline(clave_e1,a);
            clave_e2.open("clave e2.txt");
            getline(clave_e2,b);
            clave_p.open("clave p.txt");
            getline(clave_p,c);
            Gamal emisor(StringtoZZ(a),StringtoZZ(b),StringtoZZ(c),bits);
            ifstream ficheroEntrada;
            string mensaje;
            ficheroEntrada.open ("temp.txt");
            getline(ficheroEntrada,mensaje);
            ficheroEntrada.close();
            ofstream ficheroSalida;
            ficheroSalida.open("mensaje.txt");
            ficheroSalida<<emisor.encriptar(mensaje);
            ficheroSalida.close();
            }
        if(o==2){
            ifstream entrada;
            string mess;
            entrada.open ("recibido.txt");
            getline(entrada,mess);
            cout << receptor.desencriptar(mess);
        }
        }
}
