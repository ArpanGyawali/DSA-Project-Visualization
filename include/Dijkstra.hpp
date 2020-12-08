

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<functional>
#include<math.h>    
#include<float.h>
#include<vector>
#include<string>
#include "cScreen.hpp"

#define NUM_ROW 30    
#define NUM_COLS 40		

using namespace std;
using namespace sf;

class Djks : public cScreen
{
private:
	int coloured[NUM_ROW][NUM_COLS];     
    int obstacle[NUM_ROW][NUM_COLS];      
    pair<int,int> previous[NUM_ROW][NUM_COLS];
    float dist[NUM_ROW][NUM_COLS];
    int src_x, src_y, dest_x, dest_y;
    int min_x, min_y;
    int shortest_distance = 0;
	Font font1;
	Font font;
	Text text1;
	Text text2;
	Text text;
	Text text3;
	RectangleShape buttonReset;
	RectangleShape buttonLaunch;
	RectangleShape rectangle;
	RectangleShape obsRectangle;
	RectangleShape pathRectangle;
	RectangleShape srcRectangle;
	RectangleShape destRectangle;
	RectangleShape findRectangle;
public:
	Djks(void);
	void reset();
	void findMinimum(float dist[NUM_ROW][NUM_COLS],int& min_x,int& min_y);
	void pathFinder(pair<int,int> previous[NUM_ROW][NUM_COLS],float dist[NUM_ROW][NUM_COLS],int dest_x,int dest_y,int src_x,int src_y);
	void dijkstra(int src_x,int src_y,int dest_x,int dest_y,int obstacle[NUM_ROW][NUM_COLS]);
	virtual int Run(RenderWindow &App);
};