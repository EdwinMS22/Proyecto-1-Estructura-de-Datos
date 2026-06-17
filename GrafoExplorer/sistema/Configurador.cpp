#include <iostream>
#include <string>
#include <sstream>
#include "Configurador.h"

static void imprimirConfig(const Config& config) {
    std::cout << "  1) Ancho de ventana      : " << config.anchoVentana << "\n";
    std::cout << "  2) Alto de ventana       : " << config.altoVentana << "\n";
    std::cout << "  3) Cantidad de nodos     : " << config.cantidadNodos << "\n";
    std::cout << "  4) Distancia de conexion : " << config.distanciaConexion << "\n";
    std::cout << "  5) Maximo de vecinos     : " << config.maximoVecinos << "\n";
}

static int leerEntero(int minimo) {
    std::string linea;
    while (true) {
        std::getline(std::cin, linea);
        std::istringstream iss(linea);
        int valor;
        char extra;
        if ((iss >> valor) && !(iss >> extra) && valor >= minimo)
            return valor;
        std::cout << "Valor invalido, intente de nuevo: ";
    }
}

static float leerFloatPositivo() {
    std::string linea;
    while (true) {
        std::getline(std::cin, linea);
        std::istringstream iss(linea);
        float valor;
        char extra;
        if ((iss >> valor) && !(iss >> extra) && valor > 0.f)
            return valor;
        std::cout << "Valor invalido, intente de nuevo: ";
    }
}

Config solicitarConfiguracion() {
    Config config;

    std::cout << "========== GrafoExplorer ==========\n\n";
    std::cout << "Configuracion predeterminada:\n";
    imprimirConfig(config);

    std::cout << '\n';
    std::string res;
    do {
        std::cout << "Iniciar con la configuracion predeterminada? (s/n): ";
        std::getline(std::cin, res);
    } while (res != "s" && res != "S" && res != "n" && res != "N");

    if (res == "s" || res == "S")
        return config;

    int opcion = -1;
    while (opcion != 0) {
        std::cout << "\nValores actuales:\n";
        imprimirConfig(config);
        std::cout << "\nSeleccione el valor a modificar (0 para iniciar): ";
        opcion = leerEntero(0);

        switch (opcion) {
        case 1:
            std::cout << "Nuevo ancho: ";
            config.anchoVentana = static_cast<unsigned int>(leerEntero(1));
            break;
        case 2:
            std::cout << "Nuevo alto: ";
            config.altoVentana = static_cast<unsigned int>(leerEntero(1));
            break;
        case 3:
            std::cout << "Nueva cantidad de nodos: ";
            config.cantidadNodos = leerEntero(1);
            break;
        case 4:
            std::cout << "Nueva distancia de conexion: ";
            config.distanciaConexion = leerFloatPositivo();
            break;
        case 5:
            std::cout << "Nuevo maximo de vecinos: ";
            config.maximoVecinos = leerEntero(1);
            break;
        case 0:
            break;
        default:
            std::cout << "Opcion invalida.\n";
        }
    }

    return config;
}