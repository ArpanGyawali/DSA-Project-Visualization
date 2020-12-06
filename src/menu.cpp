#include "../include/menu.hpp"

menu::menu(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
	selectedItemIndex = 0;
	if (!m1.openFromFile("resource/AmongUs.wav"))
	{
		std::cerr << "Error loading start.wav" << std::endl;
	}
	m1.setLoop(true);
	m1.setVolume(50);
	// if (!sb1.loadFromFile("resource/Mono.ttf"))
	// {
	// 	std::cerr << "Error loading HeadText.ttf" << std::endl;
	// }
	// s1.setBuffer(sb1);
	// if (!sb2.loadFromFile("resource/.ttf"))
	// {
	// 	std::cerr << "Error loading HeadText.ttf" << std::endl;
	// }
}

int menu::getPressedItem()
{
	return selectedItemIndex;
}

int menu::Run(sf::RenderWindow &App)
{
	Event event;
	Texture Texture;
	Sprite Sprite;
	bool Running = true;
	int alpha = 0;
	Font font;
	Font font1;
	Text Menu[MAX_Number_OF_TEXT];
	Text head;

	// int menu = 0;
	if (!font1.loadFromFile("resource/Mono.ttf"))
	{
		std::cerr << "Error loading HeadText.ttf" << std::endl;
	}
	head.setFont(font1);
	head.setFillColor(Color::Red);
	head.setString("D.S.A");
	head.setCharacterSize(80);

	if (!font.loadFromFile("resource/Texturina.ttf"))
	{
		std::cerr << "Error loading HeadText.ttf" << std::endl;
	}

	if (!Texture.loadFromFile("resource/aa.jpg"))
	{
		std::cerr << "Error loading aa.jpg" << std::endl;
	}
	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, alpha));

	for (int i = 0; i < MAX_Number_OF_TEXT; i++) {
		Menu[i].setFont(font);
		Menu[i].setPosition(Vector2f(800-220 ,400+(i*50)));
		Menu[i].setCharacterSize(30);
	}

	if (getPressedItem() == 0)
		Menu[0].setFillColor(Color::Red);
	else
		Menu[0].setFillColor(Color::White);
	Menu[0].setString("SORTING VIZ");

	if (getPressedItem() == 1)
		Menu[1].setFillColor(Color::Red);
	else
		Menu[1].setFillColor(Color::White);
	Menu[1].setString("DIJKSTRA");


	if (getPressedItem() == 2)
		Menu[2].setFillColor(Color::Red);
	else
		Menu[2].setFillColor(Color::White);
	Menu[2].setString("CREDITS");

	Menu[3].setFillColor(Color::White);
	Menu[3].setString("EXIT");

	m1.play();

	if (playing)
	{
		alpha = alpha_max;
	}

	while (Running)
	{
		//Verifying events
		//m1.play();
		while (App.pollEvent(event))
		{
			// Window closed
			
			if (event.type == Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Up:
					if (selectedItemIndex - 1 >= 0) {
						Menu[selectedItemIndex].setFillColor(Color::White);
						selectedItemIndex--;
						Menu[selectedItemIndex].setFillColor(Color::Red);
					}
					break;
				case Keyboard::Down:
					if (selectedItemIndex + 1 < MAX_Number_OF_TEXT) {
						Menu[selectedItemIndex].setFillColor(Color::White);
						selectedItemIndex++ ;
						Menu[selectedItemIndex].setFillColor(Color::Red);
					}
					break;
				case Keyboard::Return:
					m1.pause();
					switch (getPressedItem())
                    {
                    case 0:
                    	playing = true;
                        return (1);
                        break;
                    case 1:
                    	playing = true;
                        return (2);
                        break;
                    case 2:
                    	playing = true;
                        return (3);
                        break;
                    case 3:
                        return (-1);
                        break;
                    default:
                        break;
                    }
				default:
					break;
				}
			}
		}

		if (alpha<alpha_max)
		{
			alpha++;
		}
		Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));

		App.clear();
		App.draw(Sprite);
		head.setPosition(50,40);

		if (alpha == alpha_max){
			for (int i = 0; i < MAX_Number_OF_TEXT; i++) {
				App.draw(Menu[i]);
			}
			App.draw(head);
		}
		App.display();
	}
	return (-1);
}
