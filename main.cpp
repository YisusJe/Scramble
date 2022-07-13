#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <cstdlib>
#include "NodoDoble.h"
#include "Bicolas.h"
#include "Jugador.h"
#include "Diccionario.h"

using namespace std;

NodoDoble * chars;
void Juego();
int sacarFicha();
Jugador jugador1(1), jugador2(2);
int marcador1;
int marcador2;
struct BICOLA *bicolaA;
struct BICOLA *bicolaB;

void menu(){
	cout<<"Presione 1 para jugar"<<endl;
	cout<<"Presione 2 para salir"<<endl;
	bool ward = true;
	while(ward){
		if(kbhit()){
			char key = getch();
			switch(int(key)){
				case 49:
					system("cls");
					Juego();
					break;
				case 50:
					ward = false;
					break;
			}
		}
	}
}

void sacarLetras (int userId){
	cout<<"**** Completaste una palabra ****"<<endl;
	cout<<"Puedes sacar fichas de tu tablero o sacar del monton"<<endl;
	cout<<"1- para sacar ficha por la izquierda"<<endl;
	cout<<"2- para sacar ficha por la derecha"<<endl;
	cout<<"3- terminar de sacar fichas con el monton"<<endl;
	bool ward = true;
	int element;
	while(ward){
		if((userId == 1 && tieneNodosLaBicola ( &bicolaA ) == 0) || (userId == 2 && tieneNodosLaBicola ( &bicolaB ) == 0)) return;
		if(kbhit()){
			char key = getch();
			switch(int(key)){
				case 49:
					if(userId == 1){
						element = eliminaIzqBicola( &bicolaA );
						jugador1.aniadirFicha(element);
					} else {
						element = eliminaIzqBicola( &bicolaB );
						jugador2.aniadirFicha(element);
					}
					break;
				case 50:
					if(userId == 1){
						element = eliminaDerBicola( &bicolaA );
						jugador1.aniadirFicha(element);
					} else {
						element = eliminaDerBicola( &bicolaB );
						jugador2.aniadirFicha(element);
					}
					break;
				case 51:
					if(userId == 1){
						for(int i = 0; i <= jugador1.fichasLongitud(); i++){
							jugador1.aniadirFicha(sacarFicha());
							eliminaDerBicola( &bicolaA );
						}
					} else {
						for(int i = 0; i < jugador2.fichasLongitud(); i++){
							jugador2.aniadirFicha(sacarFicha());
							eliminaDerBicola( &bicolaB );
						}
					}
			}
			if(!(userId == 1 && tieneNodosLaBicola ( &bicolaA ) == 0) || (userId == 2 && tieneNodosLaBicola ( &bicolaB ) == 0)){
				cout<<"Puedes sacar fichas de tu tablero o sacar del monton"<<endl;
				cout<<"1- para sacar ficha por la izquierda"<<endl;
				cout<<"2- para sacar ficha por la derecha"<<endl;
				cout<<"3- terminar de sacar fichas con el monton"<<endl;
			}
		}
			
	}
}

void comprobarLetras(){
	Diccionario di;
	vector<char> letrasA,letrasB;
	
	letrasA = getLetras(&bicolaA);
	letrasB = getLetras(&bicolaB);
	
	char palabra1[letrasA.size()];
	char palabra2[letrasB.size()];
	
	if(letrasA.size() > 0)
	for(int i=0; i < letrasA.size(); i++){	palabra1[i] = letrasA.at(i); }
	
	if(letrasB.size() > 0)
	for(int j=0; j < letrasB.size(); j++){	palabra2[j] = letrasB.at(j); }
	
	cout << palabra1 << endl;
	cout << palabra2 << endl;
	const char *palabraFinal1 = palabra1;
	const char *palabraFinal2 = palabra2;
	if(di.buscar(palabraFinal1)){
		jugador1.addPuntos(letrasA.size());
		sacarLetras(1);
	}else if(di.buscar(palabraFinal2)){
		jugador2.addPuntos(letrasB.size());
		sacarLetras(2);
	}
	system("PAUSE");	
}
void mostrarLetras(int * fichas){
	cout<<"Tus letras: ";
	for(int i = 0; i<10; i++){
		if(fichas[i] != 1){
			cout<<(char)fichas[i]<<" | ";
		}
	}
}

bool comprobarFichaDeUsuario (Jugador jugador, char letra){
	int * fichas = jugador.getFichas();
	for(int i = 0; i < 10; i++){
		if(char(fichas[i]) == letra){ // si existe en el mazo del usuario
			return false;
		}
	}
	cout<<"Letra no encontrada"<<endl;
	return true;
}

void insertarFicha(Jugador jugador){
	bool ward = true;
	char letra;
	while(ward){
		cout<<endl<<"Que letra desea insertar"<<endl;
		fflush(stdin);
		cin>>letra;
		ward = comprobarFichaDeUsuario(jugador, letra);
	}
	//insertar ahora ficha en el tablero del jugador
	(jugador.getID() == 1)? jugador1.eliminarFicha((int)letra): jugador2.eliminarFicha((int)letra);
	
	int op;
	cout << "Donde colocara su Letra:" << endl;
	cout << "1.Al Inicio" << endl;
	cout << "2.Al Final" << endl;
	cin>>op;
	if(jugador.getID() == 1){
		if( op == 1){
			insertIzqBicola( &bicolaA, (int)letra);
		}else if(op == 2){
			insertDerBicola( &bicolaA, (int)letra);
		}
	}else if(jugador.getID() == 2){
		if( op == 1){
			insertIzqBicola( &bicolaB, (int)letra);
		}else if(op == 2){
			insertDerBicola( &bicolaB, (int)letra);
		}
		
	}
}

