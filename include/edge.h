#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <bitset>
#include "hex.h"

class Hex;

//the class Edge stores the mutual constraints of two hexagonal tiles adjacent to each other,
//so that the hexagonal tiles can be correctly puzzled together.
class Edge {
public:
	std::vector<Hex> hexlist;

	Edge();
	std::vector<Hex> clone();
	bool edge_contains(Hex hex);
};