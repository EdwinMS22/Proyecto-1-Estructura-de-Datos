#include <string>
#include <sstream>
#include <optional>
#include "PantallaConfig.h"

using std::string;

struct Campo {
	const char* etiqueta;
	string valor;
	bool permiteDecimal;
};

static bool parsearPositivo(const string& s, float& destino) {
	std::istringstream iss(s);
	float v;
	char extra;
	if ((iss >> v) && !(iss >> extra) && v > 0.0f) {
		destino = v;
		return true;
	}
	return false;
}

static bool aplicar(Campo campos[5], Config& config) {
	float a, al, n, d, mv;
	if (!parsearPositivo(campos[0].valor, a))  return false;
	if (!parsearPositivo(campos[1].valor, al)) return false;
	if (!parsearPositivo(campos[2].valor, n))  return false;
	if (!parsearPositivo(campos[3].valor, d))  return false;
	if (!parsearPositivo(campos[4].valor, mv)) return false;
	config.anchoVentana = static_cast<unsigned int>(a);
	config.altoVentana = static_cast<unsigned int>(al);
	config.cantidadNodos = static_cast<int>(n);
	config.distanciaConexion = d;
	config.maximoVecinos = static_cast<int>(mv);
	return true;
}

static void dibujar(sf::RenderWindow& ventana, const sf::Font& fuente, Campo campos[5], int activo, bool error) {
	ventana.clear(sf::Color::Black);

	sf::Text titulo(fuente, "GrafoExplorer - Configuracion", 28);
	titulo.setPosition({ 40.0f, 30.0f });
	ventana.draw(titulo);

	float y = 110.0f;
	for (int i = 0; i < 5; ++i) {
		string linea = string(campos[i].etiqueta) + ": " + campos[i].valor;
		if (i == activo) linea += "_";
		sf::Text texto(fuente, linea, 22);
		texto.setPosition({ 40.0f, y });
		texto.setFillColor(i == activo ? sf::Color::Cyan : sf::Color::White);
		ventana.draw(texto);
		y += 45.0f;
	}

	sf::Text ayuda(fuente, "Tab: siguiente campo    Enter: iniciar    Backspace: borrar", 18);
	ayuda.setPosition({ 40.0f, y + 25.0f });
	ayuda.setFillColor(sf::Color(150, 150, 150));
	ventana.draw(ayuda);

	if (error) {
		sf::Text msg(fuente, "Hay campos vacios o invalidos", 18);
		msg.setPosition({ 40.0f, y + 55.0f });
		msg.setFillColor(sf::Color(220, 80, 80));
		ventana.draw(msg);
	}

	ventana.display();
}

PantallaConfig::PantallaConfig(sf::RenderWindow& ventana) : ventana(ventana) {}

bool PantallaConfig::ejecutar(Config& config) {
	sf::Font fuente;
	if (!fuente.openFromFile("recursos/fuentes/Roboto-SemiBold.ttf"))
		return false;

	Campo campos[5] = {
		{"Ancho de ventana",      std::to_string(config.anchoVentana),  false},
		{"Alto de ventana",       std::to_string(config.altoVentana),   false},
		{"Cantidad de nodos",     std::to_string(config.cantidadNodos), false},
		{"Distancia de conexion", std::to_string(static_cast<int>(config.distanciaConexion)), true},
		{"Maximo de vecinos",     std::to_string(config.maximoVecinos), false}
	};
	int activo = 0;
	bool error = false;

	while (ventana.isOpen()) {
		while (const std::optional evento = ventana.pollEvent()) {
			if (evento->is<sf::Event::Closed>()) {
				ventana.close();
				return false;
			}
			else if (const auto* entrada = evento->getIf<sf::Event::TextEntered>()) {
				char32_t c = entrada->unicode;
				if (c == 9) {
					activo = (activo + 1) % 5;
				}
				else if (c == 8) {
					if (!campos[activo].valor.empty())
						campos[activo].valor.pop_back();
					error = false;
				}
				else if (c == 13 || c == 10) {
					if (aplicar(campos, config)) {
						ventana.create(sf::VideoMode({config.anchoVentana, config.altoVentana}),
							config.titulo, sf::Style::Titlebar | sf::Style::Close);
						return true;
					}
					error = true;
				}
				else if (c >= '0' && c <= '9') {
					if (campos[activo].valor.size() < 6)
						campos[activo].valor += static_cast<char>(c);
					error = false;
				}
				else if (c == '.' && campos[activo].permiteDecimal) {
					if (campos[activo].valor.find('.') == std::string::npos &&
						campos[activo].valor.size() < 6)
						campos[activo].valor += '.';
					error = false;
				}
			}
		}

		dibujar(ventana, fuente, campos, activo, error);
	}
	return false;
}
