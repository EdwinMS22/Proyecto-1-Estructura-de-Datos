#pragma once

#include <SFML/Graphics.hpp>
#include "../sistema/Config.h"

class PantallaConfig {
private:
	sf::RenderWindow& ventana;

public:
	explicit PantallaConfig(sf::RenderWindow& ventana);
	bool ejecutar(Config& config);
};