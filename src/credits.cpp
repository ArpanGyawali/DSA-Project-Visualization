 #include "../include/credits.hpp"

Credits::Credits(void)
{
  f1.loadFromFile("resource/Header.ttf");
  f2.loadFromFile("resource/Text.ttf");
  s1 = "Programmed by: \n***************************";
  s2 = "\n->Arpan Gyawali(075BCT014) \n \n->Bijay Shrestha(075BCT020)\n \n->Bidhan Khatiwada(075BCT018) \n\n To Department of Computer Engineering. \t\t\t Mrs Bibha Sthapit \n\n Release date : 05 / 12 / 2020 ";
  s3 = "\t\t\t'esc': Go to Home screen \n\t\t\t'Q': Quit";
  t1.setCharacterSize(32), t1.setFillColor(sf::Color::Magenta), t1.setFont(f1), t1.setPosition(200, 40), t1.setString(s1);
  t2.setCharacterSize(24), t2.setFillColor(sf::Color::Blue), t2.setFont(f2), t2.setPosition(6, 100), t2.setString(s2);
  t3.setCharacterSize(24), t3.setFillColor(sf::Color::Blue), t3.setFont(f2), t3.setPosition(6, 500), t3.setString(s3);
}

int Credits::Run(sf::RenderWindow &App)
{
  Event eVent;
  bool Running = true;

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
    App.draw(t1);
    App.draw(t2);
    App.draw(t3);
    App.display();
  }
}