void Recuento(Jugador jugador, Jugador rival){
	cout<<"Puntuacion de "<<jugador.getName()<<" -> "<<jugador.getPuntuacion();
	cout<<"Puntuacion de "<<jugador.getName()<<" -> "<<rival.getPuntuacion();
	if(jugador.getPuntuacion() > rival.getPuntuacion()){
		cout<<"El jugador "<<jugador.getName()<<" Ha ganado!"<<endl;
	} else if(jugador.getPuntuacion() < rival.getPuntuacion()){
		cout<<"El jugador "<<rival.getName()<<" Ha ganado!"<<endl;
	} else {
		cout<<"Empate!"<<endl;
	}
	cout<<"Fin del juego"<<endl;
}

void hacerAcuerdo(Jugador jugador, Jugador rival){
	bool ward = true;
	cout<<rival.getName()<<" quieres terminar la partida?"<<endl;
	cout<<"1- Si, 2- No"<<endl;
	while(ward){
		if(kbhit()){
			char key = getch();
			switch(int(key)){
				case 49:
					cout<<"Juego Terminado"<<endl;
					Recuento(jugador,rival);
					break;
				case 50:
					cout<<"Acuerdo rechazado"<<endl;
					ward = false;
					system("pause");
					break;
			}
		}
	}
}

void menuUsuario(int turno){
	bool ward = true;
	// mostrar los tableros de cada jugador
		system("cls") ;
		cout<<"Tablero de: "<<jugador1.getName()<<"  ";
		if(jugador1.getID() == 1){
			imprimeBicola( &bicolaA );
		}
		cout<<"\t\t\t\t";
		cout<<"Tablero de: "<<jugador2.getName()<<"  ";
		if(jugador2.getID() == 2){
			imprimeBicola( &bicolaB );	
		}
		cout << endl;
		cout<<"Puntuacion de "<<jugador1.getName()<<" -> "<<jugador1.getPuntuacion();
		cout<<"\t\t\t\t";
		cout<<"Puntuacion de "<<jugador2.getName()<<" -> "<<jugador2.getPuntuacion();
		
		cout<<"\n\n\n\n"<<endl;
		string texto = (turno == 1)?jugador1.getName(): jugador2.getName();
		cout<<"Turno del jugador: "<< texto <<" /// que desea hacer?"<<endl;
		cout<<"1- Insertar letra"<<endl;
		cout<<"2- Hacer acuerdo de detener partida"<<endl;
		cout<<"3- Retirarse"<<endl;
	while(ward){	    
		
		if(kbhit()){
			char key = getch();
			switch(int(key)){
				case 49:
					if(turno == 1){
						mostrarLetras(jugador1.getFichas());
						insertarFicha(jugador1);
						comprobarLetras();
					}else {
						mostrarLetras(jugador2.getFichas());
						insertarFicha(jugador2);
						comprobarLetras();	
					}
					ward = false;
					break;
				case 50:
					hacerAcuerdo(jugador1,jugador2);
					break;
				case 51:
					cout<<"El jugador "<<(turno == 1)?jugador1.getName(): jugador2.getName();
					cout <<" se ha rendido"<<endl;
					break;
			}
		}
	}
}

void Juego(){
	char nom1[20], nom2[20];
	int fichas1[10], fichas2[10], *aux, turno = 2;
	bool empatar = false;
	cout<<"Ingrese el nombre del jugador 1"<<endl;
	cin.getline(nom1, 20);
	fflush(stdin);
	cout<<"Ingrese el nombre del jugador 2"<<endl;
	cin.getline(nom2, 20);
	fflush(stdin);
	for(int i=0;i<10;i++){
		fichas1[i] = sacarFicha();
	}
	for(int i=0;i<10;i++){
		fichas2[i] = sacarFicha();
	}
//	Jugador jugador1(1, nom1, fichas1), jugador2(2, nom2, fichas2);
	jugador1.setName(nom1);
	jugador1.setFichas(fichas1);
	jugador2.setName(nom2);
	jugador2.setFichas(fichas2);

	while(true){
		
		if(turno%2 == 0){
			menuUsuario(1);	
		}else{
			menuUsuario(2);
		}
		turno++;
	}
}

int sacarFicha(){ // generar numero random entre 97 y 122
	bool ward = true;
	int x;
	while (ward) { // ciclo de buscar numeros, en caso de encontrarlo -> eliminarlo, si no seguir buscando numeros
		x = 97+rand()%(123-97);
		cout<<(char)chars->buscar(x)<<endl; 
		if(x){ 
			chars->eliminar(x);
			ward = false;
		}
	}
	return x;
}


int main(int argc, char** argv) {
	
	int cont = 0;
	for(int i = 97; i <= 122; i++){
		for(int j = 0; j < 5; j++){
			chars->agregar(i);
		}
	}
	inicializarBicola( &bicolaA );
	inicializarBicola( &bicolaB );

	menu();
	return 0;
}
