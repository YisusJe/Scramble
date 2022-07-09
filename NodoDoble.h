#ifndef NODO_DOBLE_H
#define NODO_DOBLE_H

class NodoDoble
{
	public: 
		int val;
		NodoDoble *sig;
		NodoDoble *ant;
		void agregar(int);
		void presentarInicio();
		void presentarFinal();
		void llenar();
		int buscar(int);
		void modificar(int);
		void eliminar(int);
};
#endif
