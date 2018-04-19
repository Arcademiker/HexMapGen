#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include "../include/hex.h" //change on windows

//using namespace std;

Hex::Hex()
{
	this->rotN = 0;
	this->tileNumber = 0;
	this->connects.reset();
	this->x = 0;
	this->y = 0;
}

Hex::Hex( std::bitset<7> connects, int tileNumber)
{
	this->rotN = 0;
	this->tileNumber = tileNumber;
	this->connects.reset();
	this->connects = connects;
	this->x = 0;
	this->y = 0;
}

Hex::Hex(Edge* edge, int x, int y)
{
	this->rotN = 0;
	this->tileNumber = 0;
	this->connects.reset();
	this->changed.reset();
	this->x = x;
	this->y = y;
	this->edge = edge;
}

Hex::~Hex()
{
}

void Hex::set_bitset(std::vector<std::vector<Hex>> &world, Hex tile)
{
	this->connects = tile.get_connects();
	this->tileNumber = tile.get_tileNumber();

	int maxy = 8;
	int maxx = 16;

	if(this->connects[1])
	{
		world[this->y - 1][this->x].connects[4] = true;
		//world[this->y][this->x-1].connects[3]=true;
		if (!(this->edge->edge_contains(world[this->y - 1][this->x]) || world[this->y - 1][this->x].changed[0] == 1))
		{
			this->edge->hexlist.push_back(world[this->y - 1][this->x].clone());
		}
	}
	if(this->connects[2])
	{
		world[this->y][this->x - 1].connects[5] = true;
		//world[this->y-1][this->x].connects[4]=true;
		if (!(this->edge->edge_contains(world[this->y][this->x - 1]) || world[this->y][this->x - 1].changed[0] == 1))
		{
			this->edge->hexlist.push_back(world[this->y][this->x - 1].clone());
		}
	}
	if(this->connects[3])
	{
		world[this->y + 1][this->x - 1].connects[6] = true;
		//world[this->y-1][this->x+1].connects[5]=true;
		if (!(this->edge->edge_contains(world[this->y + 1][this->x - 1]) || world[this->y + 1][this->x - 1].changed[0] == 1))
		{
			this->edge->hexlist.push_back(world[this->y + 1][this->x - 1].clone());
		}
	}
	if(this->connects[4])
	{
		world[this->y + 1][this->x].connects[1] = true;
		//world[this->y][this->x+1].connects[0]=true;
		if (!(this->edge->edge_contains(world[this->y + 1][this->x]) || world[this->y + 1][this->x].changed[0] == 1))
		{
			this->edge->hexlist.push_back(world[this->y + 1][this->x].clone());
		}
	}
	if(this->connects[5])
	{
		world[this->y][this->x + 1].connects[2] = true;
		//world[this->y+1][this->x].connects[1]=true;
		if (!(this->edge->edge_contains(world[this->y][this->x + 1]) || world[this->y][this->x + 1].changed[0] == 1))
		{
			this->edge->hexlist.push_back(world[this->y][this->x + 1].clone());
		}
	}
	if(this->connects[6])
	{
		world[this->y - 1][this->x + 1].connects[3] = true;
		//world[this->y+1][this->x-1].connects[2]=true;
		if (!(this->edge->edge_contains(world[this->y - 1][this->x + 1]) || world[this->y - 1][this->x + 1].changed[0] == 1))
		{
			this->edge->hexlist.push_back(world[this->y - 1][this->x + 1].clone());
		}
	}

	//anlegbare Felder updaten
	
	
	//neu angelegtes Feld aus der Liste nehmen
	for (int i = 0; i < this->edge->hexlist.size(); i++)
	{
		if (this->equals(this->edge->hexlist[i]))
		{
			this->edge->hexlist.erase(this->edge->hexlist.begin() + i);
			i = this->edge->hexlist.size();
		}
	
	}
	

	this->changed.reset();
	this->changed.flip();
	world[this->y][this->x].changed[0] = true;
	
	world[this->y - 1][this->x].changed[4] = true;
	world[this->y][this->x - 1].changed[5] = true;
	world[this->y + 1][this->x - 1].changed[6] = true;
	world[this->y + 1][this->x].changed[1] = true;
	world[this->y][this->x + 1].changed[2] = true;
	world[this->y - 1][this->x + 1].changed[3]= true;

	this->rotN = tile.get_rotN();

}

std::bitset<7> Hex::get_connects()
{
	return this->connects;
}

std::bitset<7> Hex::get_changed()
{
	return this->changed;
}

