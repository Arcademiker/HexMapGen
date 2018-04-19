//todo write class in capital letter

#include <iostream>
#include <stdio.h>
//#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <string>
#include <bitset>
#include "../include/hex.h" //change on windows
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using namespace cv;
//using namespace std;


int myrandom (int i) { return std::rand()%i;}

Mat reMakeMap();
void makeMap(std::vector<std::vector<Hex>> &world);
Mat draw(std::vector<std::vector<Hex>> world);
class Hex;
class Edge;

int fail;

int main()
{
	std::srand ( unsigned ( std::time(0) ) );
	fail = 0;
	for (int i=0;i<20;i++) {
		//cutting a square shaped output image out of the whole calculated draw screen(most of the draw screen is black)
        //and calling the reMakeMap() function which creates one
		Mat output(reMakeMap(), Rect(150, 300, 330, 330));
        //double the size of the output image for better visibility for screens with higher resolutions
		resize(output, output, Size(0, 0), 2, 2, INTER_AREA);
		//opencv statement to show the output image on the user screen
		imshow("map", output);
		waitKey(0);
		//cvWaitKey(1000);
		std::cout << std::endl;
	}


	std::cout << "map generations where at least one tile was left over: " << fail << std::endl;
    waitKey(0);

	return 0;
}

//clear the whole logical HexMap and calling the HexMap generation function makeMap().
//(HexMap = map out of hexagon shaped tiles)
Mat reMakeMap()
{
	//defines
	std::vector<std::vector<Hex>> world;
	std::vector<Hex> line;
	Edge* edge = new Edge();
	std::bitset<7> rim = std::bitset<7>("0000001");
	
	//logical empty HexMap generation
	for (int y = 0; y<26; y++)
	{
		for (int x = 0; x<26; x++)
		{
			line.push_back(Hex(edge,x, y));
		}
		world.push_back(line);
		line.clear();
	}

	//logical hexagonal rim for the map (blue hexagons):
	for (int y = 8; y < 14; y++)
	{
		world[y][7].set_changed(rim);
	}
	for (int y = 3; y < 8; y++)
	{
		world[y][17].set_changed(rim);
	}
	for (int x = 12; x < 18; x++)
	{
		world[3][x].set_changed(rim);
	}
	for (int x = 7; x < 12; x++)
	{
		world[13][x].set_changed(rim);
	}
	for (int a = 0; a < 6; a++)
	{
		world[8 - a][7 + a].set_changed(rim);
	}
	for (int a = 0; a < 6; a++)
	{
		world[13 - a][12 + a].set_changed(rim);
	}

    //opencv statement to create an empty screen with 650x650 pixels
	Mat view(Size(650, 650), CV_8UC3);
    //fills the empty logical HexMap with actual
	makeMap(world);
	view = draw(world);
	return view;
}

