#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <bitset>
#include "edge.h"



//using namespace std;

class Edge;

//class Hex aggregates class Edge. Edge is one Edge of an Hexagon.
class Hex
{
	int rotN;
	int tileNumber;
	int x;
	int y;
	Edge* edge;
	std::bitset<7> connects;
	std::bitset<7> changed;

public:
	Hex();
	Hex(std::bitset<7> connects, int tileNumber);
	Hex(Edge* edge,int x, int y);
	~Hex();
	void set_bitset(std::vector<std::vector<Hex>> &world,Hex tile);
	std::bitset<7> get_connects();
	std::bitset<7> get_changed();
	std::bitset<7> get_surrounding(std::vector<std::vector<Hex>> world); //not in use
	std::bitset<7> rotc(std::bitset<7> rotbitset, int r); //not in use
	std::bitset<7> rot(std::bitset<7> rotbitset, int r); //not in use
	void rotMec(int r);
	void rotMe(int r); //not in use
	int get_tileNumber();
	int get_rotN();
	bool equals(Hex hex);
	int get_x();
	int get_y();
	std::vector<Hex> edge_clone();
	Hex clone();
	Edge* get_Edge(); //not in use
	void emergencyprotokoll(std::vector<std::vector<Hex>> &world); //not in use
	void set_changed(std::bitset<7> changed);
};