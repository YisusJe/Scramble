#include <iostream>
#include "NodoDoble.h"
#include "Bicolas.h"
using namespace std;

int main(int argc, char** argv) {
	enum opciones{ salir, insertIzq, insertDer, eliminaIzq, eliminaDer, impIzq, impDer, impTodos, quedanNodos, cuantosNodosHay, copiaBicola, sonBicolasIguales, borraBicola } opc;
	struct BICOLA *bicolaA;
	struct BICOLA *bicolaB;
	int eleccion, nuevoDato;


	// Se inicializan las dos Bicolas poniéndolas a NULL:
	inicializarBicola( &bicolaA );
	inicializarBicola( &bicolaB );



	// Menú de selección:
	do{
		printf( "\n\n" );
		printf( "Indique que desea hacer con los Nodos de la Bicola:\n\n" );
		printf( "   1. Añadir un Nodo por la izquierda\n" );
		printf( "   2. Añadir un Nodo por la derecha\n" );
		printf( "   3. Eliminar el primer Nodo\n" );
		printf( "   4. Eliminar el ultimo Nodo\n" );
		printf( "   5. Mostrar el primer Nodo\n" );
		printf( "   6. Mostrar el ultimo Nodo\n" );
		printf( "   7. Muestra todos los Nodos\n" );
		printf( "   8. Quedan Nodos?\n" );
		printf( "   9. Cuantos Nodos hay?\n" );
		printf( "  10. Copiar BicolaA a una nueva BicolaB\n" );
		printf( "  11. BicolaA es igual que BicolaB?\n" );
		printf( "  12. Borrar la BicolaA\n\n" );
		printf( "   0. Salir del programa.\n" );


		do{
			scanf( "%i", &eleccion );
		} while( eleccion < 0  &&  eleccion > 12 );
		opc = (enum opciones)(eleccion);


		printf( "\n\n" );


		switch( opc )
		{


			case insertIzq:
				printf( "Introduzca el número entero que contendrá el nuevo Nodo de la Bicola: " );
				scanf( "%i", &nuevoDato );
				insertIzqBicola( &bicolaA, nuevoDato );
			break;



			case insertDer:
				printf( "Introduzca el número entero que contendrá el nuevo Nodo de la Bicola: " );
				scanf( "%i", &nuevoDato );
				insertDerBicola( &bicolaA, nuevoDato);
			break;



			case eliminaIzq:
				eliminaIzqBicola( &bicolaA );
			break;



			case eliminaDer:
				eliminaDerBicola( &bicolaA );
			break;



			case impIzq:
				if( tieneNodosLaBicola( &bicolaA ) )
					printf( "El primer Nodo contiene un: %i\n", bicolaA->primero->elemento.num );
				else
					printf("La Bicola no contiene Nodos");
			break;



			case impDer:
				if( tieneNodosLaBicola( &bicolaA ) )
					printf( "El ultimo Nodo contiene un: %i\n", bicolaA->ultimo->elemento.num );
				else
					printf("La Bicola no contiene Nodos");
			break;



			case impTodos:
				imprimeBicola( &bicolaA );
			break;



			case quedanNodos:
				if( tieneNodosLaBicola( &bicolaA ) )
					printf( "La Bicola contiene Nodos." );
				else
					printf( "La Bicola esta vacía." );

			break;



			case cuantosNodosHay:
				printf( "La Bicola contiene %i Nodos.",  cuantosNodosTieneLaBicola( &bicolaA ) );
			break;



			case copiaBicola:
				copiarLaBicola( &bicolaA, &bicolaB );
			break;



			case sonBicolasIguales:
				if( sonIgualesLasBicolas( &bicolaA, &bicolaB ) )
					printf( "Las Bicolas son idénticas" );
				else
					printf( "Las Bicolas son diferentes" );
			break;



			case borraBicola:
				borraLaBicola( &bicolaA );		// Se borran todos los nodos...
				inicializarBicola( &bicolaA );	// ... y después se inicializa.
			break;



			case salir:
				system("clear");
			break;

		};


	} while( opc != salir );


	// Libera la RAM que pudiera quedar sin liberar:
	borraLaBicola( &bicolaA );
	borraLaBicola( &bicolaB );
	return 0;
}
