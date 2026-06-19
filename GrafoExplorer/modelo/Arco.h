#pragma once

class Arco {
public:
	int extremoA;
	int extremoB;
	float peso;

	Arco() {
		extremoA = extremoB = -1;
		peso = 0.0f;
	}

	Arco(int extremoA, int extremoB, float peso) {
		this->extremoA = extremoA;
		this->extremoB = extremoB;
		this->peso = peso;
	}

	// Dado uno de los extremos, devuelve el otro
	// Permite recorrer el arco sin importar la dirección
	int otroExtremo(int nodo) const {
		return (nodo == extremoA) ? extremoB : extremoA;
	}
};