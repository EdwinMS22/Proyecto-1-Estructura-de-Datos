#include <cstdio>
#include <optional>
#include "Visualizador.h"

namespace {
	const float RADIO_NODO = 15.0f;
	const float ALTO_BARRA = 44.0f;

	const float BOTON_X = 10.0f;
	const float BOTON_Y = 8.0f;
	const float BOTON_ANCHO = 140.0f;
	const float BOTON_ALTO = 28.0f;
	const float BOTON_SEP = 6.0f;

	const char* NOMBRES[5] = { "1  DFS", "2  BFS", "3  Prim", "4  Kruskal", "5  Dijkstra" };

	const sf::Color COLOR_FONDO(7, 10, 17);
	const sf::Color COLOR_ARCO(90, 100, 120);
	const sf::Color COLOR_ARCO_RES(210, 79, 166);
	const sf::Color COLOR_NODO(24, 95, 165);
	const sf::Color COLOR_NODO_RES(46, 123, 214);
	const sf::Color COLOR_NODO_SEL(255, 210, 90);
	const sf::Color COLOR_NODO_BORDE(133, 183, 235);
	const sf::Color COLOR_TEXTO(234, 243, 251);
	const sf::Color COLOR_BARRA(20, 26, 38);
	const sf::Color COLOR_BOTON(36, 44, 60);
	const sf::Color COLOR_BOTON_ON(24, 95, 165);
	const sf::Color COLOR_INSTR(143, 163, 188);
}

Visualizador::Visualizador(sf::RenderWindow& ventana, const Config& config,
	Grafo* grafoBase, EjecutorAlgoritmos& ejecutor)
	: ventana(ventana), config(config), grafoBase(grafoBase), ejecutor(ejecutor) {
	
	ventana.create(sf::VideoMode({config.anchoVentana, config.altoVentana}),
		config.titulo, sf::Style::Titlebar | sf::Style::Close);
	ventana.setFramerateLimit(60);

	reconfigurar = false;
	resultado = nullptr;
	hayFuente = fuente.openFromFile("recursos/Roboto-SemiBold.ttf");
	modo = Algoritmo::DFS;
	nodoInicio = -1;
	nodoDestino = -1;
}

ResultadoVista Visualizador::ejecutar() {
	while (ventana.isOpen() && !reconfigurar) {
		procesarEventos();
		dibujar();
	}
	return reconfigurar ? ResultadoVista::RECONFIGURAR : ResultadoVista::CERRAR;
}

void Visualizador::procesarEventos() {
	while (const std::optional evento = ventana.pollEvent()) {
		if (evento->is<sf::Event::Closed>()) {
			ventana.close();
		}
		else if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()) {
			switch (tecla->code) {
			case sf::Keyboard::Key::Num1: seleccionarAlgoritmo(Algoritmo::DFS); break;
			case sf::Keyboard::Key::Num2: seleccionarAlgoritmo(Algoritmo::BFS); break;
			case sf::Keyboard::Key::Num3: seleccionarAlgoritmo(Algoritmo::PRIM); break;
			case sf::Keyboard::Key::Num4: seleccionarAlgoritmo(Algoritmo::KRUSKAL); break;
			case sf::Keyboard::Key::Num5: seleccionarAlgoritmo(Algoritmo::DIJKSTRA); break;
			case sf::Keyboard::Key::G:
				grafoBase = ejecutor.regenerarGrafo();
				reiniciar();
				break;
			case sf::Keyboard::Key::R: reiniciar(); break;
			case sf::Keyboard::Key::C: reconfigurar = true; break;
			case sf::Keyboard::Key::Escape: ventana.close(); break;
			default: break;
			}
		}
		else if (const auto* clic = evento->getIf<sf::Event::MouseButtonPressed>()) {
			sf::Vector2f punto = ventana.mapPixelToCoords(clic->position);

			if (clic->button == sf::Mouse::Button::Left) {
				int boton = botonEnPosicion(punto);
				if (boton != -1) {
					seleccionarAlgoritmo(static_cast<Algoritmo>(boton));
					continue;
				}
			}
			if (punto.y < ALTO_HUD)
				continue;   // clic en la franja del menu/ayuda: no se interpreta como nodo

			int nodo = nodoEnPosicion(punto);
			if (nodo != -1)
				clicEnNodo(nodo, clic->button == sf::Mouse::Button::Right);
		}
	}
}

