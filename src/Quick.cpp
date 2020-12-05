#include "../include/Quick.hpp"

QuickSort::QuickSort(void) {
	reset();
	buttonRandom.setSize(Vector2f(196,35));   //button generate random fill
    buttonRandom.setFillColor(Color::Transparent);
    buttonRandom.setOutlineThickness(1);
    buttonRandom.setOutlineColor(Color::Red);
    buttonDescending.setSize(Vector2f(196,35));   //button generate random fill
    buttonDescending.setFillColor(Color::Transparent);
    buttonDescending.setOutlineThickness(1);
    buttonDescending.setOutlineColor(Color::Red);
    buttonAlmostSorted.setSize(Vector2f(196,35));   //button generate random fill
    buttonAlmostSorted.setFillColor(Color::Transparent);
    buttonAlmostSorted.setOutlineThickness(1);
    buttonAlmostSorted.setOutlineColor(Color::Red);
    buttonSort.setSize(Vector2f(196,35));			//button to launch sorting
    buttonSort.setFillColor(Color::Transparent);
    buttonSort.setOutlineThickness(1);
    buttonSort.setOutlineColor(Color::Red);

	rectangle.setFillColor(sf::Color::White);		//rectangular shape for array arr
	rectangle.setOutlineThickness(1.f);
	rectangle.setOutlineColor(sf::Color(0, 0, 0));

	rectangle1.setFillColor(sf::Color::White);		//rectangular shape for array arr1
	rectangle1.setOutlineThickness(1.f);
	rectangle1.setOutlineColor(sf::Color(0, 0, 0));

	rectPointer.setFillColor(sf::Color::Red);		//rectangular shape for pointer

	if (!font.loadFromFile("resource/Mono.ttf"))
	{
		std::cerr << "Error loading Text.ttf" << std::endl;
	}
	if (!font1.loadFromFile("resource/Texturina.ttf"))
	{
		std::cerr << "Error loading Text.ttf" << std::endl;
	}
	text1.setFont(font1);
	text1.setString("RANDOM");
	text1.setCharacterSize(25);
	text1.setFillColor(Color::Red);

	text2.setFont(font1);
	text2.setString("DESCENDING");
	text2.setCharacterSize(25);
	text2.setFillColor(Color::Red);

	text3.setFont(font1);
	text3.setString("ALMOST SORTED");
	text3.setCharacterSize(21);
	text3.setFillColor(Color::Red);

	text4.setFont(font1);
	text4.setString("SORT");
	text4.setCharacterSize(25);
	text4.setFillColor(Color::Red);

	text.setFont(font);
    text.setString("SORTING");
    text.setCharacterSize(45);
    text.setFillColor(Color::Red);
}

void QuickSort::reset() {
	for (size_t i = 0; i < arr.size(); i++) {
		arr[i] = (i+1) * (600/ arr.size());
	}

	for (size_t j = 0; j < arr1.size(); j++) {
		arr1[j] = (j+1) * (600/ arr1.size());
	}
	//arr = {0};
	partitionIndexes = {0};
	partitionIndexes1 = {0};
}

void QuickSort::fillArrayRandom() {
	//Generate increasing array
	for (size_t i = 0; i < arr.size(); i++) {
		arr[i] = (i+1) * (600/ arr.size());
	}

	//Shuffle array
	srand(time(0));
	random_shuffle(arr.begin(), arr.end());	//generte random numbers every time between arr.begin and arr.end
}

void QuickSort::fillArrayDescending() {
	for (size_t i = arr.size(); i >0; i--) {
		arr[arr.size()-i] = i * (600/ arr.size());
	}
}

void QuickSort::fillArrayAlmostSorted() {
	array<int, CHUNK_ARRAY_SIZE> arra;
	for (size_t k = 0; k<arr.size(); k=k+CHUNK_ARRAY_SIZE){
		for (size_t i = 0; i < CHUNK_ARRAY_SIZE; i++) {
  			arra[i] = arr[i+k];
  		}
  		// shuffleArray(&arra);
  		srand(time(0));
		random_shuffle(arra.begin(), arra.end());
  		for (size_t j = 0; j<CHUNK_ARRAY_SIZE; j++){
  			arr[j+k] = arra[j];
  		}
	}
	// for (size_t i = 0; i < arr.size(); i++) {
	// 	arr[i] = (i+1) * (600/ arr.size());
	// }
	// for (size_t k = 0; k < arr.size(); k++){
	// 	std::swap(arr[k],arr[k+1]);
 //    	std::swap(arr[k+3],arr[k+5]);
 //    }
}

void QuickSort::sortArray(std::array<int, ARR_MAX_VALUE>* arr, int low, int high) {
	if (low < high)
	{
		int pi = partition(arr, low, high);

		sortArray(arr, low, pi - 1);  
		sortArray(arr, pi+1, high);
		
		// auto preIndexSort = std::async(&QuickSort::sortArray, this, arr, low, pi - 1);
		// auto postIndexSort = std::async(&QuickSort::sortArray, this, arr, pi + 1, high);
		// preIndexSort.get();
		// postIndexSort.get();
	}
}

int QuickSort::partition(std::array<int, ARR_MAX_VALUE>* ptArr, int low, int high) {
	std::array<int, ARR_MAX_VALUE> arr = *ptArr;
	int pivot = arr[high];
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++)
	{
		partitionIndexes[j] = 1;
		if (arr[j] < pivot)
		{
			i++;
			swap(&(*ptArr)[i], &(*ptArr)[j]);
		}
		partitionIndexes[j] = 0;
	}
	swap(&(*ptArr)[i + 1], &(*ptArr)[high]);

	return (i + 1);
}

