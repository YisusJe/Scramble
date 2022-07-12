#include <iostream>
#include <vector>

using namespace std;

class Diccionario{
	
	private:
		vector<const char*> palabras;
	public:
		Diccionario();
		bool buscar(const char* palabra);
};
