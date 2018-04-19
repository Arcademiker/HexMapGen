#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include "../include/edge.h" //change on windows
#include "../include/hex.h" //change on windows

Edge::Edge()
{
	std::vector<Hex> hexlist;
}

std::vector<Hex> Edge::clone()
{
	std::vector<Hex> ret;
	for (int i = 0; i < this->hexlist.size(); i++)
	{
		ret.push_back(this->hexlist[i]);
	}
	return ret;
}

bool Edge::edge_contains(Hex hex)
{
	for (int i = 0; i < this->hexlist.size(); i++)
	{
		if (this->hexlist[i].equals(hex))
		{
			return true;
		}
	}
	return false;
}