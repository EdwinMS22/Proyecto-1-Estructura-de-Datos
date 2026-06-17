#include <optional>
#include "Visualizador.h"

void Visualizador::procesarEventos() {
	while (const std::optional evento = ventana.pollEvent()) {
		if (evento->is<sf::Event::Closed>()) {
			ventana.close();
		}
		else if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()) {
			if (tecla->code == sf::Keyboard::Key::Escape)
				ventana.close();
		}
	}
}

void Visualizador::dibujar() {
	ventana.clear(sf::Color::Black);
	ventana.display();
}

Visualizador::Visualizador(const Config& config) :
	config(config),
	ventana(sf::VideoMode({config.anchoVentana, config.altoVentana}),
		config.titulo,
		sf::Style::Titlebar | sf::Style::Close) 
{
	ventana.setFramerateLimit(60);
}

void Visualizador::ejecutar() {
	while (ventana.isOpen()) {
		procesarEventos();
		dibujar();
	}
}