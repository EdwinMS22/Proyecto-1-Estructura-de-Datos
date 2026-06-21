/*
 * Config.h
 *
 * Estructura de configuración global de GrafoExplorer. Centraliza los
 * parámetros ajustables que controlan tanto las dimensiones de la
 * ventana de la aplicación como los criterios de generación aleatoria
 * del grafo (cantidad de nodos, distancia máxima de conexión entre
 * nodos y cantidad máxima de vecinos por nodo).
 *
 * Funcionalidades:
 * - Config: struct con valores por defecto para ancho y alto de la
 *   ventana, cantidad de nodos a generar, distancia de conexión,
 *   máximo de vecinos por nodo y título de la ventana.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

struct Config {
	unsigned int anchoVentana = 1800;
	unsigned int altoVentana = 880;

	int cantidadNodos = 80;
	float distanciaConexion = 180.0f;
	int maximoVecinos = 4;

	const char* titulo = "GrafoExplorer";
};