void Visualizador::seleccionarAlgoritmo(Algoritmo algoritmo) {
	modo = algoritmo;
	reiniciar();
	if (modo == Algoritmo::KRUSKAL)
		solicitarEjecucion();   // Kruskal no recibe parametros: se ejecuta de una
}

void Visualizador::clicEnNodo(int numeroNodo, bool botonDerecho) {
	if (modo == Algoritmo::DIJKSTRA) {
		if (botonDerecho) nodoDestino = numeroNodo;
		else nodoInicio = numeroNodo;
		if (nodoInicio != -1 && nodoDestino != -1)
			solicitarEjecucion();
	}
	else if (modo == Algoritmo::DFS || modo == Algoritmo::BFS || modo == Algoritmo::PRIM) {
		if (botonDerecho) return;
		nodoInicio = numeroNodo;
		solicitarEjecucion();
	}
	// Kruskal ignora los clics
}

void Visualizador::solicitarEjecucion() {
	resultado = ejecutor.ejecutarAlgoritmo(modo, nodoInicio, nodoDestino);
}

void Visualizador::reiniciar() {
	resultado = nullptr;
	nodoInicio = -1;
	nodoDestino = -1;
}

int Visualizador::botonEnPosicion(sf::Vector2f punto) {
	for (int i = 0; i < 5; i++) {
		float x = BOTON_X + i * (BOTON_ANCHO + BOTON_SEP);
		sf::FloatRect rect({ x, BOTON_Y }, { BOTON_ANCHO, BOTON_ALTO });
		if (rect.contains(punto))
			return i;
	}
	return -1;
}

int Visualizador::nodoEnPosicion(sf::Vector2f punto) {
	for (int i = 0; i < grafoBase->cantidadNodos(); i++) {
		Nodo* n = grafoBase->obtenerNodo(i);
		float dx = punto.x - n->x;
		float dy = punto.y - n->y;
		if (dx * dx + dy * dy <= RADIO_NODO * RADIO_NODO)
			return n->numero;
	}
	return -1;
}

void Visualizador::dibujar() {
	ventana.clear(COLOR_FONDO);
	dibujarGrafo(grafoBase, false);
	if (resultado != nullptr)
		dibujarGrafo(resultado, true);
	dibujarBarra();
	dibujarInstruccion();
	ventana.display();
}

