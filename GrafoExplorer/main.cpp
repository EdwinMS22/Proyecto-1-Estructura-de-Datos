#include "sistema/Config.h"
#include "sistema/Configurador.h"
#include "interfaz/Visualizador.h"

int main() {
    Config config = solicitarConfiguracion();
    Visualizador visualizador(config);
    visualizador.ejecutar();

    return 0;
}