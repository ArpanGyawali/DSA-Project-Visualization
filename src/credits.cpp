 #include "../include/credits.hpp"

Credits::Credits(void)
{
  if (!f1.loadFromFile("resource/Mono.ttf"))
  {
    std::cerr << "Error loading Header.ttf" << std::endl;
  }
  if (!f2.loadFromFile("resource/Texturina.ttf"))
  {
    std::cerr << "Error loading Text.ttf" << std::endl;
  }
  s1 = "PROGRAMMED BY: \n***************";
  s2 = "\n->Arpan Gyawali(075BCT014) \n \n->Bijay Shrestha(075BCT020)\n \n->Bidhan Khatiwada(075BCT018) \n\n To Department of Computer Engineering. \t\t\t Mrs Bibha Sthapit \n\n Release date : 05 / 12 / 2020 ";
  s3 = "\t\t\t'esc': Go to Home screen \n\t\t\t'Q': Quit";
  t1.setCharacterSize(40), t1.setFillColor(sf::Color(220,20,60)), t1.setFont(f1), t1.setPosition(230, 40), t1.setString(s1);
  t2.setCharacterSize(24), t2.setFillColor(sf::Color::White), t2.setFont(f2), t2.setPosition(6, 100), t2.setString(s2);
  t3.setCharacterSize(24), t3.setFillColor(sf::Color::White), t3.setFont(f2), t3.setPosition(6, 500), t3.setString(s3);
}

int Credits::Run(sf::RenderWindow &App)
{
  Event eVent;
  bool Running = true;
  Texture Texture;
  Sprite Sprite;
  if (!Texture.loadFromFile("resource/fifteen.png"))
  {
    std::cerr << "Error loading star.jpg" << std::endl;
  }
  Sprite.setTexture(Texture);

	 while (Running) {
    while (App.pollEvent(eVent)) {
      if (eVent.type == sf::Event::Closed) {
        return (-1);
      }
      if (eVent.type == sf::Event::KeyPressed) {
        if (eVent.key.code == sf::Keyboard::Q) {
          return (-1);
        }
        else if (eVent.key.code == sf::Keyboard::Escape) {
          return (0);
        }
      }
    }
    App.clear();
    App.draw(Sprite);
    App.draw(t1);
    App.draw(t2);
    App.draw(t3);
    App.display();
  }
}

