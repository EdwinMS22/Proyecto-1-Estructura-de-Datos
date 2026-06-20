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