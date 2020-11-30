#include "../include/Quick.hpp"

QuickSort::QuickSort(void) {
	for (size_t i = 0; i < arr.size(); i++) {
		arr[i] = (i+1) * (600/ arr.size());
	}
	//arr = {0};
	partitionIndexes = {0};

	buttonRandom.setSize(Vector2f(100,30));   //button generate random fill
    buttonRandom.setFillColor(Color::Green);
    buttonDescending.setSize(Vector2f(100,30));   //button generate random fill
    buttonDescending.setFillColor(Color(126,0,0));
    buttonAlmostSorted.setSize(Vector2f(100,30));   //button generate random fill
    buttonAlmostSorted.setFillColor(Color::Blue);
    buttonSort.setSize(Vector2f(100,30));			//button to launch sorting
    buttonSort.setFillColor(Color(148,0,211));

	rectangle.setFillColor(sf::Color::White);		//rectangular shae for arrays
	rectangle.setOutlineThickness(1.f);
	rectangle.setOutlineColor(sf::Color(0, 0, 0));

	rectPointer.setFillColor(sf::Color::Red);		//rectangular shape for pointer

	if (!font.loadFromFile("resource/Text.ttf"))
	{
		std::cerr << "Error loading Text.ttf" << std::endl;
	}
	text1.setFont(font);
	text1.setString("RANDOM");
	text1.setCharacterSize(15);

	text2.setFont(font);
	text2.setString("DESCENDING");
	text2.setCharacterSize(12);

	text3.setFont(font);
	text3.setString("ALMOST \nSORTED");
	text3.setCharacterSize(10);

	text.setFont(font);
	text.setString("SORT");
	text.setCharacterSize(15);
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

void QuickSort::swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
	sf::sleep(sf::milliseconds(30));
}

int QuickSort::Run(RenderWindow &App) {
	Thread threadQ(std::bind(&QuickSort::sortArray,this,&arr,0,int(arr.size()-1)));
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
					return (0);
					break;
				case sf::Keyboard::Q:
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
                if(X>700 && X<800 && Y>0 && Y<30){
                	fillArrayRandom();
                	//auto f = std::async(&QuickSort::sortArray, this ,arr, 0, arr.size() - 1);
					//sortArray(&arr, 0, int(arr.size() - 1));
				}
                else if(X>700 && X<800 && Y>40 && Y<70){
                	fillArrayDescending();
                	//auto f = std::async(&QuickSort::sortArray, this ,arr, 0, arr.size() - 1);
				}
                else if(X>700 && X<800 && Y>80 && Y<110){
                	fillArrayAlmostSorted();
                	//auto f = std::async(&QuickSort::sortArray, this ,arr, 0, arr.size() - 1);
					//sortArray(&arr, 0, int(arr.size() - 1));
				}
				else if(X>700 && X <800 && Y>120 && Y<150){
					threadQ.launch();
				}
            }
		}

		App.clear(Color::Black);

		buttonRandom.setPosition(700,0);
		buttonDescending.setPosition(700,40);
		buttonAlmostSorted.setPosition(700,80);
		buttonSort.setPosition(700,120);
		App.draw(buttonRandom);
		App.draw(buttonDescending);
		App.draw(buttonAlmostSorted);
		App.draw(buttonSort);
		text.setPosition(705,125);
		text1.setPosition(702,5);
		text2.setPosition(702,45);
		text3.setPosition(705,82);
		App.draw(text);
		App.draw(text1);
		App.draw(text2);
		App.draw(text3);

		float recXsize = ((App.getSize().x)-100)/ arr.size();
	
		for(size_t i = 0 ; i < arr.size() ; i++){
			rectangle.setSize(sf::Vector2f(recXsize, arr[i]));
			rectangle.setPosition(recXsize*i, (App.getSize().y - arr[i]));
			App.draw(rectangle);
		}

		for (size_t i = 0; i < partitionIndexes.size(); i++){
			if(partitionIndexes[i] == 1){
				rectPointer.setSize(sf::Vector2f(recXsize, App.getSize().y));
				rectPointer.setPosition(recXsize*i + recXsize, 0);
				App.draw(rectPointer);
			}
		}
		App.display();
	}
}