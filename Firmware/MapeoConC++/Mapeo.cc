
#include<iostream>
#include<stdlib.h>

using namespace std;

class Punto{
private:
    char Arriba;
    char Abajo;
    char Derecha;
    char Izquierda;
public:
    Punto(char,char,char,char);
    char imprimirArriba();
    char imprimirAbajo();
    char imprimirIzquierda();
    char imprimirDerecha();


 };

 Punto::Punto(char arriba,char abajo,char derecha,char izquierda){
    Arriba=arriba;
    Abajo=abajo;
    Derecha=derecha;
    Izquierda=izquierda;
 }
   char Punto::imprimirArriba()
   {
    if(Arriba=='Y'){
      return '_';
    }else{
      return ' ';
    }
   }

    char Punto::imprimirAbajo()
   {
    if(Abajo=='Y'){
      return '_';
    }else{
      return ' ';
    }
   }

    char Punto::imprimirDerecha()
   {
    if(Derecha=='Y'){
      return '|';
    }else{
      return ' ';
    }
   }

    char Punto::imprimirIzquierda()
   {
    if(Izquierda=='Y'){
      return '|';
    }else{
      return ' ';
    }
   }

   int main(){

   //(ARRIBA,ABAJO,DERECHA,IZQUIERDA)
   Punto P11('N','N','Y','Y');
   Punto P12('N','Y','N','Y');
   Punto P13('N','Y','Y','N');
   Punto P14('N','Y','Y','Y');
   Punto P21('N','N','Y','Y');
   Punto P22('N','N','Y','Y');
   Punto P23('Y','N','N','Y');
   Punto P24('N','N','Y','N');
   Punto P31('Y','N','N','Y');
   Punto P32('Y','N','N','N');
   Punto P33('N','Y','Y','N');
   Punto P34('N','N','Y','Y');
   Punto P41('Y','Y','N','Y');
   Punto P42('Y','Y','N','N');
   Punto P43('Y','N','Y','N');
   Punto P44('Y','N','Y','Y');
   //pared arriba 41,42,43,44

cout<<"\n";
cout<<"  ";
cout<<P41.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P42.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P43.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P44.imprimirArriba();
cout<<"   ";


//pintad Izquierda,abajo Derecha 41,42,43,44
cout<<"\n";
cout<<P41.imprimirIzquierda();
cout<<" ";
cout<<P41.imprimirAbajo();
cout<<" ";
cout<<P41.imprimirDerecha();
cout<<" ";

cout<<P42.imprimirIzquierda();
cout<<" ";
cout<<P42.imprimirAbajo();
cout<<" ";
cout<<P42.imprimirDerecha();
cout<<" ";

cout<<P43.imprimirIzquierda();
cout<<" ";
cout<<P43.imprimirAbajo();
cout<<" ";
cout<<P43.imprimirDerecha();
cout<<" ";

cout<<P44.imprimirIzquierda();
cout<<" ";
cout<<P44.imprimirAbajo();
cout<<" ";
cout<<P44.imprimirDerecha();
cout<<" ";

//pared arriba 31,32,33,34
cout<<"\n";
cout<<"  ";
cout<<P31.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P32.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P33.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P34.imprimirArriba();
cout<<"   ";
//pintad Izquierda,abajo Derecha 31,32,33,34
cout<<"\n";
cout<<P31.imprimirIzquierda();
cout<<" ";
cout<<P31.imprimirAbajo();
cout<<" ";
cout<<P31.imprimirDerecha();
cout<<" ";

cout<<P32.imprimirIzquierda();
cout<<" ";
cout<<P32.imprimirAbajo();
cout<<" ";
cout<<P32.imprimirDerecha();
cout<<" ";

cout<<P33.imprimirIzquierda();
cout<<" ";
cout<<P33.imprimirAbajo();
cout<<" ";
cout<<P33.imprimirDerecha();
cout<<" ";

cout<<P34.imprimirIzquierda();
cout<<" ";
cout<<P34.imprimirAbajo();
cout<<" ";
cout<<P34.imprimirDerecha();
cout<<" ";
//pared arriba 21,22,23,24
cout<<"\n";
cout<<"  ";
cout<<P21.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P22.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P23.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P24.imprimirArriba();
cout<<"   ";

//pintar Izquierda,abajo Derecha 21,22,23,24
cout<<"\n";
cout<<P21.imprimirIzquierda();
cout<<" ";
cout<<P21.imprimirAbajo();
cout<<" ";
cout<<P21.imprimirDerecha();
cout<<" ";

cout<<P22.imprimirIzquierda();
cout<<" ";
cout<<P22.imprimirAbajo();
cout<<" ";
cout<<P22.imprimirDerecha();
cout<<" ";

cout<<P23.imprimirIzquierda();
cout<<" ";
cout<<P23.imprimirAbajo();
cout<<" ";
cout<<P23.imprimirDerecha();
cout<<" ";

cout<<P24.imprimirIzquierda();
cout<<" ";
cout<<P24.imprimirAbajo();
cout<<" ";
cout<<P24.imprimirDerecha();
cout<<" ";
//pared arriba 11,12,13,14
cout<<"\n";
cout<<"  ";
cout<<P11.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P12.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P13.imprimirArriba();
cout<<"   ";
cout<<"  ";
cout<<P14.imprimirArriba();
cout<<"   ";
//pintad Izquierda,abajo Derecha 11,12,13,14
cout<<"\n";
cout<<P11.imprimirIzquierda();
cout<<" ";
cout<<P11.imprimirAbajo();
cout<<" ";
cout<<P11.imprimirDerecha();
cout<<" ";

cout<<P12.imprimirIzquierda();
cout<<" ";
cout<<P12.imprimirAbajo();
cout<<" ";
cout<<P12.imprimirDerecha();
cout<<" ";

cout<<P13.imprimirIzquierda();
cout<<" ";
cout<<P13.imprimirAbajo();
cout<<" ";
cout<<P13.imprimirDerecha();
cout<<" ";

cout<<P14.imprimirIzquierda();
cout<<" ";
cout<<P14.imprimirAbajo();
cout<<" ";
cout<<P14.imprimirDerecha();
cout<<" ";

cout<<"\n";
cout<<"\n";


   }
