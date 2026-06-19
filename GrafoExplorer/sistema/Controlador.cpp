#include "Controlador.h"
#include "GeneradorGrafo.h"
#include "../interfaz/PantallaConfig.h"
#include "../interfaz/Visualizador.h"

Controlador::Controlador() {
	grafoBase = nullptr;
	resultado = nullptr;
}

Controlador::~Controlador() {
	delete resultado;
	delete grafoBase;
}

int Controlador::iniciar() {
	
}

Grafo* Controlador::ejecutarAlgoritmo(Algoritmo algoritmo, int nodoInicio, int nodoDestino)
{
	return nullptr;
}
