

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<functional>
#include<math.h>    
#include<float.h>
#include<vector>
#include<string>
#include "cScreen.hpp"

#define NUM_ROW 30      //number of row
#define NUM_COLS 40		//number of col

using namespace std;
using namespace sf;

class Djks : public cScreen
{
private:
	// bool sptSet[NUM_CELL][NUM_CELL];
	// vector<pair<int,int> > pathD;
	int filled[NUM_ROW][NUM_COLS];       //whether cell is colored
    int grid[NUM_ROW][NUM_COLS];       //map with obstacle
    pair<int,int> previous[NUM_ROW][NUM_COLS];
    float dist[NUM_ROW][NUM_COLS];
    int source_x, source_y, dest_x, dest_y;
    int min_x, min_y;
    int shortest_distance = 0;
	Font font1;
	Font font;
	Text text1;
	Text text2;
	Text text;
	Text text3;
	RectangleShape buttonReset;
	RectangleShape buttonStartD;
	RectangleShape rectangle;
	RectangleShape brectangle;
	RectangleShape grectangle;
	RectangleShape blueRectangle;
	RectangleShape rrectangle;
	RectangleShape yrectangle;
public:
	Djks(void);
	void reset();
	void findmin(float dist[NUM_ROW][NUM_COLS],int& min_x,int& min_y);
	void findpath(pair<int,int> previous[NUM_ROW][NUM_COLS],float dist[NUM_ROW][NUM_COLS],int dest_x,int dest_y,int source_x,int source_y);
	void dijkstra(int source_x,int source_y,int dest_x,int dest_y,int grid[NUM_ROW][NUM_COLS]);
	virtual int Run(RenderWindow &App);
};