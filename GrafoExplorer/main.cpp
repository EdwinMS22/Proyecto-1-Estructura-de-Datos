/*
 * main.cpp
 *
 * Punto de entrada de la aplicación GrafoExplorer.
 *
 * Funcionalidades:
 * - run(): crea una instancia de Controlador y llama a iniciar(),
 *   devolviendo el código de salida del programa.
 * - wWinMain(): punto de entrada estándar de Windows para aplicaciones
 *   GUI, invoca run() y retorna su resultado.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#include "sistema/Controlador.h"

static int run() {
    Controlador controlador;
    return controlador.iniciar();
}

#ifdef _WIN32
#include <windows.h>
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow){
    return run();
}
#endif