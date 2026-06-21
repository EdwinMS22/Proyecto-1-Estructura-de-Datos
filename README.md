# Proyecto-1-Estructura-de-Datos
El proyecto se trata de implementar y visualizar algoritmos sobre grafos para facilitar su análisis y comprensión.

---

## Estructura del proyecto

```
GrafoExplorer/
├── algoritmos/     # Algoritmos sobre el grafo
├── ed/             # Estructuras de datos genéricas
├── interfaz/       # Interfaz gráfica (SFML) y manejo de eventos
├── modelo/         # Entidades del dominio (grafo, nodo, arco)
├── recursos/       # Recursos visuales de la interfaz gráfica
├── sistema/        # Generación del grafo, lógica y coordinación
└── main.cpp        # Punto de entrada
```

## Algoritmos implementados
1. Búsqueda en profundidad (DFS)
2. Búsqueda en anchura (BFS)
3. Algoritmo de Prim
4. Algoritmo de Kruskal
5. Algoritmo de Dijkstra

---
## Nota sobre dependencias (SFML 3):
En caso de encontrar errores al ejecutar el programa debido a archivos .dll faltantes, extrae el archivo sfml-dependencias.zip incluido en el repositorio en libs/. 
Debes copiar los archivos .dll correspondientes a las carpetas de salida Debug y Release, ya que estos han sido excluidos del control de versiones mediante .gitignore.