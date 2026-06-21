/*
 * PantallaConfig.h
 *
 * Pantalla inicial de GrafoExplorer encargada de capturar, mediante
 * teclado, los parámetros de configuración definidos en Config antes 
 * de iniciar la generación y visualización del grafo.
 *
 * Funcionalidades:
 * - ejecutar(config): muestra la pantalla de configuración, captura y
 *   valida la entrada del usuario, y vuelca los valores resultantes
 *   sobre el Config recibido. Devuelve true si el usuario confirmó la
 *   configuración o false si cerró la ventana.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

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