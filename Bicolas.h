#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct INFO
{
	int num;
};

struct NODO
{
	struct INFO elemento;
	struct NODO *p_anterior;
	struct NODO *p_siguiente;
};

struct BICOLA
{
	int nodos;
	struct NODO *primero;
	struct NODO *ultimo;
};



/* FUNCIONES ******************************************************************/

// Pone los punteros de una bicola a NULL
void inicializarBicola( struct BICOLA **bicola )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola sin inicializar..
	Poscondici�n:
					Se inicializa la Bicola poni�ndola a NULL o 0 seg�n el par�metro a inicializar.
	*/

	// Se solicita memoria al sistema para la nueva Bicola:
	struct BICOLA *temp = (struct BICOLA *) malloc(sizeof(struct BICOLA));

	temp->nodos		= 0;
	temp->primero	= NULL;
	temp->ultimo	= NULL;

	(*bicola) 		= temp;

};



// Inserta nodos por la izquierda:
void insertIzqBicola( struct BICOLA **bicola, int dato )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola y un par�metro de tipo entero con el dato a introducir.
	Poscondici�n:
					Se inserta al principio un nuevo Nodo en la Bicola.
	*/

	// Se solicita memoria al sistema para el nuevo Nodo:
	struct NODO *temp = (struct NODO *) malloc(sizeof(struct NODO));


	// Si la Bicola no tiene Nodos se inserta sin mas
	if( (*bicola)->primero == NULL )
	{
		temp->elemento.num	= dato;					// Se guarda el nuevo dato en el nuevo Nodo.
		temp->p_anterior	= NULL;					// Como es el primer Nodo de la Bicola, tanto el puntero anterior como el siguiente apuntan a NULL.
		temp->p_siguiente	= NULL;

		(*bicola)->primero	= temp;					// Como es el primer Nodo de la Bicola, se hace que primero y ultimo apunten ambos al mismo Nodo.
		(*bicola)->ultimo	= temp;
	}
	else
	{
		temp->elemento.num	= dato;					// Se guarda el dato nuevo en el nuevo Nodo.
		temp->p_anterior	= NULL;					// Como el nuevo Nodo va a ser el primero de la Bicola no apuntara a ning�n Nodo anterior.
		temp->p_siguiente	= (*bicola)->primero;	// El nuevo Nodo apuntara al siguiente Nodo (donde ahora apunta "primero".

		(*bicola)->primero->p_anterior	= temp;		// El puntero anterior del primer Nodo se hace que apunte al nuevo Nodo.
		(*bicola)->primero				= temp;		// El puntero del primero se hace que apunte al nuevo Nodo que ahora es el primero.
	};


	(*bicola)->nodos += 1;							// Se suma 1 a la variable que guarda el numero de Nodos de la Bicola.

};



// Inserta nodos por la derecha:
void insertDerBicola( struct BICOLA **bicola, int dato )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola y un par�metro de tipo entero con el dato a introducir.
	Poscondici�n:
					Se inserta al final un nuevo Nodo en la Bicola.
	*/


	struct NODO *temp = (struct NODO *) malloc(sizeof(struct NODO));


	// Si la bicola esta vac�a se introduce sin mas:
	if( (*bicola)->primero == NULL )
	{
		temp->elemento.num	= dato;
		temp->p_anterior	= NULL;
		temp->p_siguiente	= NULL;

		(*bicola)->primero	= temp;
		(*bicola)->ultimo	= temp;
	}
	  // Si contiene nodos, se introduce al final de todos ellos:
	else
	{
		temp->elemento.num	= dato;
		temp->p_anterior	= (*bicola)->ultimo;
		temp->p_siguiente	= NULL;

		(*bicola)->ultimo->p_siguiente	= temp;
		(*bicola)->ultimo				= temp;
	};


	(*bicola)->nodos += 1;

};



// Elimina el primer Nodo:
void eliminaIzqBicola( struct BICOLA **bicola )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola.
	Poscondici�n:
					Se elimina el primer Nodo de la Bicola.
	*/


	struct NODO *aBorrar;


	// Si la Bicola esta vac�a...
	if( (*bicola)->primero == NULL )
	{
		printf( "No puede eliminar Nodos de una Bicola vac�a." );
	}
	  // Si solo hay un Nodo en la Bicola, al liberar la RAM del Nodo se inicializa la Bicola a los valores por defecto:
	else if( (*bicola)->nodos == 1)
	{
		free(*bicola);
		inicializarBicola( bicola );
	}
	  // En caso contrario se elimina solo el primer Nodo:
	else if( (*bicola)->nodos > 1 )
	{
		aBorrar = (*bicola)->primero;

		(*bicola)->primero->p_siguiente->p_anterior	= NULL;
		(*bicola)->primero							= (*bicola)->primero->p_siguiente;
		free(aBorrar);

		(*bicola)->nodos -= 1;
	};

};



// Elimina el ultimo Nodo:
void eliminaDerBicola( struct BICOLA **bicola )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola.
	Poscondici�n:
					Se elimina el ultimo Nodo de la Bicola.
	*/


	struct NODO *aBorrar;


	// Si la Bicola esta vacia...
	if( (*bicola)->primero == NULL )
	{
		printf( "No puede eliminar Nodos de una Bicola vac�a." );
	}
	  // Si solo hay un Nodo en la Bicola, al liberar la RAM del Nodo se inicializa la Bicola a los valores por defecto:
	else if( (*bicola)->nodos == 1 )
	{
		free(*bicola);
		inicializarBicola( bicola );
	}
	else if( (*bicola)->nodos > 1 )
	{
		aBorrar = (*bicola)->ultimo;

		(*bicola)->ultimo->p_anterior->p_siguiente	= NULL;
		(*bicola)->ultimo							= (*bicola)->ultimo->p_anterior;
		free(aBorrar);

		(*bicola)->nodos -= 1;
	};

};



