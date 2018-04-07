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

void ejecutarLogica(){
	cout <<"logica big\n";
}


string leerNombre(ifstream &arch){
	char input[128];
	for(int i = 0;i < 128;i++)	{
		input[i] = 00;
	}
	string nombreClasificador;
	arch.getline(input,sizeof(input),'\0');		
	nombreClasificador = input;
	return nombreClasificador;
}

void parsearArchivo(char *ruta){
	ifstream arch;
/*	int magicus;*/
	arch.open(ruta, std::ifstream::binary);
	string nombreClasificador = leerNombre(arch);		
	cout<< ruta <<" :se estable conexion con el dispositivo "<< nombreClasificador <<"\n";
	char input[4];
	while(!arch.eof()){
		arch.get(input,sizeof(input)+1);		
		printf("%X\n", input[0]);
		printf("%X\n", input[1]);
		printf("%X\n", input[2]);
		printf("%X\n", input[3]);
		printf("PENSA\n");
/*		memcpy(&magicus,&input,sizeof(magicus));		
		if(magicus == -1){
			cout <<"ATASCADO MAN\n";
		}else if(soyBigEndian){
			ejecutarLogica();			
		}else{
			cout<<"little!\n";
			ejecutarLogica();*/
		}	
/*	}*/
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
