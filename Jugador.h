#include <cstring>

class Jugador{
	private:
		int id;
		char name[20];
		int fichas[10];
		int puntos;
	public:
		Jugador(int id){
			this->id = id; 
			strcpy(name, "Jugador");
			puntos = 0;
		}
		Jugador (int id, char * name, int * fichas){
			this->id=id;
			strcpy(this->name, name);
			for(int i = 0; i < 10; i++){
				this->fichas[i] = fichas[i];
			}
		}
		void setFichas(int *fichas){
			for(int i = 0; i < 10; i++){
				this->fichas[i] = fichas[i];
			}
		}
		int * getFichas(){
			return fichas;
		}
		void setName(char name[20]){
			strcpy(this->name, name);
		}
		char * getName(){
			return name;
		}
		
		int getPuntuacion(){
			return puntos;
		}
		int getID(){
            return id;
        }
        void eliminarFicha(int letra){
        	bool encontrado = true;
        	int i = 0;
        	while(encontrado){
//        		cout<<this->fichas[i]<<" y "<<letra<<endl;
        		if(letra == fichas[i]){
        			cout << "elimanada la letra: " << fichas[i]<< endl; 
        			this->fichas[i]=1;
        			encontrado = false;
				}
				i++;
			}
        }
        void addPuntos(int puntos){
        	this->puntos += puntos;
		}
};