// Devuelve un true o un false si la Bicola contiene o no Nodos:
int tieneNodosLaBicola( struct BICOLA **bicola )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola.
	Poscondici�n:
					Se devuelve un par�metro de tipo entero con valores true 1 o false 0 dependiendo de si la Bicola contiene Nodos o no.
	*/


	int resp = 0;

	if( (*bicola)->nodos != 0 )
		resp = 1;

	return resp;
};



// Libera la memoria RAM usada por la Bicola:
void borraLaBicola( struct BICOLA **bicola )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola.
	Poscondici�n:
					Se libera la RAM usada por los Nodos contenidos en la Bicola.
	*/


	struct NODO *actual, *siguiente;
	actual = (*bicola)->primero;

	while( actual != NULL )
	{
		siguiente = actual->p_siguiente;
		free(actual);
		actual = siguiente;
	};

	*bicola = NULL;
};



// Devuelve el n�mero de Nodos que contiene la Bicola:
int cuantosNodosTieneLaBicola( struct BICOLA **bicola )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola.
	Poscondici�n:
					Se devuelve un par�metro de tipo entero que indica el n�mero de Nodos que contiene la Bicola.
	*/

	return (*bicola)->nodos;
};



// Copia la bicola original a la bicola copia:
void copiarLaBicola( struct BICOLA **bicolaA, struct BICOLA **bicolaB )
{
	/*
	Precondici�n:
					Se han de recibir dos dobles punteros de tipo struct BICOLA a dos Bicolas.
	Poscondici�n:
					Se copia �ntegramente la BicolaA en la BicolaB
	*/


	struct NODO *temp = (*bicolaA)->primero;


	// Si la BicolaB no esta vacia, se libera la RAM antes de copiar la BicolaA en BicolaB.
	if( (*bicolaB)->primero != NULL )
	{
		borraLaBicola( bicolaB );		// Se borra y se inicializa.
		inicializarBicola( bicolaB );
	};



	if( temp == NULL )
		printf( "La Bicola A no contiene Nodos, no se puede copiar nada." );
	else
	{
		while( temp != NULL )
		{
			// Se inserta al final:
			insertDerBicola( bicolaB, temp->elemento.num );

			// Se avanza un Nodo hacia delante:
			temp = temp->p_siguiente;
		};

	};

};



// Compara dos bicolas, devuelve true o false
int sonIgualesLasBicolas( struct BICOLA **bicolaA, struct BICOLA **bicolaB )
{
	/*
	Precondici�n:
					Se han de recibir dos dobles punteros de tipo struct BICOLA a dos Bicolas.
	Poscondici�n:
					Se devuelve un true 1 si las dos Bicolas son id�nticas. En caso de que haya alguna diferencia entre ellas, ya sea en el contenido de sus Nodos o en la longitud de las Bicolas se devolver� un false 0.
	*/


	struct NODO *bicA = (*bicolaA)->primero;
	struct NODO *bicB = (*bicolaB)->primero;
	int salirBucle=0, resp=1;


	if( bicA == NULL ||  bicB == NULL )
	{
		resp = 0;

		if( bicA == NULL )
			printf( "Debe de insertar antes alg�n Nodo en la Bicola A\n" );

		if( bicB == NULL )
			printf( "Debe de insertar antes alg�n Nodo en la Bicola B\n" );
	}
	else
	{
		while( !salirBucle )
		{
			// Si alguno de los datos (num en este caso) del elemento de cada Nodo de la Bicola es diferente de la copia, devuelve false:
			if( bicA->elemento.num != bicB->elemento.num )
			{
				resp = 0;
				salirBucle = 1;
			}
			 // Si todo es igual...
			else
			{
				// Si los dos punteros siguen a puntando a algo diferente de NULL se avanza una posici�n:
				bicA = bicA->p_siguiente;
				bicB = bicB->p_siguiente;


				// Si alguno de los dos punteros ha llegado a NULL antes que el otro, las Bicolas est�n mal copiadas:
				if( (bicA != NULL  &&  bicB == NULL)  ||  (bicA == NULL  &&  bicB != NULL) )
				{
					resp = 0;
					salirBucle = 1;
				}
				  // Si por el contrario, las dos est�n a NULL a la vez, se termina la iteraci�n y se devuelve true;
				else if( (bicA == NULL  &&  bicB == NULL) )
				{
					salirBucle = 1;
				};

			};

		};

	};

	return resp;

};



// imprime por pantalla el contenido de todos los Nodos de la Bicola:
void imprimeBicola( struct BICOLA **bicola )
{
	/*
	Precondici�n:
					Se recibe un doble puntero de tipo struct BICOLA a una Bicola.
	Poscondici�n:
					Se imprime por pantalla el contenido de todos los Nodos.
	*/


	struct NODO *bic = (*bicola)->primero;



	if( bic == NULL )
		// printf( "La Bicola no contiene Nodos." );
		printf("");
	else
	{

		// printf( "Su Bicola contiene: " );

		while( bic != NULL )
		{
			printf("%c", bic->elemento.num);
			bic = bic->p_siguiente;
		};


	};

};


void verificarPalabraPalindromo (){
}
