#include <iostream>
#include "NodoDoble.h"

using namespace std;


NodoDoble *inicio, *fin, *aux, *aux2;

void NodoDoble::agregar(int x){
	aux = new NodoDoble();
	aux->val=x;
	aux->sig=NULL;
	aux->ant=NULL;
	
	if(inicio==NULL){
		inicio = aux;
	} else {
		fin->sig=aux;
		aux->ant=fin;
	}
	fin=aux;
}

void NodoDoble::presentarInicio(){
	aux=inicio;
	while(aux!=NULL){
		cout<<"ID: "<<aux->val<<endl;
		aux=aux->sig;
	}
}

void NodoDoble::presentarFinal(){
	aux=fin;
	while(aux!=NULL){
		cout<<"ID: "<<aux->val<<endl;
		aux=aux->ant;
	}
}

void NodoDoble::buscar(int x){
	bool ward = false;
	if(x>(fin->val/2)){
		cout<<"por fin"<<endl;
		aux=fin;
		while(aux!=NULL && !ward){
			if(aux->val==x){
				ward = true;
				cout<<"Registro encontrado"<<endl;
			}
			else {
				aux = aux->ant;
			}
		}
	} else {
		cout<<"por inicio"<<endl;
		aux=inicio;
		while(aux!=NULL && !ward){
			if(aux->val==x){
				ward = true;
				cout<<"Registro encontrado"<<endl;
			}
			else {
				aux = aux->sig;
			}
		}
	}
	if(!ward){
		cout<<"Registro no existe"<<endl;
	}
}

void NodoDoble::modificar(int x){
	aux->val=x;
}

void NodoDoble::eliminar(int x){
	buscar(x);
	if(aux!=NULL){
		if(aux==inicio){
			inicio=aux->sig;
			aux=inicio;
			aux->ant=NULL;
		} else if (fin == aux){
			fin = aux->ant;
			aux=fin;
			aux->sig=NULL;
		} else {
			aux2=aux->ant;
			aux2->sig=aux->sig;
			aux=aux->sig;
			aux->ant=aux2;
		}
	}
}
