/*
 * Pair.h
 *
 * Implementación genérica de una estructura par (clave, valor).
 * Esta clase permite almacenar dos tipos de datos relacionados, donde la clave
 * se utiliza principalmente para operaciones de comparación y ordenamiento,
 * mientras que el valor representa la información asociada.
 * 
 * Consideraciones:
 * - Las comparaciones NO consideran el valor, únicamente la clave.
 * - Esto lo hace adecuado para estructuras ordenadas como MinHeap o PriorityQueue.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include <iostream>

template <typename K, typename V>
class Pair {
public:
	K key;
	V value;

	Pair() = default;
	Pair(K key) {
		this->key = key;
	}
	Pair(K key, V value) {
		this->key = key;
		this->value = value;
	}
	bool operator==(const Pair<K, V>& other) {
		return key == other.key;
	}
	bool operator!=(const Pair<K, V>& other) {
		return key != other.key;
	}
	bool operator<(const Pair<K, V>& other) {
		return key < other.key;
	}
	bool operator<=(const Pair<K, V>& other) {
		return key <= other.key;
	}
	bool operator>(const Pair<K, V>& other) {
		return key > other.key;
	}
	bool operator>=(const Pair<K, V>& other) {
		return key >= other.key;
	}
	friend std::ostream& operator<<(std::ostream& os, const Pair<K, V>& p) {
		os << "(" << p.key << ", " << p.value << ")";
		return os;
	}
};