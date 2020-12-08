#include "../include/Quick.hpp"

SortBattle::SortBattle(void) {
	reset();
	buttonRandom.setSize(Vector2f(196, 35));  
	buttonRandom.setFillColor(Color::Transparent);
	buttonRandom.setOutlineThickness(1);
	buttonRandom.setOutlineColor(Color::Red);
	buttonDescending.setSize(Vector2f(196, 35));   
	buttonDescending.setFillColor(Color::Transparent);
	buttonDescending.setOutlineThickness(1);
	buttonDescending.setOutlineColor(Color::Red);
	buttonAlmostSorted.setSize(Vector2f(196, 35));  
	buttonAlmostSorted.setFillColor(Color::Transparent);
	buttonAlmostSorted.setOutlineThickness(1);
	buttonAlmostSorted.setOutlineColor(Color::Red);
	buttonSort.setSize(Vector2f(196, 35));			
	buttonSort.setFillColor(Color::Transparent);
	buttonSort.setOutlineThickness(1);
	buttonSort.setOutlineColor(Color::Red);

	rectangle.setFillColor(sf::Color::White);	
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color(0, 0, 0));

	rectangle1.setFillColor(sf::Color::White);		
	rectangle1.setOutlineThickness(1);
	rectangle1.setOutlineColor(sf::Color(0, 0, 0));

	rectPointer.setFillColor(sf::Color::Transparent);		
	rectPointer.setOutlineThickness(2);
	rectPointer.setOutlineColor(Color::Red);

	if (!font.loadFromFile("resource/Mono.ttf"))
	{
		std::cerr << "Error loading Text.ttf" << std::endl;
	}
	if (!font1.loadFromFile("resource/Texturina.ttf"))
	{
		std::cerr << "Error loading Text.ttf" << std::endl;
	}
	if (!font2.loadFromFile("resource/Underline.ttf"))
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
	text4.setCharacterSize(35);
	text4.setFillColor(Color::Red);

	text.setFont(font);
	text.setString("SORTING");
	text.setCharacterSize(45);
	text.setFillColor(Color::Red);

	text5.setFont(font2);
	text5.setString("Quick sort");
	text5.setCharacterSize(18);
	text5.setFillColor(Color::Red);

	text6.setFont(font2);
	text6.setString("Bubble Sort");
	text6.setCharacterSize(18);
	text6.setFillColor(Color::Red);

	text7.setFont(font2);
	text7.setString("00.00");
	text7.setCharacterSize(18);
	text7.setFillColor(Color::Red);

	text8.setFont(font2);
	text8.setString("00.00");
	text8.setCharacterSize(18);
	text8.setFillColor(Color::Red);
}

void SortBattle::reset() {
	for (size_t i = 0; i < arr.size(); i++) {
		arr[i] = (i + 1) * (540 / arr.size());
	}

	for (size_t j = 0; j < arr1.size(); j++) {
		arr1[j] = (j + 1) * (540 / arr1.size());
	}
	//arr = {0};
	text7.setString("00.00");
	text8.setString("00.00");
	partitionIndexes = { 0 };
	partitionIndexes1 = { 0 };
}

void SortBattle::fillArrayRandom() {
	for (size_t i = 0; i < arr.size(); i++) {
		arr[i] = (i + 1) * (540 / arr.size());
	}


	srand(time(0));
	random_shuffle(arr.begin(), arr.end());	
}

void SortBattle::fillArrayDescending() {
	for (size_t i = arr.size(); i > 0; i--) {
		arr[arr.size() - i] = i * (540 / arr.size());
	}
}

