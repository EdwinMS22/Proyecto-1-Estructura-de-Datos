/*
 * Controlador.h
 *
 * Clase central de GrafoExplorer. Actúa como coordinador de la
 * aplicación: posee la ventana de SFML, la configuración del programa
 * y el ciclo de vida del grafo (tanto el grafo base generado
 * aleatoriamente como los grafos resultado producidos por los
 * algoritmos). Implementa la interfaz EjecutorAlgoritmos para
 * desacoplar la vista de la lógica de ejecución de algoritmos, evitando 
 * dependencias circulares entre capas.
 *
 * Funcionalidades:
 * - iniciar(): ciclo principal de la aplicación; crea/recrea la
 *   ventana según la configuración y alterna entre pantalla de
 *   configuración y visualización del grafo.
 * - generarGrafo(): método privado que crea un nuevo grafo base a
 *   partir de la configuración actual usando GeneradorGrafo.
 * - ejecutarAlgoritmo(algoritmo, nodoInicio, nodoDestino): punto único
 *   de despacho hacia los algoritmos de grafos implementado desde EjecutorAlgoritmos.
 * - regenerarGrafo(): descarta el grafo base actual y genera uno
 *   nuevo, implementado desde EjecutorAlgoritmos.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"
#include "../interfaz/EjecutorAlgoritmos.h"

class Controlador : public EjecutorAlgoritmos {
private:
	sf::RenderWindow ventana;
	Config config;
	Grafo* grafoBase;
	Grafo* resultado;

	Grafo* generarGrafo();

public:
	Controlador();
	~Controlador();

	int iniciar();

	Grafo* ejecutarAlgoritmo(Algoritmo algoritmo, int nodoInicio, int nodoDestino) override;
	Grafo* regenerarGrafo() override;
};