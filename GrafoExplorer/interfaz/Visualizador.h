#pragma once

#include <SFML/Graphics.hpp>
#include "../sistema/Config.h"
#include "../modelo/Grafo.h"
#include "EjecutorAlgoritmos.h"

enum class ResultadoVista { CERRAR, RECONFIGURAR };

class Visualizador {
private:
	sf::RenderWindow& ventana;
	const Config& config;
	bool reconfigurar;
	Grafo* grafoBase;
	EjecutorAlgoritmos& ejecutor;
	Grafo* resultado;

	sf::Font fuente;
	bool hayFuente;

	Algoritmo modo;
	int nodoInicio;       // seleccion de origen (DFS/BFS/Prim/Dijkstra); -1 si no hay
	int nodoDestino;      // seleccion de destino (solo Dijkstra); -1 si no hay

	void procesarEventos();
	void dibujar();

	void seleccionarAlgoritmo(Algoritmo algoritmo);
	void clicEnNodo(int numeroNodo, bool botonDerecho);
	void solicitarEjecucion();
	void reiniciar();

	int nodoEnPosicion(sf::Vector2f punto);    // numero de nodo bajo el punto, o -1
	int botonEnPosicion(sf::Vector2f punto);   // indice de boton de la barra, o -1

	void dibujarGrafo(Grafo* grafo, bool resaltado);
	void dibujarBarra();
	void dibujarInstruccion();

public:
	// Alto reservado arriba para la barra (la ayuda va sobre ella, a la derecha de los botones)
	// Los nodos se generan por debajo de esta franja para que no queden tapados por la barra
	static constexpr float ALTO_HUD = 64.0f;

	Visualizador(sf::RenderWindow& ventana, const Config& config,
		Grafo* grafoBase, EjecutorAlgoritmos& ejecutor);
	ResultadoVista ejecutar();
};