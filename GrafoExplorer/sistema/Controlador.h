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

	// EjecutorAlgoritmos: punto único donde se llaman los algorítmos.
	Grafo* ejecutarAlgoritmo(Algoritmo algoritmo, int nodoInicio, int nodoDestino) override;
	Grafo* regenerarGrafo() override;
};