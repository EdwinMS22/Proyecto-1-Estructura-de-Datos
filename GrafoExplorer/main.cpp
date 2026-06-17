#include <SFML/Graphics.hpp>
#include "sistema/Config.h"
#include "interfaz/PantallaConfig.h"
#include "interfaz/Visualizador.h"

static int run() {
    Config config;

    sf::RenderWindow ventana(sf::VideoMode({700, 700}),
        "GrafoExplorer - Configuracion",
        sf::Style::Titlebar | sf::Style::Close);

    PantallaConfig pantalla(ventana);
    if (!pantalla.ejecutar(config))
        return 0;

    Visualizador visualizador(ventana, config);
    visualizador.ejecutar();
    return 0;
}

#ifdef _WIN32
#include <windows.h>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    return run();
}
#endif