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
	int margen;	// para que no se corten en la pantalla
	std::mt19937 motor;

public:
	// Constructor por defecto: semilla aleatoria distinta en cada corrida
	GeneradorGrafo(int cantidadNodos, float distanciaConexion, int maxVecinos,
		int ancho, int alto, int margen = 20)
		: GeneradorGrafo(cantidadNodos, distanciaConexion, maxVecinos,
			ancho, alto, margen, std::random_device{}()) {
	}

	// Constructor con semilla fija: depuracion / defensa.
	GeneradorGrafo(int cantidadNodos, float distanciaConexion, int maxVecinos,
		int ancho, int alto, int margen, unsigned int semilla)
		: motor(semilla) {
		this->cantidadNodos = cantidadNodos;
		this->distanciaConexion = distanciaConexion;
		this->maxVecinos = maxVecinos;
		this->ancho = ancho;
		this->alto = alto;
		this->margen = margen;
	}

	// El que lo llama es dueño y debe liberarlo
	Grafo* generar() {
		Grafo* grafo = new Grafo(cantidadNodos, maxVecinos);

		std::uniform_real_distribution<float> distX(
			static_cast<float>(margen),
			static_cast<float>(ancho - margen)
		);

		std::uniform_real_distribution<float> distY(
			static_cast<float>(margen),
			static_cast<float>(alto - margen)
		);
		for (int i = 0; i < cantidadNodos; i++)
			grafo->agregarNodo(distX(motor), distY(motor));

		float umbralCuadrado = distanciaConexion * distanciaConexion;
		for (int i = 0; i < cantidadNodos; i++) {
			Nodo* ni = grafo->obtenerNodo(i);
			for (int j = i + 1; j < cantidadNodos; j++) {
				if (ni->gradoActual() >= maxVecinos)
					break;	// i ya está lleno por lo que no toma más vecinos
				Nodo* nj = grafo->obtenerNodo(j);
				if (nj->gradoActual() >= maxVecinos)
					continue;	//j está lleno y se prueba con el siguiente
				float dx = ni->x - nj->x;
				float dy = ni->y - nj->y;
				if (dx * dx + dy * dy <= umbralCuadrado)
					grafo->agregarArco(i, j);
			}
		}
		return grafo;
	}
};