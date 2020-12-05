#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <array>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>
#include <future>
#include <list>
#include <ctime>
#include "cScreen.hpp"

#define ARR_MAX_VALUE 100
#define CHUNK_ARRAY_SIZE 10

using namespace std;
using namespace sf;

class QuickSort : public cScreen
{
private:
	std::array<int, ARR_MAX_VALUE> arr;
	std::array<int, ARR_MAX_VALUE> arr1;
	std::array<int, ARR_MAX_VALUE> partitionIndexes;
	std::array<int, ARR_MAX_VALUE> partitionIndexes1;
	RectangleShape buttonRandom;
	RectangleShape buttonDescending;
	RectangleShape buttonAlmostSorted;
	RectangleShape buttonSort;
	RectangleShape rectangle;
	RectangleShape rectangle1;
	RectangleShape rectPointer;
	Font font;
	Font font1;
	Text text1;
	Text text2;
	Text text3;
	Text text;
	Text text4;

public:
	QuickSort(void);
	void sortArray(std::array<int, ARR_MAX_VALUE>* arr, int low, int high);
	void bubbleSort(std::array<int, ARR_MAX_VALUE>* arr1);
	void fillArrayRandom();
	void fillArrayDescending();
	void fillArrayAlmostSorted();
	void reset();
	int partition(std::array<int, ARR_MAX_VALUE>* arr, int low, int high);
	void swap(int* a, int* b);
	virtual int Run(RenderWindow &App);
};


