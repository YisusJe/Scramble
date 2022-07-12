#include <iostream>
#include "Diccionario.h"
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

Diccionario::Diccionario(){
	string linea;
	vector<string> palabras;
	ifstream archivo("diccionario.txt");
	
	while(!archivo.eof()){	
		getline(archivo,linea);
		palabras.push_back(linea);		
	}
	
	for(int i=0;i < palabras.size() ; i++){
		this->palabras.push_back(palabras.at(i).c_str());
	}
	
	
}

void Diccionario::buscar(const char * palabra){
	
	for(int i=0; i < this->palabras.size();i++){
		
		if(strcmp(this->palabras.at(i),palabra) == 0)
		cout << this->palabras.at(i) << endl;
		
	}
}
