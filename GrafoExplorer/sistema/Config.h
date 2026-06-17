#pragma once

struct Config {
	unsigned int anchoVentana = 1280;
	unsigned int altoVentana = 720;

	int cantidadNodos = 100;
	float distanciaConexion = 180.0f;
	int maximoVecinos = 6;

	const char* titulo = "GrafoExplorer";
};