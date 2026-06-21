/*
 * Controlador.cpp
 *
 * Implementación de la clase Controlador. Maneja el ciclo de vida
 * completo de la aplicación: alterna entre la pantalla de
 * configuración y la visualización del grafo, reutilizando la misma 
 * ventana de SFML al recrearla con cada nueva configuración. Administra 
 * la memoria del grafo base y del grafo resultado. Despacha la ejecución 
 * de los algoritmos de grafos según lo solicitado desde la interfaz.
 *
 * Funcionalidades:
 * - Controlador(): inicializa los punteros de grafoBase y resultado en
 *   nullptr.
 * - ~Controlador(): libera la memoria de resultado y grafoBase.
 * - iniciar(): ciclo principal; crea la ventana de configuración,
 *   ejecuta PantallaConfig, genera un nuevo grafo base con la
 *   configuración resultante y lanza el Visualizador.
 * - generarGrafo(): crea un GeneradorGrafo con los parámetros de
 *   config (reservando el margen superior según ALTO_HUD del
 *   Visualizador) y devuelve el grafo generado.
 * - regenerarGrafo(): libera el grafo resultado y el grafo base
 *   actuales, genera un nuevo grafo base y lo retorna.
 * - ejecutarAlgoritmo(algoritmo, nodoInicio, nodoDestino): libera el
 *   resultado anterior y despacha hacia la función del algoritmo
 *   correspondiente sobre el grafo base, almacenando y devolviendo 
 *   el nuevo grafo resultado.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#include "Controlador.h"
#include "GeneradorGrafo.h"
#include "../algoritmos/Dfs.h"
#include "../algoritmos/Bfs.h"
#include "../algoritmos/Prim.h"
#include "../algoritmos/Kruskal.h"
#include "../algoritmos/Dijkstra.h"
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
	while (true) {
		ventana.create(sf::VideoMode({ 700, 700 }),
			"GrafoExplorer - Configuracion",
			sf::Style::Titlebar | sf::Style::Close);

		PantallaConfig pantalla(ventana);
		if (!pantalla.ejecutar(config))
			return 0;

		delete resultado;
		resultado = nullptr;
		delete grafoBase;
		grafoBase = generarGrafo();

		Visualizador visualizador(ventana, config, grafoBase, *this);
		if (visualizador.ejecutar() == ResultadoVista::CERRAR)
			return 0;
	}
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
		case Algoritmo::BFS:      resultado = bfs(*grafoBase, nodoInicio); break;
		case Algoritmo::PRIM:     resultado = prim(*grafoBase, nodoInicio); break;
		case Algoritmo::KRUSKAL:  resultado = kruskal(*grafoBase); break;
		case Algoritmo::DIJKSTRA: resultado = dijkstra(*grafoBase, nodoInicio, nodoDestino); break;
	}
	return resultado;
}