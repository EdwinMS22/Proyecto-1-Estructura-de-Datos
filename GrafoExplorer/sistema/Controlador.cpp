#include "Controlador.h"
#include "GeneradorGrafo.h"
#include "../algoritmos/Dfs.h"
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
	ventana.create(sf::VideoMode({700, 700}),
		"GrafoExplorer - Configuracion",
		sf::Style::Titlebar | sf::Style::Close);

	PantallaConfig pantalla(ventana);
	if (!pantalla.ejecutar(config))
		return 0;

	GeneradorGrafo generador(config.cantidadNodos, config.distanciaConexion,
							 config.maximoVecinos, config.anchoVentana, config.altoVentana);
	grafoBase = generarGrafo();

	Visualizador visualizador(ventana, config, grafoBase, *this);
	visualizador.ejecutar();
	
	return 0;
}

Grafo* Controlador::generarGrafo() {
	GeneradorGrafo generador(config.cantidadNodos, config.distanciaConexion,
							 config.maximoVecinos, config.anchoVentana, config.altoVentana,
							 20, static_cast<int>(Visualizador::ALTO_HUD));
	return generador.generar();
}

Grafo* Controlador::regenerarGrafo() {
	delete resultado;
	resultado = nullptr;
	delete grafoBase;
	grafoBase = generarGrafo();
	return grafoBase;
}

Grafo* Controlador::ejecutarAlgoritmo(Algoritmo algoritmo, int nodoInicio, int nodoDestino) {
	delete resultado;
	resultado = nullptr;

	switch (algoritmo) {
		case Algoritmo::DFS:      resultado = dfs(*grafoBase, nodoInicio); break;
		case Algoritmo::BFS:      /* resultado = bfs(*grafoBase, nodoInicio); */ break;
		case Algoritmo::PRIM:     /* resultado = prim(*grafoBase, nodoInicio); */ break;
		case Algoritmo::KRUSKAL:  /* resultado = kruskal(*grafoBase); */ break;
		case Algoritmo::DIJKSTRA: /* resultado = dijkstra(*grafoBase, nodoInicio, nodoDestino); */ break;
	}
	return resultado;
}