#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/screens.hpp"
//#include "Sorting.hpp"
Music music;

int main()
{
    //Applications variables
    std::vector<cScreen*> Screens;
    int screen = 0;
    SoundBuffer buffer;
   
    if (!buffer.loadFromFile("resource/GUI_Select_01_1.wav")) {
        std::cout << "Error!" << std::endl;
    }

    Sound sound1;
    sound1.setBuffer(buffer);

    if (!music.openFromFile("resource/AmongUs.wav")) {
        std::cout << "Error" << std::endl;
    }

    music.play();
    music.setVolume(10.f);
    music.setLoop(true);

    //Window creation
    sf::RenderWindow App(sf::VideoMode(800, 600), "DSA PROJECT");

    //Screens preparations
    menu s0;
    Screens.push_back(&s0);
    SortBattle s1;
    Screens.push_back(&s1);
    Djks s2;
    Screens.push_back(&s2);
    Credits s3;
    Screens.push_back(&s3);

    //Main loop
    while (screen >= 0)
    {
        //background.generate(App);
        
        screen = Screens[screen]->Run(App);
        sound1.play();
    }

    return 0;
}
