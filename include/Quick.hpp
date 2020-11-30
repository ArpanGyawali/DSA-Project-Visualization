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

#define ARR_MAX_VALUE 150
#define CHUNK_ARRAY_SIZE 15

using namespace std;
using namespace sf;

class QuickSort : public cScreen
{
private:
	std::array<int, ARR_MAX_VALUE> arr;
	std::array<int, ARR_MAX_VALUE> partitionIndexes;
	RectangleShape buttonRandom;
	RectangleShape buttonDescending;
	RectangleShape buttonAlmostSorted;
	RectangleShape buttonSort;
	RectangleShape rectangle;
	RectangleShape rectPointer;
	Font font;
	Text text1;
	Text text2;
	Text text3;
	Text text;

public:
	QuickSort(void);
	void sortArray(std::array<int, ARR_MAX_VALUE>* arr, int low, int high);
	void fillArrayRandom();
	void fillArrayDescending();
	void fillArrayAlmostSorted();
	int partition(std::array<int, ARR_MAX_VALUE>* arr, int low, int high);
	void swap(int* a, int* b);
	virtual int Run(RenderWindow &App);
};


