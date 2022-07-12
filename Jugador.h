#include <cstring>

class Jugador{
	private:
		int id;
		char name[20];
		int fichas[10];
		int puntos;
	public:
		Jugador (int id, char * name, int * fichas){
			this->id=id;
			strcpy(this->name, name);
			for(int i = 0; i < 10; i++){
				this->fichas[i] = fichas[i];
			}
		}
		int * getFichas(){
			return fichas;
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
        	for(int i = 0; i<10; i++){
//        		cout<<fichas[i]<<" y "<<letra<<endl;
        		if(letra == fichas[i]){
        			fichas[i]=0;
        			break;
				}
			}
        }
};
