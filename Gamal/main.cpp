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
    ZZ Km;
    string alfabeto;
    void generar_claves_receptor(int bits){
        p=ga(30,bits,8,10);
        e1=find_root(p);
        d=modulo(ga(30,bits,9,8),p-to_ZZ(5))+to_ZZ(3);
        e2=potenciaMod(e1,d,p);
    }
    void generar_claves_emisor(int bits){
        ZZ r=modulo(ga(30,bits,9,8),p-to_ZZ(5))+to_ZZ(3);
        c1=potenciaMod(e1,r,p);
        Km=potenciaMod(e2,r,p);
    }
public:
    ZZ e1;
    ZZ e2;
    ZZ p;
    ZZ c1;
    Gamal(int bits){
        generar_claves_receptor(bits);
        alfabeto="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
    }
    Gamal(ZZ E1,ZZ E2,ZZ P,int bits){
        e1=E1;
        e2=E2;
        p=P;
        generar_claves_emisor(bits);
        alfabeto="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,;";
    }
    string encriptar(string mensaje){
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
        return message;
    }
    string desencriptar(ZZ C1, string mensaje){
        string message;
        string letra;
        string temp;
        string aux;
        ZZ num;
        ZZ KM=potenciaMod(C1,d,p);
        cout<<KM<<endl;
        cout<<p<<endl;
        cout<<inversoMult(KM,p)<<endl;
        int tam = ZZtoString(to_ZZ(alfabeto.length()-1)).length();
        int tamN= ZZtoString(p).length();
        for(int i=0;i<mensaje.length();i+=tamN){
            letra="";
            for(int j=0;j<tamN;j++){
                letra+=mensaje[j+i];
            }
            num=StringtoZZ(letra);
            //cout<<letra<<endl;
            //cout<<KM<<endl<<p<<endl<<inversoMult(KM,p)<<endl;
            letra=ZZtoString(modulo(num*inversoMult(KM,p),p));
            cout<<"Se desencripto una letra"<<endl;
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

int main()
{
    srand(time(NULL));
    Gamal receptor(1024);
    Gamal emisor(receptor.e1,receptor.e2,receptor.p,1024);
    string mensaje=emisor.encriptar("I have made over one thousand blades. But, jet, those hands will never hold anything. So, as I pray, Unlimited Blade Works.luis.rendon.ucsp.edu.pe. Me gusta el arroz con mango akasdjkasjdklasjdlasjdlksajdklaldjdlkajdlajdaksldjlasjdlkasjdlksajdklasjdslkajdlksajdlkajdlksajdlaslkdsakldlsakjdlasjldkasdalskjdakldja");
    cout<<receptor.desencriptar(emisor.c1,mensaje);
    return 0;
}