//creates the logical HexMap (map out of hexagon shaped tiles)
void makeMap(std::vector<std::vector<Hex>> &world)
{
	std::vector<Hex> tile;
	//tile.push_back(Hex(std::bitset<7>("0000001"), 0));
	tile.push_back(Hex(std::bitset<7>("0000011"), 1));
	tile.push_back(Hex(std::bitset<7>("0000111"), 2));
	tile.push_back(Hex(std::bitset<7>("0001011"), 3));
	tile.push_back(Hex(std::bitset<7>("0010011"), 4));
	tile.push_back(Hex(std::bitset<7>("0010111"), 5));
	tile.push_back(Hex(std::bitset<7>("0001111"), 6));
	tile.push_back(Hex(std::bitset<7>("0101011"), 7));
	tile.push_back(Hex(std::bitset<7>("0100111"), 8));
	tile.push_back(Hex(std::bitset<7>("0110111"), 9));
	tile.push_back(Hex(std::bitset<7>("0101111"), 10));
	tile.push_back(Hex(std::bitset<7>("0011111"), 11));
	tile.push_back(Hex(std::bitset<7>("0111111"), 12));
	tile.push_back(Hex(std::bitset<7>("1111111"), 13));
	
	//tile.push_back(Hex(std::bitset<7>("0000000"), 14));
	tile.push_back(Hex(std::bitset<7>("0000110"), 15));
	tile.push_back(Hex(std::bitset<7>("0001010"), 16));
	tile.push_back(Hex(std::bitset<7>("0010010"), 17));
	tile.push_back(Hex(std::bitset<7>("0011110"), 18));
	tile.push_back(Hex(std::bitset<7>("0011110"), 19));
	tile.push_back(Hex(std::bitset<7>("0011110"), 20));
	tile.push_back(Hex(std::bitset<7>("0101110"), 21));
	tile.push_back(Hex(std::bitset<7>("0110110"), 22));
	tile.push_back(Hex(std::bitset<7>("0110110"), 23));
	tile.push_back(Hex(std::bitset<7>("0111010"), 24));
	tile.push_back(Hex(std::bitset<7>("1011010"), 25));
	tile.push_back(Hex(std::bitset<7>("1101010"), 26));
	tile.push_back(Hex(std::bitset<7>("1111110"), 27));
	tile.push_back(Hex(std::bitset<7>("1111110"), 28));
	tile.push_back(Hex(std::bitset<7>("1111110"), 29));
	tile.push_back(Hex(std::bitset<7>("1111110"), 30));
	tile.push_back(Hex(std::bitset<7>("1111110"), 31));
	
	//tile.push_back(Hex(std::bitset<7>("0000001"), 0));
	//tile.push_back(Hex(std::bitset<7>("0000011"), 1));
	tile.push_back(Hex(std::bitset<7>("0000111"), 2));
	tile.push_back(Hex(std::bitset<7>("0001011"), 3));
	tile.push_back(Hex(std::bitset<7>("0010011"), 4));
	tile.push_back(Hex(std::bitset<7>("0010111"), 5));
	tile.push_back(Hex(std::bitset<7>("0001111"), 6));
	tile.push_back(Hex(std::bitset<7>("0101011"), 7));
	tile.push_back(Hex(std::bitset<7>("0100111"), 8));
	tile.push_back(Hex(std::bitset<7>("0110111"), 9));
	tile.push_back(Hex(std::bitset<7>("0101111"), 10));
	tile.push_back(Hex(std::bitset<7>("0011111"), 11));
	tile.push_back(Hex(std::bitset<7>("0111111"), 12));
	tile.push_back(Hex(std::bitset<7>("1111111"), 13));
	//
	////tile.push_back(Hex(std::bitset<7>("0000000"), 14));
	//tile.push_back(Hex(std::bitset<7>("0000110"), 15));
	//tile.push_back(Hex(std::bitset<7>("0001010"), 16));
	//tile.push_back(Hex(std::bitset<7>("0010010"), 17));
	//tile.push_back(Hex(std::bitset<7>("0011110"), 18));
	//tile.push_back(Hex(std::bitset<7>("0011110"), 19));
	//tile.push_back(Hex(std::bitset<7>("0011110"), 20));
	//tile.push_back(Hex(std::bitset<7>("0101110"), 21));
	//tile.push_back(Hex(std::bitset<7>("0110110"), 22));
	//tile.push_back(Hex(std::bitset<7>("0110110"), 23));
	//tile.push_back(Hex(std::bitset<7>("0111010"), 24));
	//tile.push_back(Hex(std::bitset<7>("1011010"), 25));
	//tile.push_back(Hex(std::bitset<7>("1101010"), 26));
	//tile.push_back(Hex(std::bitset<7>("1111110"), 27));
	//tile.push_back(Hex(std::bitset<7>("1111110"), 28));
	//tile.push_back(Hex(std::bitset<7>("1111110"), 29));
	//tile.push_back(Hex(std::bitset<7>("1111110"), 30));
	//tile.push_back(Hex(std::bitset<7>("1111110"), 31));

    //generation of the logical HexMap:
	int n = tile.size();
	int x = 12;
	int y = 8;

	//placing of the first hexagon tile
	random_shuffle(tile.begin(), tile.end(), myrandom);
	int rrand = myrandom(6);
	tile[tile.size() - 1].rotMec(rrand);
	world[y][x].set_bitset(world, tile[tile.size() - 1]);
	tile.pop_back();

	//placing the rest of the hexagon tiles
	Hex tmp;
	int tilesize;
	int counter = 0;
	std::vector<Hex> stack;
	Hex free;
	int tilescounter = 0;
	while (!tile.empty())
	{
		random_shuffle(tile.begin(), tile.end(), myrandom);
		tilesize = tile.size();
		for (int j = 0; j < tile.size(); j++)
		{
			tmp = tile[j];
			stack = world[y][x].edge_clone();
			random_shuffle(stack.begin(), stack.end(), myrandom);
			rrand = 6;
			for (int k = 0; k < stack.size(); k++) {
				free = stack[k];
				tmp.rotMec(6-rrand);
				rrand = myrandom(6);
				tmp.rotMec(rrand);
				for (int r = 0; r < 6; r++)
				{
					if ((tmp.get_connects() & world[free.get_y()][free.get_x()].get_changed()) == (world[free.get_y()][free.get_x()].get_connects() & world[free.get_y()][free.get_x()].get_changed())) //110010&111000==110000&111000
					{
						world[free.get_y()][free.get_x()].set_bitset(world, tmp);
						tile.erase(tile.begin() + j);
						r = 6;
						k = stack.size();
						j = tile.size();
					}
					tmp.rotMec(1);
				}
				counter++;
				
			}
			tilescounter++;
		}
		if (tilesize == tile.size())
		{
			//world[y][x].get_Edge()->hexlist.clear();
			//world[y][x].emergencyprotokoll(world);
			fail++;
			break;
		}
	}

    //calculations of some statistics:
	std::cout << std::endl << "laid tiles total:" <<  n-tile.size() << std::endl;
	std::cout << "total number of tries to lay down a specific tile (without rotations of the tiles): " << counter << std::endl;
	std::cout << "used tiles (including discarded ones): " << tilescounter << std::endl;
	double mean;
	mean = double(counter) / double(tilescounter);
	std::cout << "per field: " << mean << std::endl;
	mean = double(tilescounter) / double(n - tile.size());
	std::cout << "per tile: " << mean << std::endl;
}

