#include <fstream>
#include <iostream>
#include <cstdlib>
#include "ConfigPaquete.h"
#include "Empaquetador.h"

using namespace std;

ConfigPaquete* procesarLinea(string linea){
	ConfigPaquete *config;
	config = new ConfigPaquete();
	string substring;
	size_t inicio = 0;
	size_t siguiente = linea.find("=");
	substring = linea.substr(inicio,siguiente-inicio);
	int id = atoi(substring.c_str());	
	if(id != 0){
		config->setId(id);	
		inicio = siguiente + 1;	
		siguiente = linea.find(",");
		string nombre = linea.substr(inicio,siguiente-inicio);
		config->setNombre(nombre);
		inicio = siguiente + 1;	
		int limite = atoi(linea.substr(inicio).c_str());
		config->setLimite(limite);
	}
	return config;
}

void leerConfiguracion(char *arch,vector<ConfigPaquete*> *empaquetador){
	ifstream archivo(arch); 
	char input[128];	
	while(!archivo.eof()){			
		archivo.getline(input,sizeof(input));
		string linea = input;
		if(!linea.empty()){		
			empaquetador->push_back(procesarLinea(linea));
		}
	}
	archivo.close();
}


int main (int argc,char *argv[]){		
	if (argc < 2){
		printf("Pelotudo");
		return 1;
	}
	vector<ConfigPaquete*> empaquetador;
	leerConfiguracion(argv[1],&empaquetador);
	ConfigPaquete *paquete;
	for (size_t i = 0; i < empaquetador.size(); ++i) {
    	delete empaquetador[i]; 	
	}
	empaquetador.clear();
	return 0;
}

