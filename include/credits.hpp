#include <SFML\Graphics.hpp>
#include <iostream>
#include "cScreen.hpp"
#include <string>
using namespace sf;

class Credits : public cScreen
{
public:
	Credits(void);
	virtual int Run(sf::RenderWindow &App);
private:
	Font f1,f2;
	Text t1,t2,t3;
	String s1,s2,s3;
};
 