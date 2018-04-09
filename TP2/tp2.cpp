#include <algorithm>
#include <arpa/inet.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
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

int calcularMediana(std::vector<int> anchos){
	std::sort(anchos.begin(), anchos.end());	
	int cantidad = anchos.size();	
	if((cantidad % 2) == 0){
		int mitad = cantidad/2;
		int dato = (int) ceil((float) (anchos[mitad] + anchos[mitad - 1])/2);
		return dato;
	}else{
		return anchos[(int)floor(cantidad/2)];
	}
}


void procesarBinarios(int &info, Empaquetador &empaquetador){
	unsigned int tipoTornillo;
	unsigned int cantidad;
	unsigned int ancho;
	tipoTornillo = cantidad  = ancho = info;
	tipoTornillo >>= 27;
	cantidad <<= 5;
	cantidad >>= 10;
	ancho <<= 27;
	ancho >>= 27;
	Paquete *paquete;
	paquete = empaquetador.getPaquetePorTipo(tipoTornillo);;
	paquete->setCantidad(paquete->getCantidad() + cantidad);
	paquete->addAncho(ancho);
	if(paquete->getCantidad() >= paquete->getLimite()){
		int mediana = calcularMediana(paquete->getAnchos());
		printf("Paquete listo: %i tornillos de tipo %s (mediana: %i)\n",
			   paquete->getLimite(),paquete->getNombre().c_str(),mediana);
		paquete->limpiarAnchos();
		paquete->setCantidad(paquete->getCantidad() - paquete->getLimite());
	}
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

void parsearArchivo(char *ruta,Empaquetador &empaquetador){
	ifstream arch;
	bool soyBigEndian = getEndiannes();
	int magicus;
	arch.open(ruta, std::ifstream::binary);
	string nombreClasificador = leerNombre(arch);		
	cout<< ruta <<" :se estable conexion con el dispositivo "<< nombreClasificador <<"\n";
	char input[4];
	while(!arch.eof()){
		arch.get(input,sizeof(input)+1);			
		memcpy(&magicus,&input,sizeof(magicus));		
		if(magicus == -1){
			cout <<"ATASCADO MAN\n";
		}else if (soyBigEndian){
			procesarBinarios(magicus,empaquetador);
		}else{			
			magicus = htonl(magicus);
			procesarBinarios(magicus,empaquetador);
		}			
	}
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
		parsearArchivo(argv[j],empaquetador);
	}
	empaquetador.mostrarRemanentes();
	return 0;
}
