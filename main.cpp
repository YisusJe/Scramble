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
int marcador1;
int marcadar2;
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
void comprobarLetras(Jugador jugador){
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
		marcador1 += letrasA.size();
	}else if(di.buscar(palabraFinal2)){
		marcador2 += letrasB.size();
	}
	system("PAUSE");	
}
void mostrarLetras(int * fichas){
	cout<<"Tus letras: ";
	for(int i = 0; i<10; i++){
		if(fichas[i] != 0){
			cout<<(char)fichas[i]<<" ";
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
	jugador.eliminarFicha((int)letra);
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

void menuUsuario(Jugador jugador, Jugador rival){
	bool ward = true;
	// mostrar los tableros de cada jugador
		system("cls") ;
		cout<<"Tablero de: "<<jugador.getName()<<"  ";
		if(jugador.getID() == 1){
			imprimeBicola( &bicolaA );
		} else {
			imprimeBicola( &bicolaB );
		}
		cout<<"\t\t\t\t";
		cout<<"Tablero de: "<<rival.getName()<<"  ";
		if(rival.getID() == 1){
			imprimeBicola( &bicolaA );
			
		} else {
			imprimeBicola( &bicolaB );
		}
		cout << endl;
		cout<<"Puntuacion de "<<jugador.getName()<<" -> "<<jugador.getPuntuacion();
		cout<<"\t\t\t\t";
		cout<<"Puntuacion de "<<rival.getName()<<" -> "<<rival.getPuntuacion();
		
		cout<<"\n\n\n\n"<<endl;
		cout<<"Turno del jugador: "<<jugador.getName()<<" /// que desea hacer?"<<endl;
		cout<<"1- Insertar letra"<<endl;
		cout<<"2- Hacer acuerdo de detener partida"<<endl;
		cout<<"3- Retirarse"<<endl;
	while(ward){	    
		
		if(kbhit()){
			char key = getch();
			switch(int(key)){
				case 49:
					mostrarLetras(jugador.getFichas());
					insertarFicha(jugador);
					comprobarLetras(jugador);
					ward = false;
					break;
				case 50:
					hacerAcuerdo(jugador,rival);
					break;
				case 51:
					cout<<"El jugador "<<jugador.getName()<<" se ha rendido"<<endl;
					break;
			}
		}
	}
}

void Juego(){
	char nom1[20], nom2[20];
	int fichas1[10], fichas2[10], *aux, turno = 1;
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
	Jugador jugador1(1, nom1, fichas1), jugador2(2, nom2, fichas2);
	while(true){
		if(turno == 1){
			menuUsuario(jugador1, jugador2);
			turno = 2;
		} else {
			menuUsuario(jugador2, jugador1);
			turno = 1;
		}
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
