#include <iostream>
#include <vector>

using namespace std;

class Diccionario{
	
	private:
		vector<const char*> palabras;
	public:
		Diccionario();
		void buscar(const char* palabra);
};
