#pragma once

#include <SFML/Graphics.hpp>
#include "../sistema/Config.h"

class Visualizador {
private:
	const Config& config;
	sf::RenderWindow& ventana;

	void procesarEventos();
	void dibujar();

public:
	Visualizador(sf::RenderWindow& ventana, const Config& config);
	void ejecutar();
};