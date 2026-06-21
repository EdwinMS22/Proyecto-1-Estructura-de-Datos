/*
 * Visualizador.h
 *
 * Pantalla principal de visualización de GrafoExplorer. Se encarga de
 * dibujar el grafo base y, cuando corresponde, el resultado de un
 * algoritmo sobre la misma ventana, además de gestionar la interacción
 * del usuario. Delega la ejecución real de los algoritmos en EjecutorAlgoritmos.
 *
 * Funcionalidades:
 * - ejecutar(): ciclo principal de la vista; procesa eventos y dibuja
 *   en cada iteración hasta que el usuario cierre la ventana o
 *   solicite reconfigurar. Devuelve el ResultadoVista correspondiente.
 * - procesarEventos(): atiende los eventos de SFML.
 * - dibujar(): redibuja la ventana completa en cada cuadro.
 * - seleccionarAlgoritmo(algoritmo): cambia el algoritmo activo.
 * - clicEnNodo(numeroNodo, botonDerecho): registra el nodo
 *   seleccionado como inicio o destino según el botón del mouse
 *   utilizado, y dispara la ejecución cuando ya hay suficiente
 *   selección.
 * - nodoEnPosicion(punto): devuelve el número de nodo ubicado bajo una
 *   posición de pantalla, o -1 si no hay ninguno.
 * - dibujarGrafo(grafo, resaltado): dibuja los nodos y arcos de un
 *   grafo, marcando opcionalmente los elementos resaltados por el
 *   algoritmo ejecutado.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

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
	int nodoInicio;
	int nodoDestino;
	bool sinRuta;

	void procesarEventos();
	void dibujar();

	void seleccionarAlgoritmo(Algoritmo algoritmo);
	void clicEnNodo(int numeroNodo, bool botonDerecho);
	void solicitarEjecucion();
	void reiniciar();

	int nodoEnPosicion(sf::Vector2f punto);
	int botonEnPosicion(sf::Vector2f punto);

	void dibujarGrafo(Grafo* grafo, bool resaltado);
	void dibujarBarra();
	void dibujarInstruccion();

public:
	// Alto reservado arriba para la barra
	static constexpr float ALTO_HUD = 64.0f;

	Visualizador(sf::RenderWindow& ventana, const Config& config,
		Grafo* grafoBase, EjecutorAlgoritmos& ejecutor);
	ResultadoVista ejecutar();
};