//not in use
std::bitset<7> Hex::get_surrounding(std::vector<std::vector<Hex>> world)
{

	std::bitset<7> surrounding;
	surrounding[2] = world[this->y - 1][this->x].connects[4];
	surrounding[1] = world[this->y][this->x-1].connects[5];
	surrounding[6] = world[this->y + 1][this->x - 1].connects[6];
	surrounding[5] = world[this->y + 1][this->x].connects[1];
	surrounding[4] = world[this->y][this->x + 1].connects[2];
	surrounding[3] = world[this->y-1][this->x+1].connects[3];
	surrounding[0] = 0;
	
	
	return surrounding;
}

//not in use
std::bitset<7> Hex::rotc(std::bitset<7> rotbitset, int r)
{
	bool tmpbit;

	for (int i = 0; i < r; i++)
	{
		tmpbit = rotbitset[6];
		rotbitset <<= 1;
		rotbitset[0] = rotbitset[1];
		rotbitset[1] = tmpbit;
	}
	this->rotN = r;
	return  rotbitset;
}

//not in use
std::bitset<7> Hex::rot(std::bitset<7> rotbitset, int r)
{
	bool tmpbit;

	for (int i = 0; i < r; i++)
	{
		tmpbit = rotbitset[6];
		rotbitset <<= 1;
		rotbitset[0] = rotbitset[1];
		rotbitset[1] = tmpbit;
	}

	return  rotbitset;
}

void Hex::rotMec(int r)
{
	bool tmpbit;

	for (int i = 0; i < r; i++)
	{
		tmpbit = this->connects[6];
		this->connects <<= 1;
		this->connects[0] = this->connects[1];
		this->connects[1] = tmpbit;
	}
	this->rotN = (this->rotN+r)%6;
}

//not in use
void Hex::rotMe(int r)
{
	bool tmpbit;

	for (int i = 0; i < r; i++)
	{
		tmpbit = this->connects[6];
		this->connects <<= 1;
		this->connects[0] = this->connects[1];
		this->connects[1] = tmpbit;
	}
}

int Hex::get_tileNumber()
{
	return this->tileNumber;
}

int Hex::get_rotN()
{
	return rotN;
}


bool Hex::equals(Hex hex)
{
	if (this->get_x() == hex.get_x() && this->get_y() == hex.get_y()) {
		return true;
	}
	return false;
}

int Hex::get_x()
{
	return this->x;
}

int Hex::get_y()
{
	return this->y;
}

std::vector<Hex> Hex::edge_clone() {
	return this->edge->clone();
}

//partially clone enough
Hex Hex::clone() {
	Hex ret;
	ret.x = this->get_x();
	ret.y = this->get_y();
	return ret;
}

//not in use
Edge* Hex::get_Edge()
{
	return this->edge;
}

//not in use
void Hex::emergencyprotokoll(std::vector<std::vector<Hex>> &world)
{
	int ccc = 0;
	//random!
	if (edge->hexlist.size() < 10)
	{
		for (int p = 0; p < 26; p++)
		{
			for (int q = 0; q < 26; q++)
			{
				if (world[p][q].changed[0] == 1 && p - 1 > 3 && q - 1 > 3 && q + p - 1 > 10 && q + 1 < 16 && p + 1 < 11 && p - q + 1 < 9 && q - p + 1 < 8)
				{
					if (world[p - 1][q].changed[0] == 0 && !this->edge->edge_contains(world[p - 1][q])) { this->edge->hexlist.push_back(world[p - 1][q].clone()); ccc++; }
					if (world[p][q - 1].changed[0] == 0 && !this->edge->edge_contains(world[p][q - 1])) { this->edge->hexlist.push_back(world[p][q - 1].clone()); ccc++; }
					if (world[p + 1][q - 1].changed[0] == 0 && !this->edge->edge_contains(world[p + 1][q - 1])) { this->edge->hexlist.push_back(world[p + 1][q - 1].clone()); ccc++; }
					if (world[p + 1][q].changed[0] == 0 && !this->edge->edge_contains(world[p + 1][q])) { this->edge->hexlist.push_back(world[p + 1][q].clone()); ccc++; }
					if (world[p][q + 1].changed[0] == 0 && !this->edge->edge_contains(world[p][q + 1])) { this->edge->hexlist.push_back(world[p][q + 1].clone()); ccc++; }
					if (world[p - 1][q + 1].changed[0] == 0 && !this->edge->edge_contains(world[p - 1][q + 1])) { this->edge->hexlist.push_back(world[p - 1][q + 1].clone()); ccc++; }
				}
			}
			if (ccc > 11) {
				break;
			}
		}
	}
}

void Hex::set_changed(std::bitset<7> changed)
{
	this->changed = changed;
}