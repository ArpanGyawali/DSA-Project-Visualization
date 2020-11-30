#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/screens.hpp"
//#include "../include/background.hpp"


int main()
{
    //Applications variables
    std::vector<cScreen*> Screens;
    int screen = 0;

    //Window creation
    sf::RenderWindow App(sf::VideoMode(800, 600), "DSA PROJECT");
    //Background background(800, 600);

    //Screens preparations
    menu s0;
    Screens.push_back(&s0);
    QuickSort s1;
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
    }

    return 0;
}