void SortBattle::fillArrayAlmostSorted() {
	array<int, CHUNK_ARRAY_SIZE> arra;
	for (size_t k = 0; k < arr.size(); k = k + CHUNK_ARRAY_SIZE) {
		for (size_t i = 0; i < CHUNK_ARRAY_SIZE; i++) {
			arra[i] = arr[i + k];
		}
		srand(time(0));
		random_shuffle(arra.begin(), arra.end());
		for (size_t j = 0; j < CHUNK_ARRAY_SIZE; j++) {
			arr[j + k] = arra[j];
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

void SortBattle::QuickSort(std::array<int, ARR_MAX_VALUE>* arr, int low, int high) {
	Clock clock1;
	if (low < high)
	{
		int pi = partition(arr, low, high);

		QuickSort(arr, low, pi - 1);
		QuickSort(arr, pi + 1, high);

		// auto preIndexSort = std::async(&SortBattle::QuickSort, this, arr, low, pi - 1);
		// auto postIndexSort = std::async(&SortBattle::QuickSort, this, arr, pi + 1, high);
		// preIndexSort.get();
		// postIndexSort.get();
	}
	Time t1 = clock1.getElapsedTime();
	//float f1 = roundf(t1.asSeconds() * 100) / 100;		
	text7.setString(std::to_string(t1.asSeconds()));
}

int SortBattle::partition(std::array<int, ARR_MAX_VALUE>* ptArr, int low, int high) {
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

void SortBattle::bubbleSort(std::array<int, ARR_MAX_VALUE> *arr1)
{
	//int n = ARR_MAX_VALUE;
	Clock clock2;
	//std::array<int, ARR_MAX_VALUE> arr1 = *pArr;
	for (int i = 0; i < ARR_MAX_VALUE - 1; i++){			
		int count = 0;
		for (int j = 0; j < ARR_MAX_VALUE - i - 1; j++){		
			partitionIndexes1[j] = 1;
			if ((*arr1)[j]>(*arr1)[j+1]) {
				swap(&(*arr1)[j], &(*arr1)[j+1]);
				count ++;
			}
			partitionIndexes1[j] = 0;
		}
		if (count == 0)
			break;
	}
	Time t2 = clock2.getElapsedTime();
	//float f2 = roundf(t2.asSeconds() * 100) / 100;		
	text8.setString(std::to_string(t2.asSeconds()));
}

void SortBattle::swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
	sf::sleep(sf::milliseconds(100));
}

int SortBattle::Run(RenderWindow& App) {
	Thread threadQ(std::bind(&SortBattle::QuickSort, this, &arr, 0, int(arr.size() - 1)));
	Thread threadB(std::bind(&SortBattle::bubbleSort, this, &arr1));
	//View view(Vector2f(0.0f,0.0f),Vector2f(800.0f,600.0f));
	Texture Texture;
	Sprite Sprite;
	SoundBuffer buffer1,buffer2;

	if (!buffer1.loadFromFile("resource/GUI_Select_21_1.wav")) {
		cout << "Error!" << endl;
	}

	if (!buffer2.loadFromFile("resource/GUI_Scroll_Sound_1_1.wav")) {
		cout << "Error!" << endl;
	}

	Sound sound1,sound2;
	sound1.setBuffer(buffer1);
	sound2.setBuffer(buffer2);

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
				threadB.terminate();
				threadQ.terminate();
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

			if (event.type == Event::MouseMoved)
			{
				int X = event.mouseMove.x;
				int Y = event.mouseMove.y;
				if (X > 302 && X < 498 && Y >70 && Y < 105) 
					text1.setFillColor(Color::White);
				else
					text1.setFillColor(Color::Red);

				if (X > 302 && X < 498 && Y>105 && Y < 140) {
					text2.setFillColor(Color::White);
				}
				else
					text2.setFillColor(Color::Red);

				if (X > 302 && X < 498 && Y>140 && Y < 175) {
					text3.setFillColor(Color::White);
				}
				else
					text3.setFillColor(Color::Red);

				if (X > 302 && X < 498 && Y>565 && Y < 599) {
					text4.setFillColor(Color::White);
				}
				else
					text4.setFillColor(Color::Red);    
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				int X = event.mouseButton.x;
				int Y = event.mouseButton.y;
				//cout << "Y-coordinate is: " << Y << endl;
				if (X > 302 && X < 498 && Y>70 && Y < 105) {
					reset();
					sound2.play();
					threadB.terminate();
					threadQ.terminate();
					fillArrayRandom();
					for (int i = 0; i < ARR_MAX_VALUE; ++i)
						arr1[i] = arr[i];
					//auto f = std::async(&SortBattle::QuickSort, this ,arr, 0, arr.size() - 1);
					//QuickSort(&arr, 0, int(arr.size() - 1));
				}
				else if (X > 302 && X < 498 && Y>105 && Y < 140) {
					reset();
					sound2.play();
					threadB.terminate();
					threadQ.terminate();
					fillArrayDescending();
					for (int i = 0; i < ARR_MAX_VALUE; ++i)
						arr1[i] = arr[i];
					//auto f = std::async(&SortBattle::QuickSort, this ,arr, 0, arr.size() - 1);
				}
				else if (X > 302 && X < 498 && Y>140 && Y < 175) {
					reset();
					sound2.play();
					threadB.terminate();
					threadQ.terminate();
					fillArrayAlmostSorted();
					for (int i = 0; i < ARR_MAX_VALUE; ++i)
						arr1[i] = arr[i];
					//auto f = std::async(&SortBattle::QuickSort, this ,arr, 0, arr.size() - 1);
					//QuickSort(&arr, 0, int(arr.size() - 1));
				}
				else if (X > 302 && X < 498 && Y>565 && Y < 599) {
					sound1.play();
					threadB.terminate();
					threadQ.terminate();
					threadB.launch();
					threadQ.launch();
				}
				// else if(X>700 && X <800 && Y>160 && Y<190){
				// 	threadB.launch();
				// }
			}
		}

		App.clear(Color::Black);
		//App.setView(view);
		App.draw(Sprite);

		buttonRandom.setPosition(302, 70);
		buttonDescending.setPosition(302, 105);
		buttonAlmostSorted.setPosition(302, 140);
		buttonSort.setPosition(302, 565);
		App.draw(buttonRandom);
		App.draw(buttonDescending);
		App.draw(buttonAlmostSorted);
		App.draw(buttonSort);
		text.setPosition(310, 10);
		text1.setPosition(330, 73);
		text2.setPosition(310, 108);
		text3.setPosition(304, 143);
		text4.setPosition(355, 564);
		text5.setPosition(10, 10);
		text6.setPosition(650, 10);
		text7.setPosition(190, 10);
		text8.setPosition(510, 10);
		App.draw(text);
		App.draw(text1);
		App.draw(text2);
		App.draw(text3);
		App.draw(text4);
		App.draw(text5);
		App.draw(text6);
		App.draw(text7);
		App.draw(text8);

		float recXsize = ((App.getSize().x) - 500) / arr.size();

		for (size_t i = 0; i < arr.size(); i++) {
			rectangle.setSize(sf::Vector2f(recXsize, arr[i]));
			rectangle.setPosition(recXsize * i, (App.getSize().y - arr[i]));
			App.draw(rectangle);
		}

		for (size_t i = 0; i < arr1.size(); i++) {
			rectangle1.setSize(sf::Vector2f(recXsize, arr1[i]));
			rectangle1.setPosition(recXsize * i + 500, (App.getSize().y - arr1[i]));
			App.draw(rectangle1);
		}

		for (size_t i = 0; i < partitionIndexes.size(); i++) {
			if (partitionIndexes[i] == 1) {
				rectPointer.setSize(sf::Vector2f(recXsize, 540));
				rectPointer.setPosition(recXsize * i + recXsize, 60);
				App.draw(rectPointer);
			}
		}

		for (size_t i = 0; i < partitionIndexes1.size(); i++) {
			if (partitionIndexes1[i] == 1) {
				rectPointer.setSize(sf::Vector2f(recXsize, 540));
				rectPointer.setPosition(recXsize * i + 500 + recXsize, 60);
				App.draw(rectPointer);
			}
		}
		App.display();
	}
}