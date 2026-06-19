#include <SFML/Graphics.hpp>
#include "sistema/Config.h"
#include "interfaz/PantallaConfig.h"
#include "sistema/Controlador.h"

static int run() {
    Config config;

    sf::RenderWindow ventana(sf::VideoMode({700, 700}),
        "GrafoExplorer - Configuracion",
        sf::Style::Titlebar | sf::Style::Close);

    PantallaConfig pantalla(ventana);
    if (!pantalla.ejecutar(config))
        return 0;

    Controlador controlador(ventana, config);
    controlador.iniciar();

    return 0;
}

#ifdef _WIN32
#include <windows.h>
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow){
    return run();
}
#endif