// #include <SFML\Graphics.hpp>
// #define MAX_Number_OF_TEXT 4 
// using namespace sf;
// class Menu
// {
// public:
// 	Menu(float width,float height);
// 	~Menu();
// 	void draw(RenderWindow &window);
// 	void moveUp();
// 	void moveDown();
// 	// void moveKeyUp();
// 	// void moveKeyDown();
// 	int getPressedItem();
// private:
// 	int selectedItemIndex;
// 	//int selectedKeyIndex;
// 	Font font;
// 	Text menu[MAX_Number_OF_TEXT];
// 	//Text Key[2]
// };

#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>
#define MAX_Number_OF_TEXT 4
using namespace sf;

class menu : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
	int selectedItemIndex;
public:
	menu(void);
	int getPressedItem();
	virtual int Run(sf::RenderWindow &App);
};