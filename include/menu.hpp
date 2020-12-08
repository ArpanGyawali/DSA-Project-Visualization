#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define MAX_Number_OF_TEXT 4
using namespace sf;

class menu : public cScreen
{
private:
	// SoundBuffer sb1, sb2;
	// Sound s1, s2;
	Music m1;
	int alpha_max;
	int alpha_div;
	bool playing;
	int selectedItemIndex;
public:
	menu(void);
	int getPressedItem();
	virtual int Run(sf::RenderWindow &App);
};