 #include "../include/background.hpp"

Background::Background(float width, float height)
{
   	texts.loadFromFile("resource/star.jpg");
   	texts.setRepeated(true);
	stars.setTexture(texts);
	frame_time = (float) 1 / (float) 60;
	posx = 0;
	passed_time = seconds(0.1);
}


void Background::generate(RenderWindow &window)
{
	passed_time += clock.restart();
     while (passed_time.asSeconds() >= frame_time) {
     	stars.setTextureRect(sf::IntRect(posx, 0, window.getSize().x, window.getSize().y));
        posx += 2;

		window.clear();
        window.draw(stars);

        passed_time -= sf::seconds(frame_time);
    }
}
