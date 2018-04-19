#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <bitset>
#include "hex.h"

class Hex;

class Edge {
public:
	std::vector<Hex> hexlist;

	Edge();
	std::vector<Hex> clone();
	bool edge_contains(Hex hex);
};