//receives the logical HexMap and draws it by
//searching for the specific images out of the ressources folder that fits the logical hexagon tiles
Mat draw(std::vector<std::vector<Hex>> world)
{
    //defines the image size of one hexagon tile
	Mat imgHex(Size(32, 32), CV_8UC3, float(0));
    //defines (temporary) screen size where the hexagon tiles a drawn onto
	Mat map(Size(650, 650), CV_8UC3, float(0));
	for(int y=0; y<25; y++)
	{
		for(int x=0; x<25; x++)
		{

			//draw rim
			if (world[y][x].get_changed()[0] == 1 && world[y][x].get_changed().count() < 7)
			{
				imgHex = imread("../ressources/rim.png", CV_LOAD_IMAGE_COLOR);
				for (int i = 0; i < 16; i++)
				{
					for (int j = 8 - ((i + 1) / 2); j < 23 + ((i + 1) / 2); j++)
					{
						map.at<Vec3b>(32 * y + x * 16 + i, 32 * x - x * 8 + j) = imgHex.at<Vec3b>(i, j);
					}
				}
				for (int i = 16; i < 32; i++)
				{
					for (int j = ((i + 1) / 2) - 8; j < 40 - ((i + 1) / 2); j++)
					{
						map.at<Vec3b>(32 * y + x * 16 + i, 32 * x - x * 8 + j) = imgHex.at<Vec3b>(i, j);
					}
				}
			}
			//draw map
			if (world[y][x].get_changed().count() == 7)
			{
				int r = world[y][x].get_rotN();
				int s = world[y][x].get_tileNumber();
				switch (r)
				{
				case 0:
					switch (s)
					{
					case 0:
						imgHex = imread("../ressources/0000001r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 1:
						imgHex = imread("../ressources/0000011r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 2:
						imgHex = imread("../ressources/0000111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 3:
						imgHex = imread("../ressources/0001011r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 4:
						imgHex = imread("../ressources/0010011r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 5:
						imgHex = imread("../ressources/0010111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 6:
						imgHex = imread("../ressources/0001111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 7:
						imgHex = imread("../ressources/0101011r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 8:
						imgHex = imread("../ressources/0100111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 9:
						imgHex = imread("../ressources/0110111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 10:
						imgHex = imread("../ressources/0101111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 11:
						imgHex = imread("../ressources/0011111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 12:
						imgHex = imread("../ressources/0111111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 13:
						imgHex = imread("../ressources/1111111r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 14:
						imgHex = imread("../ressources/0000000r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 15:
						imgHex = imread("../ressources/0000110r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 16:
						imgHex = imread("../ressources/0001010r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 17:
						imgHex = imread("../ressources/0010010r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 18:
						imgHex = imread("../ressources/0012210r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 19:
						imgHex = imread("../ressources/0021210r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 20:
						imgHex = imread("../ressources/0022110r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 21:
						imgHex = imread("../ressources/0201210r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 22:
						imgHex = imread("../ressources/0210210r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 23:
						imgHex = imread("../ressources/0220110r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 24:
						imgHex = imread("../ressources/0221010r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 25:
						imgHex = imread("../ressources/2021010r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 26:
						imgHex = imread("../ressources/2201010r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 27:
						imgHex = imread("../ressources/2321310r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 28:
						imgHex = imread("../ressources/2331210r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 29:
						imgHex = imread("../ressources/3213210r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 30:
						imgHex = imread("../ressources/3312210r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 31:
						imgHex = imread("../ressources/3322110r.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					default:
						break;
					}
					break;
				case 1:
					switch (s)
					{
					case 0:
						imgHex = imread("../ressources/0000001r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 1:
						imgHex = imread("../ressources/0000011r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 2:
						imgHex = imread("../ressources/0000111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 3:
						imgHex = imread("../ressources/0001011r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 4:
						imgHex = imread("../ressources/0010011r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 5:
						imgHex = imread("../ressources/0010111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 6:
						imgHex = imread("../ressources/0001111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 7:
						imgHex = imread("../ressources/0101011r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 8:
						imgHex = imread("../ressources/0100111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 9:
						imgHex = imread("../ressources/0110111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 10:
						imgHex = imread("../ressources/0101111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 11:
						imgHex = imread("../ressources/0011111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 12:
						imgHex = imread("../ressources/0111111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 13:
						imgHex = imread("../ressources/1111111r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 14:
						imgHex = imread("../ressources/0000000r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 15:
						imgHex = imread("../ressources/0000110r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 16:
						imgHex = imread("../ressources/0001010r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 17:
						imgHex = imread("../ressources/0010010r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 18:
						imgHex = imread("../ressources/0012210r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 19:
						imgHex = imread("../ressources/0021210r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 20:
						imgHex = imread("../ressources/0022110r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 21:
						imgHex = imread("../ressources/0201210r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 22:
						imgHex = imread("../ressources/0210210r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 23:
						imgHex = imread("../ressources/0220110r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 24:
						imgHex = imread("../ressources/0221010r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 25:
						imgHex = imread("../ressources/2021010r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 26:
						imgHex = imread("../ressources/2201010r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 27:
						imgHex = imread("../ressources/2321310r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 28:
						imgHex = imread("../ressources/2331210r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 29:
						imgHex = imread("../ressources/3213210r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 30:
						imgHex = imread("../ressources/3312210r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 31:
						imgHex = imread("../ressources/3322110r2.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					default:
						break;
					}
					break;
				case 2:
					switch (s)
					{
					case 0:
						imgHex = imread("../ressources/0000001.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 1:
						imgHex = imread("../ressources/0000011.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 2:
						imgHex = imread("../ressources/0000111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 3:
						imgHex = imread("../ressources/0001011.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 4:
						imgHex = imread("../ressources/0010011.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 5:
						imgHex = imread("../ressources/0010111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 6:
						imgHex = imread("../ressources/0001111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 7:
						imgHex = imread("../ressources/0101011.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 8:
						imgHex = imread("../ressources/0100111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 9:
						imgHex = imread("../ressources/0110111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 10:
						imgHex = imread("../ressources/0101111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 11:
						imgHex = imread("../ressources/0011111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 12:
						imgHex = imread("../ressources/0111111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 13:
						imgHex = imread("../ressources/1111111.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 14:
						imgHex = imread("../ressources/0000000.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 15:
						imgHex = imread("../ressources/0000110.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 16:
						imgHex = imread("../ressources/0001010.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 17:
						imgHex = imread("../ressources/0010010.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 18:
						imgHex = imread("../ressources/0012210.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 19:
						imgHex = imread("../ressources/0021210.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 20:
						imgHex = imread("../ressources/0022110.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 21:
						imgHex = imread("../ressources/0201210.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 22:
						imgHex = imread("../ressources/0210210.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 23:
						imgHex = imread("../ressources/0220110.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 24:
						imgHex = imread("../ressources/0221010.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 25:
						imgHex = imread("../ressources/2021010.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 26:
						imgHex = imread("../ressources/2201010.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 27:
						imgHex = imread("../ressources/2321310.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 28:
						imgHex = imread("../ressources/2331210.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 29:
						imgHex = imread("../ressources/3213210.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 30:
						imgHex = imread("../ressources/3312210.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 31:
						imgHex = imread("../ressources/3322110.png", CV_LOAD_IMAGE_COLOR);
						break;
					default:
						break;
					}
					break;
				case 3:
					switch (s)
					{
					case 0:
						imgHex = imread("../ressources/0000001r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 1:
						imgHex = imread("../ressources/0000011r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 2:
						imgHex = imread("../ressources/0000111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 3:
						imgHex = imread("../ressources/0001011r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 4:
						imgHex = imread("../ressources/0010011r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 5:
						imgHex = imread("../ressources/0010111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 6:
						imgHex = imread("../ressources/0001111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 7:
						imgHex = imread("../ressources/0101011r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 8:
						imgHex = imread("../ressources/0100111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 9:
						imgHex = imread("../ressources/0110111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 10:
						imgHex = imread("../ressources/0101111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 11:
						imgHex = imread("../ressources/0011111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 12:
						imgHex = imread("../ressources/0111111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 13:
						imgHex = imread("../ressources/1111111r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 14:
						imgHex = imread("../ressources/0000000r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 15:
						imgHex = imread("../ressources/0000110r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 16:
						imgHex = imread("../ressources/0001010r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 17:
						imgHex = imread("../ressources/0010010r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 18:
						imgHex = imread("../ressources/0012210r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 19:
						imgHex = imread("../ressources/0021210r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 20:
						imgHex = imread("../ressources/0022110r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 21:
						imgHex = imread("../ressources/0201210r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 22:
						imgHex = imread("../ressources/0210210r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 23:
						imgHex = imread("../ressources/0220110r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 24:
						imgHex = imread("../ressources/0221010r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 25:
						imgHex = imread("../ressources/2021010r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 26:
						imgHex = imread("../ressources/2201010r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 27:
						imgHex = imread("../ressources/2321310r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 28:
						imgHex = imread("../ressources/2331210r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 29:
						imgHex = imread("../ressources/3213210r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 30:
						imgHex = imread("../ressources/3312210r.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 31:
						imgHex = imread("../ressources/3322110r.png", CV_LOAD_IMAGE_COLOR);
						break;
					default:
						break;
					}
					break;
				case 4:
					switch (s)
					{
					case 0:
						imgHex = imread("../ressources/0000001r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 1:
						imgHex = imread("../ressources/0000011r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 2:
						imgHex = imread("../ressources/0000111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 3:
						imgHex = imread("../ressources/0001011r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 4:
						imgHex = imread("../ressources/0010011r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 5:
						imgHex = imread("../ressources/0010111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 6:
						imgHex = imread("../ressources/0001111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 7:
						imgHex = imread("../ressources/0101011r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 8:
						imgHex = imread("../ressources/0100111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 9:
						imgHex = imread("../ressources/0110111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 10:
						imgHex = imread("../ressources/0101111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 11:
						imgHex = imread("../ressources/0011111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 12:
						imgHex = imread("../ressources/0111111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 13:
						imgHex = imread("../ressources/1111111r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 14:
						imgHex = imread("../ressources/0000000r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 15:
						imgHex = imread("../ressources/0000110r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 16:
						imgHex = imread("../ressources/0001010r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 17:
						imgHex = imread("../ressources/0010010r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 18:
						imgHex = imread("../ressources/0012210r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 19:
						imgHex = imread("../ressources/0021210r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 20:
						imgHex = imread("../ressources/0022110r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 21:
						imgHex = imread("../ressources/0201210r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 22:
						imgHex = imread("../ressources/0210210r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 23:
						imgHex = imread("../ressources/0220110r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 24:
						imgHex = imread("../ressources/0221010r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 25:
						imgHex = imread("../ressources/2021010r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 26:
						imgHex = imread("../ressources/2201010r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 27:
						imgHex = imread("../ressources/2321310r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 28:
						imgHex = imread("../ressources/2331210r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 29:
						imgHex = imread("../ressources/3213210r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 30:
						imgHex = imread("../ressources/3312210r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					case 31:
						imgHex = imread("../ressources/3322110r2.png", CV_LOAD_IMAGE_COLOR);
						break;
					default:
						break;
					}
					break;
				case 5:
					switch (s)
					{
					case 0:
						imgHex = imread("../ressources/0000001.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 1:
						imgHex = imread("../ressources/0000011.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 2:
						imgHex = imread("../ressources/0000111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 3:
						imgHex = imread("../ressources/0001011.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 4:
						imgHex = imread("../ressources/0010011.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 5:
						imgHex = imread("../ressources/0010111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 6:
						imgHex = imread("../ressources/0001111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 7:
						imgHex = imread("../ressources/0101011.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 8:
						imgHex = imread("../ressources/0100111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 9:
						imgHex = imread("../ressources/0110111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 10:
						imgHex = imread("../ressources/0101111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 11:
						imgHex = imread("../ressources/0011111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 12:
						imgHex = imread("../ressources/0111111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 13:
						imgHex = imread("../ressources/1111111.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 14:
						imgHex = imread("../ressources/0000000.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 15:
						imgHex = imread("../ressources/0000110.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 16:
						imgHex = imread("../ressources/0001010.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 17:
						imgHex = imread("../ressources/0010010.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 18:
						imgHex = imread("../ressources/0012210.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 19:
						imgHex = imread("../ressources/0021210.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 20:
						imgHex = imread("../ressources/0022110.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 21:
						imgHex = imread("../ressources/0201210.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 22:
						imgHex = imread("../ressources/0210210.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 23:
						imgHex = imread("../ressources/0220110.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 24:
						imgHex = imread("../ressources/0221010.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 25:
						imgHex = imread("../ressources/2021010.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 26:
						imgHex = imread("../ressources/2201010.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 27:
						imgHex = imread("../ressources/2321310.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 28:
						imgHex = imread("../ressources/2331210.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 29:
						imgHex = imread("../ressources/3213210.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 30:
						imgHex = imread("../ressources/3312210.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					case 31:
						imgHex = imread("../ressources/3322110.png", CV_LOAD_IMAGE_COLOR);
						flip(imgHex, imgHex, 0);
						flip(imgHex, imgHex, 1);
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				
				for (int i = 0; i < 16; i++)
				{
					for (int j = 8 - ((i + 1) / 2); j < 23 + ((i + 1) / 2); j++)
					{
						map.at<Vec3b>(32 * y + x * 16 + i, 32 * x - x * 8 + j) = imgHex.at<Vec3b>(i, j);
					}
				}
				for (int i = 16; i < 32; i++)
				{
					for (int j = ((i + 1) / 2) - 8; j < 40 - ((i + 1) / 2); j++)
					{
						map.at<Vec3b>(32 * y + x * 16 + i, 32 * x - x * 8 + j) = imgHex.at<Vec3b>(i, j);
					}
				}				
			}

		}
	}
	return map;
}





//"0000000"
//"0000110"
//"0001010"
//"0010010"
//"0012210"
//"0021210"
//"0022110"
//"0201210"
//"0210210"
//"0220110"
//"0221010"
//"2021010"
//"2201010"
//"2321310"
//"2331210"
//"3213210"
//"3312210"
//"3322110"