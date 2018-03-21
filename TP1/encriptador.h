#ifndef __ENCRIPTADOR_H__
#define __ENCRIPTADOR_H__

// Tipo encriptador_t: encripta los datos.
typedef struct ElementoEncriptador{
	char *dato;
	struct ElementoEncriptador *siguiente;
} Elemento;

typedef struct EncriptadorLista{
	Elemento *inicio;
	int tamaño;
} Encriptador;

// inicializa la instancia this para ser utilizada
// Pre: this apunta un sector valido de memoria
void encriptador_create(Encriptador *this);

void encriptador_encriptar(Encriptador *this, FILE *datos_a_encriptar);

size_t encriptador_get_datos(Encriptador *this);

void encriptador_destroy(Encriptador *this);

#endif
