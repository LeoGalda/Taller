#include <arpa/inet.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Paquete.h"
#include "Empaquetador.h"

using namespace std;

Paquete* procesarLinea(const string &linea){
	string substring;
	size_t inicio = 0;
	size_t siguiente = linea.find("=");
	substring = linea.substr(inicio,siguiente-inicio);
	int id = atoi(substring.c_str());	
	inicio = siguiente + 1;	
	siguiente = linea.find(",");
	string nombre = linea.substr(inicio,siguiente-inicio);
	inicio = siguiente + 1;	
	int limite = atoi(linea.substr(inicio).c_str());
	Paquete* paquete = new Paquete(id,nombre,limite);
	return paquete;
}

void leerConfiguracion(char *arch,Empaquetador &empaquetador){
	ifstream archivo(arch); 
	char input[128];	
	while(!archivo.eof()){			
		archivo.getline(input,sizeof(input));
		string linea = input;
		if(!linea.empty()){		
			empaquetador.agregarPaquete(procesarLinea(linea));
		}		
	}
	archivo.close();
}


bool getEndiannes(){
	int16_t i = 1;
   	int8_t *p = (int8_t *) &i;

   	if (p[0] == 1){
   		return false;
   	}
   	return true;
}

void ejecutarLogicaBig(){
	cout <<"logica big\n";
}


void leerNombre(ifstream &arch){
	char input[2];	
	char nombre[128];	
	char remanente = 0x00;
	int i = 0;
	do{
		arch.getline(input,sizeof(input) * 2);		
		printf("%X\n",input[0]);
		printf("%X\n",input[1]);
		if(input[1] == 0x00){
			nombre[i] = input[1];
			remanente = input[0];
			i++;
		}else{
			nombre[i] = input[1];
			i++;
			nombre[i] = input[0];
			i++;
		}		
	} while((input[0] != 0x00) && (input[1] != 0x00));
	printf("aca termine");
	for(int j=0; j < i; j++){
		printf("%X",nombre[j]);
	}
	printf("\n");
	printf("remanente: %0X\n",remanente);
}

void parsearArchivo(char *ruta){
	ifstream arch;
	arch.open(ruta, std::ifstream::binary);
//	bool soyBigEndian = getEndiannes();	
	leerNombre(arch);		
	cout<< ruta <<":se estable conexion con el dispositivo";
/*	while(!arch.eof()){			
		arch.getline(input,sizeof(input) * 4);		
		memcpy(&magicus,&input,sizeof(magicus));
		printf("%X\n", magicus);
		if(magicus == -1){
			cout <<"ATASCADO MAN\n";
		}else if(soyBigEndian){
			ejecutarLogica();			
		}else{
			htonl(magicus);
			ejecutarLogicaBig();
		}	
	}*/
	arch.close();
}

int main (int argc,char *argv[]){		
	if (argc < 3){
		cout<< "pelotudo\n";
		return 1;
	}
	Empaquetador empaquetador;
	leerConfiguracion(argv[1],empaquetador);	
	for(int j = 2; j < argc; j++){
		parsearArchivo(argv[j]);
	}
	return 0;
}
