/*
 * GeneradorGrafo.h
 *
 * Encargado de generar grafos no dirigidos aleatorios para
 * GrafoExplorer. Distribuye los nodos en posiciones aleatorias dentro
 * del área de la ventana (respetando márgenes laterales y un margen
 * superior reservado para el HUD), y conecta los nodos cercanos entre
 * sí según una distancia de conexión configurable y un máximo de
 * vecinos por nodo. El grafo resultante puede quedar desconectado
 * dependiendo de la distribución generada.
 *
 * Funcionalidades:
 * - generar(): crea un nuevo Grafo, ubica los nodos en posiciones
 *   aleatorias dentro del área disponible y agrega arcos entre pares de
 *   nodos cuya distancia euclidiana sea menor o igual al umbral de
 *   conexión, respetando el máximo de vecinos por nodo. Devuelve un
 *   puntero dinámico cuya propiedad es de quién llame la función
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include <random>
#include "../modelo/Grafo.h"
#include "../modelo/Nodo.h"

class GeneradorGrafo {
private:
	int cantidadNodos;
	float distanciaConexion;
	int maxVecinos;
	int ancho;
	int alto;
	int margen;
	int margenSuperior;
	std::mt19937 motor;

public:
	GeneradorGrafo(int cantidadNodos, float distanciaConexion, int maxVecinos,
		int ancho, int alto, int margen = 20, int margenSuperior = 20)
		: GeneradorGrafo(cantidadNodos, distanciaConexion, maxVecinos,
			ancho, alto, margen, margenSuperior, std::random_device{}()) {
	}
	GeneradorGrafo(int cantidadNodos, float distanciaConexion, int maxVecinos,
		int ancho, int alto, int margen, int margenSuperior, unsigned int semilla)
		: motor(semilla) {
		this->cantidadNodos = cantidadNodos;
		this->distanciaConexion = distanciaConexion;
		this->maxVecinos = maxVecinos;
		this->ancho = ancho;
		this->alto = alto;
		this->margen = margen;
		this->margenSuperior = margenSuperior;
	}

	Grafo* generar() {
		Grafo* grafo = new Grafo(cantidadNodos, maxVecinos);

		float minX = static_cast<float>(margen);
		float maxX = static_cast<float>(ancho - margen);
		float minY = static_cast<float>(margenSuperior);
		float maxY = static_cast<float>(alto - margen);

		std::uniform_real_distribution<float> distX(minX, maxX);
		std::uniform_real_distribution<float> distY(minY, maxY);
		for (int i = 0; i < cantidadNodos; i++)
			grafo->agregarNodo(distX(motor), distY(motor));

		float umbralCuadrado = distanciaConexion * distanciaConexion;
		for (int i = 0; i < cantidadNodos; i++) {
			Nodo* ni = grafo->obtenerNodo(i);
			for (int j = i + 1; j < cantidadNodos; j++) {
				if (ni->gradoActual() >= maxVecinos)
					break;
				Nodo* nj = grafo->obtenerNodo(j);
				if (nj->gradoActual() >= maxVecinos)
					continue;
				float dx = ni->x - nj->x;
				float dy = ni->y - nj->y;
				if (dx * dx + dy * dy <= umbralCuadrado)
					grafo->agregarArco(i, j);
			}
		}
		return grafo;
	}
};