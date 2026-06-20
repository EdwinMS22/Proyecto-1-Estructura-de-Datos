#pragma once

struct Config {
	unsigned int anchoVentana = 1800;
	unsigned int altoVentana = 880;

	int cantidadNodos = 80;
	float distanciaConexion = 180.0f;
	int maximoVecinos = 4;

	const char* titulo = "GrafoExplorer";
};