void Visualizador::dibujarGrafo(Grafo* grafo, bool resaltado) {
	int cantArcos = grafo->cantidadArcos();
	sf::VertexArray lineas(sf::PrimitiveType::Lines, cantArcos * 2);
	sf::Color colorArco = resaltado ? COLOR_ARCO_RES : COLOR_ARCO;
	for (int i = 0; i < cantArcos; i++) {
		Arco* arco = grafo->obtenerArco(i);
		Nodo* a = grafo->obtenerNodo(arco->extremoA);
		Nodo* b = grafo->obtenerNodo(arco->extremoB);
		lineas[i * 2].position = { a->x, a->y };
		lineas[i * 2].color = colorArco;
		lineas[i * 2 + 1].position = { b->x, b->y };
		lineas[i * 2 + 1].color = colorArco;
	}
	ventana.draw(lineas);

	sf::CircleShape circulo(RADIO_NODO);
	circulo.setOrigin({ RADIO_NODO, RADIO_NODO });
	circulo.setOutlineThickness(2.f);
	circulo.setOutlineColor(COLOR_NODO_BORDE);
	for (int i = 0; i < grafo->cantidadNodos(); i++) {
		Nodo* n = grafo->obtenerNodo(i);

		// En la capa de resultado solo se resaltan los nodos alcanzados (los que tienen
		// alguna arista en el resultado); los no alcanzados se ven con el grafo base.
		if (resaltado && n->gradoActual() == 0)
			continue;

		sf::Color relleno = resaltado ? COLOR_NODO_RES : COLOR_NODO;
		if (!resaltado && (n->numero == nodoInicio || n->numero == nodoDestino))
			relleno = COLOR_NODO_SEL;
		circulo.setFillColor(relleno);
		circulo.setPosition({ n->x, n->y });
		ventana.draw(circulo);

		if (hayFuente) {
			char etiqueta[16];
			std::snprintf(etiqueta, sizeof(etiqueta), "N%d", n->numero);
			sf::Text texto(fuente, etiqueta, 11);
			texto.setFillColor(COLOR_TEXTO);
			sf::FloatRect limite = texto.getLocalBounds();
			texto.setOrigin(limite.position + limite.size / 2.0f);
			texto.setPosition({ n->x, n->y });
			ventana.draw(texto);
		}
	}
}

void Visualizador::dibujarBarra() {
	sf::RectangleShape fondo({ static_cast<float>(config.anchoVentana), ALTO_BARRA });
	fondo.setPosition({ 0.0f, 0.0f });
	fondo.setFillColor(COLOR_BARRA);
	ventana.draw(fondo);

	for (int i = 0; i < 5; i++) {
		float x = BOTON_X + i * (BOTON_ANCHO + BOTON_SEP);
		sf::RectangleShape boton({ BOTON_ANCHO, BOTON_ALTO });
		boton.setPosition({ x, BOTON_Y });
		boton.setFillColor(static_cast<int>(modo) == i ? COLOR_BOTON_ON : COLOR_BOTON);
		boton.setOutlineThickness(1.f);
		boton.setOutlineColor(COLOR_NODO_BORDE);
		ventana.draw(boton);

		if (hayFuente) {
			sf::Text texto(fuente, NOMBRES[i], 13);
			texto.setFillColor(COLOR_TEXTO);
			sf::FloatRect limite = texto.getLocalBounds();
			texto.setOrigin(limite.position + limite.size / 2.0f);
			texto.setPosition({ x + BOTON_ANCHO / 2.0f, BOTON_Y + BOTON_ALTO / 2.0f });
			ventana.draw(texto);
		}
	}
}

void Visualizador::dibujarInstruccion() {
	if (!hayFuente)
		return;
	const char* mensaje;
	switch (modo) {
	case Algoritmo::DFS:
	case Algoritmo::BFS:
	case Algoritmo::PRIM:
		mensaje = "Clic sobre un nodo para ejecutar desde ahi    |    G: nuevo grafo    R: reiniciar    C: cambiar configuracion    Esc: salir";
		break;
	case Algoritmo::KRUSKAL:
		mensaje = "Kruskal se ejecuta sin seleccion    |    G: nuevo grafo    R: reiniciar    C: cambiar configuracion    Esc: salir";
		break;
	case Algoritmo::DIJKSTRA:
		mensaje = "Clic izq: nodo inicial    Clic der: nodo destino    |    G: nuevo grafo    R: reiniciar    C: cambiar configuracion    Esc: salir";
		break;
	default:
		mensaje = "";
		break;
	}
	sf::Text t(fuente, mensaje, 13);
	t.setFillColor(COLOR_INSTR);
	sf::FloatRect limite = t.getLocalBounds();
	t.setOrigin({ limite.position.x, limite.position.y + limite.size.y / 2.0f });
	float x = BOTON_X + 5 * (BOTON_ANCHO + BOTON_SEP) + 12.0f;
	t.setPosition({ x, ALTO_BARRA / 2.0f });
	ventana.draw(t);
}