void QuickSort::bubbleSort(std::array<int, ARR_MAX_VALUE>* pArr)
{
	//int n = ARR_MAX_VALUE;

	std::array<int, ARR_MAX_VALUE> arr1 = *pArr;
	for (int i = 0; i < ARR_MAX_VALUE - 1; i++){			//for no of passes
		int count = 0;
		for (int j = 0; j < ARR_MAX_VALUE - i - 1; j++){		//for iteraion (ignoring the last sorted element)
			partitionIndexes1[j] = 1;
			if (arr1[j] > arr1[j + 1]){
				swap(&(*pArr)[j], &(*pArr)[j+1]);
				//std::swap(arr1[j],arr1[j+1]);
				count ++;
			}
			partitionIndexes1[j] = 0;
		}
		if (count == 0)
			break;
	}
}

void QuickSort::swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
	sf::sleep(sf::milliseconds(30));
}

int QuickSort::Run(RenderWindow &App) {
	Thread threadQ(std::bind(&QuickSort::sortArray,this,&arr,0,int(arr.size()-1)));
	Thread threadB(std::bind(&QuickSort::bubbleSort,this,&arr1));
	Texture Texture;
    Sprite Sprite;
    if (!Texture.loadFromFile("resource/red1.png"))
    {
        std::cerr << "Error loading one.jpg" << std::endl;
    }
    Sprite.setTexture(Texture);
	Event event;
	bool Running = true;
	while (Running)
	{
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return (-1);
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					threadB.terminate();
					threadQ.terminate();
					reset();
					return (0);
					break;
				case sf::Keyboard::Q:
					threadB.terminate();
					threadQ.terminate();
					return (-1);
					break;
				default:
					break;
				}
			}
			if(event.type==Event::MouseButtonPressed && event.mouseButton.button==Mouse::Left)
			{
                int X=event.mouseButton.x;
                int Y=event.mouseButton.y;
                if(X>302 && X<498 && Y>70 && Y<105){
                	reset();
                	threadB.terminate();
					threadQ.terminate();
                	fillArrayRandom();
                	for(int i=0; i<ARR_MAX_VALUE; ++i)
        				arr1[i] = arr[i];
                	//auto f = std::async(&QuickSort::sortArray, this ,arr, 0, arr.size() - 1);
					//sortArray(&arr, 0, int(arr.size() - 1));
				}
                else if(X>302 && X<498 && Y>105 && Y<140){
                	reset();
                	threadB.terminate();
					threadQ.terminate();
                	fillArrayDescending();
                	for(int i=0; i<ARR_MAX_VALUE; ++i)
        				arr1[i] = arr[i];
                	//auto f = std::async(&QuickSort::sortArray, this ,arr, 0, arr.size() - 1);
				}
                else if(X>302 && X<498 && Y>140 && Y<175){
                	reset();
                	threadB.terminate();
					threadQ.terminate();
                	fillArrayAlmostSorted();
                	for(int i=0; i<ARR_MAX_VALUE; ++i)
        				arr1[i] = arr[i];
                	//auto f = std::async(&QuickSort::sortArray, this ,arr, 0, arr.size() - 1);
					//sortArray(&arr, 0, int(arr.size() - 1));
				}
				else if(X>302 && X<498 && Y>175 && Y<210){
					threadB.launch();
					threadQ.launch();
				}
				// else if(X>700 && X <800 && Y>160 && Y<190){
				// 	threadB.launch();
				// }
            }
		}

		App.clear(Color::Black);
		App.draw(Sprite);

		buttonRandom.setPosition(302,70);
		buttonDescending.setPosition(302,105);
		buttonAlmostSorted.setPosition(302,140);
		buttonSort.setPosition(302,175);
		App.draw(buttonRandom);
		App.draw(buttonDescending);
		App.draw(buttonAlmostSorted);
		App.draw(buttonSort);
		text.setPosition(310,20);
		text1.setPosition(330,73);
		text2.setPosition(310,108);
		text3.setPosition(304,143);
		text4.setPosition(355,178);
		App.draw(text);
		App.draw(text1);
		App.draw(text2);
		App.draw(text3);
		App.draw(text4);

		float recXsize = ((App.getSize().x)-500)/ arr.size();
	
		for(size_t i = 0 ; i < arr.size() ; i++){
			rectangle.setSize(sf::Vector2f(recXsize, arr[i]));
			rectangle.setPosition(recXsize*i, (App.getSize().y - arr[i]));
			App.draw(rectangle);
		}

		for(size_t i = 0 ; i < arr1.size() ; i++){
			rectangle1.setSize(sf::Vector2f(recXsize, arr1[i]));
			rectangle1.setPosition(recXsize*i + 500, (App.getSize().y - arr1[i]));
			App.draw(rectangle1);
		}

		for (size_t i = 0; i < partitionIndexes.size(); i++){
			if(partitionIndexes[i] == 1){
				rectPointer.setSize(sf::Vector2f(recXsize, App.getSize().y));
				rectPointer.setPosition(recXsize*i + recXsize, 0);
				App.draw(rectPointer);
			}
		}

		for (size_t i = 0; i < partitionIndexes1.size(); i++){
			if(partitionIndexes1[i] == 1){
				rectPointer.setSize(sf::Vector2f(recXsize, App.getSize().y));
				rectPointer.setPosition(recXsize*i + 500 + recXsize, 0);
				App.draw(rectPointer);
			}
		}
		App.display();
	}
}