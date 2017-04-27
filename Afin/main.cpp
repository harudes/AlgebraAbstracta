#include <iostream>
#include <NTL/ZZ.h>
#include "AriMod.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

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
        int pos;
        ZZ A_temp=modulo(A,to_ZZ(tam));
        ZZ B_temp=modulo(B,to_ZZ(tam));
        for(int i = 0; i <= mensaje.size(); i++){
            pos=alfabeto.find(mensaje[i]);
            pos=to_int(modulo(to_ZZ(pos)*A_temp,to_ZZ(tam)));
            pos=to_int(modulo(to_ZZ(pos)+B_temp,to_ZZ(tam)));
            mensaje[i]=alfabeto[pos];
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
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
