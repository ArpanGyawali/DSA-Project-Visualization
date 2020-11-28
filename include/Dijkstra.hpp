#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<functional>
#include<math.h>    
#include<float.h>
#include<vector>
#include<string>
#include "cScreen.hpp"
using namespace std;
using namespace sf;
#define num 60      //number of cells in a row

class Djks : public cScreen
{
private:
	// bool sptSet[num][num];
	// vector<pair<int,int> > pathD;
	int filled[num][num];       //whether cell is colored
    int grid[num][num];       //map with obstacle
    pair<int,int> previous[num][num];
    float dist[num][num];
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
	void findmin(float dist[num][num],int& min_x,int& min_y);
	void findpath(pair<int,int> previous[num][num],float dist[num][num],int dest_x,int dest_y,int source_x,int source_y);
	void dijkstra(int source_x,int source_y,int dest_x,int dest_y,int grid[num][num]);
	virtual int Run(RenderWindow &App);
};