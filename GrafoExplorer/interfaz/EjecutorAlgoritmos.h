#pragma once

#include "../modelo/Grafo.h"

enum class Algoritmo {DFS, BFS, PRIM, KRUSKAL, DIJKSTRA};

class EjecutorAlgoritmos {
public:
	virtual ~EjecutorAlgoritmos() = default;


	// Ejecuta el algoritmo indicado con los nodos seleccionados y devuelve el Grafo*
	// resultado (arbol de expansion o ruta), o nullptr si no hay resultado. El resultado
	// pertenece al ejecutor: el visualizador solo lo dibuja, no lo libera.
	virtual Grafo* ejecutarAlgoritmo(Algoritmo algoritmo, int nodoInicio, int nodoDestino) = 0;
};