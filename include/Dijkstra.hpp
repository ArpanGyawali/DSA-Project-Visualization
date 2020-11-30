#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<functional>
#include<math.h>    
#include<float.h>
#include<vector>
#include<string>
#include "cScreen.hpp"

#define NUM_CELL 60      //number of cells in a row

using namespace std;
using namespace sf;

class Djks : public cScreen
{
private:
	// bool sptSet[NUM_CELL][NUM_CELL];
	// vector<pair<int,int> > pathD;
	int filled[NUM_CELL][NUM_CELL];       //whether cell is colored
    int grid[NUM_CELL][NUM_CELL];       //map with obstacle
    pair<int,int> previous[NUM_CELL][NUM_CELL];
    float dist[NUM_CELL][NUM_CELL];
    int source_x, source_y, dest_x, dest_y;
    int min_x, min_y;
	Font font;
	Text text1;
	//Thread threadD;
	RectangleShape buttonStartD;
	RectangleShape rectangle;
	RectangleShape brectangle;
	RectangleShape grectangle;
	RectangleShape blueRectangle;
	RectangleShape rrectangle;
	RectangleShape yrectangle;
public:
	Djks(void);
	void findmin(float dist[NUM_CELL][NUM_CELL],int& min_x,int& min_y);
	void findpath(pair<int,int> previous[NUM_CELL][NUM_CELL],float dist[NUM_CELL][NUM_CELL],int dest_x,int dest_y,int source_x,int source_y);
	void dijkstra(int source_x,int source_y,int dest_x,int dest_y,int grid[NUM_CELL][NUM_CELL]);
	virtual int Run(RenderWindow &App);
};